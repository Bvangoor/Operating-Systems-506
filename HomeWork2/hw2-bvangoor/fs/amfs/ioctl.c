/*
 * linux/fs/amfs/ioctl.c
 *
 */

#include <linux/mount.h>
#include <linux/compat.h>
#include <asm/uaccess.h>
#include "amfs.h"

int write_to_file(struct file *filp, void *buf, int len)
{
    mm_segment_t oldfs;
    int bytes;
    oldfs = get_fs();
    set_fs(KERNEL_DS);
    bytes = filp->f_op->write(filp, buf, len, &filp->f_pos);
    set_fs(oldfs);
    return bytes;
}

static int file_unlink(struct inode *dir, struct dentry *dentry) {
    int err=0;
    err = vfs_unlink(dir, dentry, NULL);
    return err;
}

static int file_rename(struct inode *old_dir, struct dentry *old_dentry, struct inode *new_dir, struct dentry *new_dentry) {
    int err=0;
    err = vfs_rename(old_dir, old_dentry,
                     new_dir, new_dentry,
                     NULL, 0);
    return err;
}

int append_pattern_to_file(char *pattern, char *file) {
    struct file *filp=NULL;
    int err, result;
    umode_t inputFileMode;
    err = 0;
    filp = filp_open(file, O_APPEND, 0);
    if (PTR_ERR(filp)==-ENOENT) {
        printk("%s doesnot exists\n", file);
        err = -ENOENT;
        goto append_out1;
    }
    if (!filp || IS_ERR(filp)) {
        printk("Read error for pattern file %d\n", (int) PTR_ERR(filp));
        err = PTR_ERR(filp);
        goto append_out1;
    }
    inputFileMode = filp->f_inode->i_mode;
    if(!S_ISREG(inputFileMode)) {
        printk("Pattern File is not a regular file\n");
        err = -EISDIR;
        goto append_out2;
    }
    if (!filp->f_op->write) {
        printk("Error in appending to pattern file\n");
        err = PTR_ERR(filp);
        goto append_out2;
    }
    printk("pattern to write : %s %d\n", pattern, strlen(pattern));
    result = write_to_file(filp, (void*)pattern, strlen(pattern));
    printk("result value : %d\n", result);
    if ((result<0)||(result!=strlen(pattern))) {
	printk("appending to pattern file failed\n");
            err = -EFAULT;
            goto append_out2;
    }

append_out2:
    if(filp)
        filp_close(filp, NULL);
append_out1:
    return err;
}

int write_pattern_to_file(char *file, struct node *head) {
	char *tempOutFile=NULL;
	struct file *filp=NULL;
	struct dentry *dentry=NULL, *olddentry=NULL, *newdentry=NULL;
	struct node *temp=NULL;
	char *delimiter="\n";
	int err=0;
	umode_t inputFileMode;
    	filp = filp_open(file, O_WRONLY, 0);
    	if (PTR_ERR(filp)==-ENOENT) {
        	printk("%s doesnot exists\n", file);
        	err = -ENOENT;
        	goto write_out1;
    	}
    	if (!filp || IS_ERR(filp)) {
        	printk("write error for pattern file %d\n", (int) PTR_ERR(filp));
	        err = PTR_ERR(filp);
        	goto write_out1;
	}
    	inputFileMode = filp->f_inode->i_mode;
    	if(!S_ISREG(inputFileMode)) {
        	printk("Pattern File is not a regular file\n");
	        err = -EISDIR;
        	goto write_out2;
    	}
    	if (!filp->f_op->write) {
        	printk("Error in writing to pattern file\n");
	        err = PTR_ERR(filp);
        	goto write_out2;
    	}
	olddentry = filp->f_path.dentry;
        filp_close(filp, NULL);
	tempOutFile =  (char *)kmalloc((strlen(file)+5)*sizeof(char), GFP_KERNEL);
        strncpy(tempOutFile, file, strlen(file));
        strcat(tempOutFile, ".tmp");
        tempOutFile[(strlen(file)+5)]='\0';
	filp = filp_open(tempOutFile, O_WRONLY, 0);
        if (PTR_ERR(filp)==-ENOENT || IS_ERR(filp)) {
                printk("temp Output File doesnot exists, creating it\n");
        } else {
                printk("temp output File exists, truncating and creating new one\n");
                dentry = filp->f_path.dentry;
                filp_close(filp, NULL);
                err = file_unlink(dentry->d_parent->d_inode, dentry);
                if(err != 0) {
                	printk("unlink of already existing temporary file failed\n");
                	err = -EBUSY;
                	goto write_out3;
                }
                printk("unlink function returned : %d\n", err);
        }
        filp = filp_open(tempOutFile, O_CREAT, inputFileMode);
        if(!filp || IS_ERR(filp)) {
                printk("Error in creating temp output file\n");
                err = PTR_ERR(filp);
                goto write_out3;
        } else {
                printk("temp output File created succesfully\n");
        }

	newdentry = filp->f_path.dentry;

	if (!filp || IS_ERR(filp)) {
            printk("Write error for output file %d\n", (int) PTR_ERR(filp));
            err = PTR_ERR(filp);
            goto write_out3;
        }

        if (!filp->f_op->write) {
            printk("Error in writing to temp output file\n");
            err = PTR_ERR(filp);
            goto write_out3;
        }
	temp = head;
	while(temp!=NULL) {
		err = write_to_file(filp, (void*)temp->line, strlen(temp->line));
		if ((err<0)||(err!=strlen(temp->line))) {
			printk("error writing to file\n");
			goto write_out3;
		}
		err = write_to_file(filp, (void*)delimiter, strlen(delimiter));
                if ((err<0)||(err!=strlen(delimiter))) {
                        printk("error writing to file\n");
                        goto write_out3;
                }
		temp = temp->next;
	}
	err = file_rename(newdentry->d_parent->d_inode, newdentry, olddentry->d_parent->d_inode, olddentry);
        if(err!=0) {
                printk("renaming of temppattern file to pattern file failed\n");
                err = -EBUSY;
                goto write_out3;
        }

write_out3:
	if(tempOutFile)
		kfree(tempOutFile);	
write_out2:
	if(filp)
        	filp_close(filp, NULL);
write_out1:
    	return err;
}


long amfs_ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{
	struct inode *inode = file_inode(filp);
	struct super_block *sb = inode->i_sb;
	struct arguments *input;
	struct node *temp, *temp_head=NULL;
	char *delimiter="\n";
//	char *path=NULL, *pattern=NULL;
	int err, pos=0, i, len;
	bool repeat = false;
	printk("ioctl called with %u\n", cmd);
	switch (cmd) {
	case _IOC_NR(AMFS_IOC_GETPATTERN):
		input = (struct arguments *)kmalloc(sizeof(struct arguments), GFP_KERNEL);
		if (input==NULL) {
			printk("Failed to allocate kernel memory\n");
			err = -ENOMEM;
			goto out;
		}
		err = copy_from_user((void *)input, (void *)arg, sizeof(struct arguments));
		if(err){
			printk("copy from user failed\n");
			goto out;
		}
		err = copy_from_user((void *)(input->buffer), (void *)(((struct arguments*)arg)->buffer), PAGE_SIZE);
                if(err){
                        printk("copy from user failed\n");
                        goto out;
                }
		temp = amfs_pattern_super(sb);
		while(pos!=input->position) {
			temp=temp->next;
			pos++;
		}
		i=0;
		while(temp!=NULL) {
  	        	len = strlen(temp->line);
	       		if ((i+len)>PAGE_SIZE) {
				repeat = true;
        	    		break;
			}
	        	strcpy((input->buffer)+i, temp->line);
	        	i = i + strlen(temp->line);
		        (input->buffer)[i]='\n';
	        	i = i + 1;
		        pos++;
		        temp=temp->next;
	        }
	    	(input->buffer)[i-1]='\0';
		input->position=pos;
		input->repeat=(repeat)?1:0;
		put_user(input->position, &(((struct arguments*)arg)->position));
		put_user(input->repeat, &(((struct arguments*)arg)->repeat));
		put_user(input->buffer, &(((struct arguments*)arg)->buffer));			
out:		
		if(input)
			kfree(input);
		return err;
	case _IOC_NR(AMFS_IOC_ADDPATTERN):
		input = (struct arguments *)kmalloc(sizeof(struct arguments), GFP_KERNEL);
                if (input==NULL) {
                        printk("Failed to allocate kernel memory\n");
                        err = -ENOMEM;
                        goto out1;
                }
                err = copy_from_user((void *)input, (void *)arg, sizeof(struct arguments));
                if(err){
                        printk("copy from user failed\n");
                        goto out1;
                }
                err = copy_from_user((void *)(input->buffer), (void *)(((struct arguments*)arg)->buffer), PAGE_SIZE);
                if(err){
                        printk("copy from user failed\n");
                        goto out1;
                }
		printk("buffer passed from user : %s\n", input->buffer);
		err = append_pattern_to_file(input->buffer, amfs_path_super(sb));
		if(err){
			printk("failed to append pattern to file\n");
			input->repeat=0;
			goto out1;
		}
		err = append_pattern_to_file(delimiter, amfs_path_super(sb));
                if(err){
                        printk("failed to append pattern to file\n");
                        input->repeat=0;
                        goto out1;
                }
		input->repeat=1;
		temp = allocate_node(strlen(input->buffer));
                if (temp==NULL){
                    err = -ENOMEM;
                    goto out1;
                }
                strcpy(temp->line, input->buffer);  //TODO add checks
		temp_head = amfs_pattern_super(sb);
		amfs_set_pattern_super(sb, NULL);
                insert_node(&temp_head, temp);
		amfs_set_pattern_super(sb, temp_head);
		put_user(input->repeat, &(((struct arguments*)arg)->repeat));		
out1:
                if(input)
                        kfree(input);
                return err;
	case _IOC_NR(AMFS_IOC_DELPATTERN):
		input = (struct arguments *)kmalloc(sizeof(struct arguments), GFP_KERNEL);
                if (input==NULL) {
                        printk("Failed to allocate kernel memory\n");
                        err = -ENOMEM;
                        goto out2;
                }
                err = copy_from_user((void *)input, (void *)arg, sizeof(struct arguments));
                if(err){
                        printk("copy from user failed\n");
                        goto out2;
                }
                err = copy_from_user((void *)(input->buffer), (void *)(((struct arguments*)arg)->buffer), PAGE_SIZE);
                if(err){
                        printk("copy from user failed\n");
                        goto out2;
                }
                printk("buffer passed from user : %s\n", input->buffer);
		temp_head = amfs_pattern_super(sb);
		amfs_set_pattern_super(sb, NULL);
		err = delete_line(&temp_head, input->buffer);
		amfs_set_pattern_super(sb, temp_head);
		if(err) {
			printk("error in deleting pattern\n");			
		}
/*		if (err==0) {
			printk("pattern deleted\n");
			input->repeat=1;
                        put_user(input->repeat, &(((struct arguments*)arg)->repeat));
		}*/
		if(err==0) {
			err = write_pattern_to_file(amfs_path_super(sb), temp_head);
			input->repeat=1;
			put_user(input->repeat, &(((struct arguments*)arg)->repeat));
		}
out2:
		if(input)
                        kfree(input);
                return err;
	default:
		return -ENOTTY;
	}
}

