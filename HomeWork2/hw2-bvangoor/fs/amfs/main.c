/*
 * Copyright (c) 1998-2014 Erez Zadok
 * Copyright (c) 2009	   Shrikar Archak
 * Copyright (c) 2003-2014 Stony Brook University
 * Copyright (c) 2003-2014 The Research Foundation of SUNY
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "amfs.h"
#include <linux/module.h>
#include <linux/parser.h>

int read_from_file(struct file *filp, void *buf, int len)
{
    mm_segment_t oldfs;
    int bytes;
    oldfs = get_fs();
    set_fs(KERNEL_DS);
//    filp->f_pos = 0;
    printk("file position : %llu\n", filp->f_pos);
    bytes = filp->f_op->read(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);
    return bytes;
}

static char *split_new_lines(char **s)
{
        char *sbegin = *s;
        char *p;

        if (sbegin == NULL)
                return NULL;

        for (p = sbegin; *p; p++) {
                if (*p == '\n') {
                        *p = '\0';
                        *s = p + 1;
                        return sbegin;
                }
        }
        *s = NULL;
        return sbegin;
}

struct node* allocate_node(int len) {
    struct node *temp;
    temp = (struct node*)kmalloc(sizeof(struct node), GFP_KERNEL);
    if(temp==NULL) {
	printk("Error Allocating node\n");
	return NULL;
    }
    temp->line = (char *)kmalloc(len*sizeof(char), GFP_KERNEL);
    if(temp->line==NULL) {
	printk("Error Allocating node\n");
        return NULL;
    }
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

void delete_node(struct node *old) {
    kfree(old->line);
    kfree(old);
}

void insert_node(struct node **head, struct node *new) {
    struct node *temp;
    if((*head)==NULL)
        *head=new;
    else {
        temp=*head;
        while(temp->next!=NULL)
            temp=temp->next;
        temp->next=new;
        new->prev=temp;
    }
}

int delete_line(struct node **head, char *line) {
    struct node *temp, *prev, *next;
    if((*head)==NULL) {
        printk("Error head is NULL\n");
        return -ENODATA;
    } else {
        temp=*head;
        while(temp!=NULL) {
            if(strcmp(temp->line, line)==0) {
                if(temp==*head) {
                    next = temp->next;
                    temp->next=NULL;
                    delete_node(temp);
                    *head = next;
                    if(*head)
                        (*head)->prev=NULL;
                    return 0;
                } else {
                    prev=temp->prev;
                    next=temp->next;
                    temp->prev=NULL;
                    temp->next=NULL;
                    prev->next=next;
                    if(next)
                        next->prev=prev;
                    delete_node(temp);
                    return 0;
                }
            }
	    temp=temp->next;
        }
    }
    printk("deleted nothing\n");
    return -ENODATA;
}

void delete_entire_list(struct node **head) {
    struct node *temp1, *temp2;
    temp1 = *head;
    temp2=NULL;
    if(temp1)
        temp2 = temp1->next;
    while(temp1!=NULL) {
        delete_node(temp1);
        temp1=temp2;
        if(temp1)
            temp2 = temp1->next;
    }
    *head=NULL;
}

void print_list(struct node **head) {
    struct node *temp;
    temp=*head;
    while(temp!=NULL) {
        printk("line : %s\n", temp->line);
        temp=temp->next;
    }
}

int read_pattern_file(struct node **head, char *file) {
    struct file *filp=NULL;
    struct node *temp;
    char *srcbuffer, *p, *dummyptr;
    int err, result;
    umode_t inputFileMode;
    result=PAGE_SIZE;
    err = 0; 
    filp = filp_open(file, O_RDONLY, 0);
    if (PTR_ERR(filp)==-ENOENT) {
	printk("%s doesnot exists\n", file);
	err = -ENOENT;
	goto out1;
    }
    if (!filp || IS_ERR(filp)) {
	printk("Read error for pattern file %d\n", (int) PTR_ERR(filp));
        err = PTR_ERR(filp);
        goto out1;
    }
    inputFileMode = filp->f_inode->i_mode;
    if(!S_ISREG(inputFileMode)) {
	printk("Pattern File is not a regular file\n");
        err = -EISDIR;
	goto out2;
    }
    if (!filp->f_op->read) {
	printk("Error in reading pattern file\n");
        err = PTR_ERR(filp);
        goto out2;
    }
    srcbuffer = (char *)kmalloc((PAGE_SIZE+1)*sizeof(char), GFP_KERNEL);
    if (srcbuffer==NULL) {
	printk("Failed to allocate kernel memory for srcbuffer\n");
	err = -ENOMEM;
	goto out2;
    }
    while(result==PAGE_SIZE) {
	printk("before\n");
	result = read_from_file(filp, (void *)srcbuffer, PAGE_SIZE);
	printk("after\n");
        if(result < 0) {
	    printk("Reading from input file failed\n");
	    err = -EFAULT;
	    goto out3;
        }
//	if(result < PAGE_SIZE)
	srcbuffer[result]='\0';
	dummyptr = srcbuffer;
	while ((p = split_new_lines(&srcbuffer)) != NULL) {
	    if(*p) {
		temp = allocate_node(strlen(p));
		if (temp==NULL){
		    err = -ENOMEM;
		    goto out4;
		}
		strcpy(temp->line, p);  //TODO add checks
		insert_node(head, temp);
	    }
	}
	if(srcbuffer==NULL)
		srcbuffer = dummyptr;
    }
//    print_list(head);
out4:
    if(err)
        delete_entire_list(head); //delete only in case of error
out3:
    kfree(srcbuffer);
out2:
    if(filp)
	filp_close(filp, NULL);
out1:
    return err;
}

/*
 * There is no need to lock the amfs_super_info's rwsem as there is no
 * way anyone can have a reference to the superblock at this point in time.
 */
static int amfs_read_super(struct super_block *sb, void *raw_data, int silent)
{
	int err = 0, len;
	struct super_block *lower_sb;
	struct path lower_path;
	struct options *opt;
	char *dev_name, *path=NULL;
	struct inode *inode;
	struct node *head;
	opt = (struct options *) raw_data;
	dev_name = (char *)opt->dev_name;
	head = NULL;
	if (!dev_name) {
		printk(KERN_ERR
		       "amfs: read_super: missing dev_name argument\n");
		err = -EINVAL;
		goto out;
	}	
	/* reading pattern file */
	err = read_pattern_file(&head, (char *)opt->pattern_file);
	if (err) {
	    printk("Error reading pattern file\n");
	    goto out;
	}
	len = strlen((char *)opt->pattern_file);
	path = kmalloc(len+1, GFP_KERNEL);
	if(path==NULL) {
	  	printk("kernel out of memory\n");
		err = -ENOMEM;
		goto out;	
	}
	strncpy(path, (char *)opt->pattern_file, len);
	path[len]='\0';
	printk("path : %s\n", path);
//	printk("From created head\n");
//	print_list(&head);
	/* parse lower path */
	err = kern_path(dev_name, LOOKUP_FOLLOW | LOOKUP_DIRECTORY,
			&lower_path);
	if (err) {
		printk(KERN_ERR	"amfs: error accessing "
		       "lower directory '%s'\n", dev_name);
		goto out;
	}

	/* allocate superblock private data */
	sb->s_fs_info = kzalloc(sizeof(struct amfs_sb_info), GFP_KERNEL);
	if (!AMFS_SB(sb)) {
		printk(KERN_CRIT "amfs: read_super: out of memory\n");
		err = -ENOMEM;
		goto out_free;
	}

	/* set the lower superblock field of upper superblock */
	lower_sb = lower_path.dentry->d_sb;
	atomic_inc(&lower_sb->s_active);
	amfs_set_lower_super(sb, lower_sb);
	amfs_set_pattern_super(sb, head);
	amfs_set_path_super(sb, path);
	printk("path form sb : %s\n", amfs_path_super(sb));
//	temp = amfs_pattern_super(sb);
//	printk("From super block \n");
//        print_list(&temp);
	/* inherit maxbytes from lower file system */
	sb->s_maxbytes = lower_sb->s_maxbytes;

	/*
	 * Our c/m/atime granularity is 1 ns because we may stack on file
	 * systems whose granularity is as good.
	 */
	sb->s_time_gran = 1;

	sb->s_op = &amfs_sops;

	/* get a new inode and allocate our root dentry */
	inode = amfs_iget(sb, lower_path.dentry->d_inode);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_sput;
	}
	sb->s_root = d_make_root(inode);
	if (!sb->s_root) {
		err = -ENOMEM;
		goto out_iput;
	}
	d_set_d_op(sb->s_root, &amfs_dops);

	/* link the upper and lower dentries */
	sb->s_root->d_fsdata = NULL;
	err = new_dentry_private_data(sb->s_root);
	if (err)
		goto out_freeroot;

	/* if get here: cannot have error */

	/* set the lower dentries for s_root */
	amfs_set_lower_path(sb->s_root, &lower_path);

	/*
	 * No need to call interpose because we already have a positive
	 * dentry, which was instantiated by d_make_root.  Just need to
	 * d_rehash it.
	 */
	d_rehash(sb->s_root);
	if (!silent)
		printk(KERN_INFO
		       "amfs: mounted on top of %s type %s\n",
		       dev_name, lower_sb->s_type->name);
	goto out; /* all is well */

	/* no longer needed: free_dentry_private_data(sb->s_root); */
out_freeroot:
	dput(sb->s_root);
out_iput:
	iput(inode);
out_sput:
	/* drop refs we took earlier */
	atomic_dec(&lower_sb->s_active);
	kfree(AMFS_SB(sb));
	sb->s_fs_info = NULL;
out_free:
	path_put(&lower_path);

out:
	if (err && head)
	    delete_entire_list(&head);
	if(err && path)
	    kfree(path);
	return err;
}

enum {
        OPT_PATTERNFILE,
        OPT_ERR,
};

static const match_table_t amfs_tokens = {
        {OPT_PATTERNFILE,              "pattdb=%s"},
        {OPT_ERR,                       NULL}
};

static int amfs_parse_opt(char *opt, char **result)
{
        char *p;
        int token;
	substring_t args[MAX_OPT_ARGS];
        p = opt;
	token = match_token(p, amfs_tokens, args);
	switch (token) {
	case OPT_PATTERNFILE:
	    *result = match_strdup(&args[0]);
	    break;
	default:
            printk("amfs: unrecognized mount option \"%s\" or missing value\n", p);
            return -EINVAL;
	}
        return 0;
}

void print_usage(void) {
	printk("usage : mount -t amfs -o pattdb=<patternfile> <lower file system dir> <mount point>\n");
	return;
}

struct dentry *amfs_mount(struct file_system_type *fs_type, int flags,
			    const char *dev_name, void *raw_data)
{
	struct options *opt;
	struct dentry *d;
	char *pattern_file;
        int result;
//	pattern_file = (char *)kmalloc();
	if((char*)raw_data==NULL) {
		print_usage();	
		return ERR_PTR(-EINVAL);
	}
	result = amfs_parse_opt((char*)raw_data, &pattern_file);
	if (result) {
	    printk("Error in parsing option : %s\n", (char*)raw_data);
	    print_usage();
	    return ERR_PTR(result);
	}
	if(!dev_name) {
	    print_usage();
	    return ERR_PTR(-EINVAL);
	}
 	opt = (struct options*)kmalloc(sizeof(struct options), GFP_KERNEL);
	if (opt==NULL)
	    return ERR_PTR(-ENOMEM);
	opt->pattern_file = (char*)(pattern_file);
	opt->dev_name = dev_name;
	printk("Lower device Name : %s\n", opt->dev_name);
 	printk("Pattern file : %s\n", opt->pattern_file);
	d = mount_nodev(fs_type, flags, (void*)opt,
                           amfs_read_super);
	if(IS_ERR(d)) {
	    if(opt->pattern_file)
		kfree(opt->pattern_file);
	    if(opt)
	        kfree(opt);
	}
	return d;   
}

static struct file_system_type amfs_fs_type = {
	.owner		= THIS_MODULE,
	.name		= AMFS_NAME,
	.mount		= amfs_mount,
	.kill_sb	= generic_shutdown_super,
	.fs_flags	= 0,
};
MODULE_ALIAS_FS(AMFS_NAME);

static int __init init_amfs_fs(void)
{
	int err;

	pr_info("Registering amfs " AMFS_VERSION "\n");

	err = amfs_init_inode_cache();
	if (err)
		goto out;
	err = amfs_init_dentry_cache();
	if (err)
		goto out;
	err = register_filesystem(&amfs_fs_type);
out:
	if (err) {
		amfs_destroy_inode_cache();
		amfs_destroy_dentry_cache();
	}
	return err;
}

static void __exit exit_amfs_fs(void)
{
	amfs_destroy_inode_cache();
	amfs_destroy_dentry_cache();	
	unregister_filesystem(&amfs_fs_type);
	pr_info("Completed amfs module unload\n");
}

MODULE_AUTHOR("Bharath Kumar Reddy Vangoor, Filesystems and Storage Lab, Stony Brook University"
	      " (http://www.fsl.cs.sunysb.edu/~bharath/)");
MODULE_DESCRIPTION("Amfs " AMFS_VERSION
		   " (http://wrapfs.filesystems.org/)");
MODULE_LICENSE("GPL");

module_init(init_amfs_fs);
module_exit(exit_amfs_fs);
