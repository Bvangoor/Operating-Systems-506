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

#ifndef _AMFS_H_
#define _AMFS_H_

#include <linux/dcache.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/aio.h>
#include <linux/mm.h>
#include <linux/mount.h>
#include <linux/namei.h>
#include <linux/seq_file.h>
#include <linux/statfs.h>
#include <linux/fs_stack.h>
#include <linux/magic.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/xattr.h>

/* the file system name */
#define AMFS_NAME "amfs"

/* amfs root inode number */
#define AMFS_ROOT_INO     1

/* useful for tracking code reachability */
#define UDBG printk(KERN_DEFAULT "DBG:%s:%s:%d\n", __FILE__, __func__, __LINE__)

/* operations vectors defined in specific files */
extern const struct file_operations amfs_main_fops;
extern const struct file_operations amfs_dir_fops;
extern const struct inode_operations amfs_main_iops;
extern const struct inode_operations amfs_dir_iops;
extern const struct inode_operations amfs_symlink_iops;
extern const struct super_operations amfs_sops;
extern const struct dentry_operations amfs_dops;
extern const struct address_space_operations amfs_aops, amfs_dummy_aops;
extern const struct vm_operations_struct amfs_vm_ops;

extern int amfs_init_inode_cache(void);
extern void amfs_destroy_inode_cache(void);
extern int amfs_init_dentry_cache(void);
extern void amfs_destroy_dentry_cache(void);
extern int new_dentry_private_data(struct dentry *dentry);
extern void free_dentry_private_data(struct dentry *dentry);
extern struct dentry *amfs_lookup(struct inode *dir, struct dentry *dentry,
				    unsigned int flags);
extern struct inode *amfs_iget(struct super_block *sb,
				 struct inode *lower_inode);
extern int amfs_interpose(struct dentry *dentry, struct super_block *sb,
			    struct path *lower_path);

extern long amfs_ioctl(struct file *, unsigned int, unsigned long);

struct arguments {
	char *buffer;
	int position;
	int repeat;
};

/* ioctl commands*/
#define AMFS_IOC_GETPATTERN             _IOR('f', 21, struct arguments)
#define AMFS_IOC_ADDPATTERN             _IOW('f', 22, struct arguments)
#define AMFS_IOC_DELPATTERN             _IOW('f', 23, struct arguments)

/* Extended Attributes*/
#define XATTR_NAME "user.quarantine"

/* device name and option */
struct options {
    const char *dev_name;
    char *pattern_file;
};

/*For list operations*/
struct node {
    char *line;
    struct node *next;
    struct node *prev;
};


extern struct node* allocate_node(int len);
extern void delete_node(struct node *old);
extern void insert_node(struct node **head, struct node *new);
extern int delete_line(struct node **head, char *line);
extern void delete_entire_list(struct node **head);

/* file private data */
struct amfs_file_info {
	struct file *lower_file;
	const struct vm_operations_struct *lower_vm_ops;
};

/* amfs inode data in memory */
struct amfs_inode_info {
	struct inode *lower_inode;
	struct inode vfs_inode;
};

/* amfs dentry data in memory */
struct amfs_dentry_info {
	spinlock_t lock;	/* protects lower_path */
	struct path lower_path;
};

/* amfs super-block data in memory */
struct amfs_sb_info {
	struct super_block *lower_sb;
	struct node *pattern_list;
	char *path;
};

/*
 * inode to private data
 *
 * Since we use containers and the struct inode is _inside_ the
 * amfs_inode_info structure, AMFS_I will always (given a non-NULL
 * inode pointer), return a valid non-NULL pointer.
 */
static inline struct amfs_inode_info *AMFS_I(const struct inode *inode)
{
	return container_of(inode, struct amfs_inode_info, vfs_inode);
}

/* dentry to private data */
#define AMFS_D(dent) ((struct amfs_dentry_info *)(dent)->d_fsdata)

/* superblock to private data */
#define AMFS_SB(super) ((struct amfs_sb_info *)(super)->s_fs_info)

/* file to private Data */
#define AMFS_F(file) ((struct amfs_file_info *)((file)->private_data))

/* file to lower file */
static inline struct file *amfs_lower_file(const struct file *f)
{
	return AMFS_F(f)->lower_file;
}

static inline void amfs_set_lower_file(struct file *f, struct file *val)
{
	AMFS_F(f)->lower_file = val;
}

/* inode to lower inode. */
static inline struct inode *amfs_lower_inode(const struct inode *i)
{
	return AMFS_I(i)->lower_inode;
}

static inline void amfs_set_lower_inode(struct inode *i, struct inode *val)
{
	AMFS_I(i)->lower_inode = val;
}

/* superblock to lower superblock */
static inline struct super_block *amfs_lower_super(
	const struct super_block *sb)
{
	return AMFS_SB(sb)->lower_sb;
}

static inline void amfs_set_lower_super(struct super_block *sb,
					  struct super_block *val)
{
	AMFS_SB(sb)->lower_sb = val;
}

/* superblock to pattern lines list*/
static inline struct node *amfs_pattern_super(
        const struct super_block *sb)
{
        return AMFS_SB(sb)->pattern_list;
}

static inline void amfs_set_pattern_super(struct super_block *sb,
                                          struct node *val)
{
        AMFS_SB(sb)->pattern_list = val;
}

static inline char* amfs_path_super(
        const struct super_block *sb)
{
        return AMFS_SB(sb)->path;
}

static inline void amfs_set_path_super(struct super_block *sb,
                                          char *val)
{
        AMFS_SB(sb)->path = val;
}


/* path based (dentry/mnt) macros */
static inline void pathcpy(struct path *dst, const struct path *src)
{
	dst->dentry = src->dentry;
	dst->mnt = src->mnt;
}
/* Returns struct path.  Caller must path_put it. */
static inline void amfs_get_lower_path(const struct dentry *dent,
					 struct path *lower_path)
{
	spin_lock(&AMFS_D(dent)->lock);
	pathcpy(lower_path, &AMFS_D(dent)->lower_path);
	path_get(lower_path);
	spin_unlock(&AMFS_D(dent)->lock);
	return;
}
static inline void amfs_put_lower_path(const struct dentry *dent,
					 struct path *lower_path)
{
	path_put(lower_path);
	return;
}
static inline void amfs_set_lower_path(const struct dentry *dent,
					 struct path *lower_path)
{
	spin_lock(&AMFS_D(dent)->lock);
	pathcpy(&AMFS_D(dent)->lower_path, lower_path);
	spin_unlock(&AMFS_D(dent)->lock);
	return;
}
static inline void amfs_reset_lower_path(const struct dentry *dent)
{
	spin_lock(&AMFS_D(dent)->lock);
	AMFS_D(dent)->lower_path.dentry = NULL;
	AMFS_D(dent)->lower_path.mnt = NULL;
	spin_unlock(&AMFS_D(dent)->lock);
	return;
}
static inline void amfs_put_reset_lower_path(const struct dentry *dent)
{
	struct path lower_path;
	spin_lock(&AMFS_D(dent)->lock);
	pathcpy(&lower_path, &AMFS_D(dent)->lower_path);
	AMFS_D(dent)->lower_path.dentry = NULL;
	AMFS_D(dent)->lower_path.mnt = NULL;
	spin_unlock(&AMFS_D(dent)->lock);
	path_put(&lower_path);
	return;
}

/* locking helpers */
static inline struct dentry *lock_parent(struct dentry *dentry)
{
	struct dentry *dir = dget_parent(dentry);
	mutex_lock_nested(&dir->d_inode->i_mutex, I_MUTEX_PARENT);
	return dir;
}

static inline void unlock_dir(struct dentry *dir)
{
	mutex_unlock(&dir->d_inode->i_mutex);
	dput(dir);
}
#endif	/* not _AMFS_H_ */
