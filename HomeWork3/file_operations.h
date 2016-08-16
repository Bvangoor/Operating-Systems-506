#include <linux/fs.h>
#include "arguments.h"

int wrapfs_read_file(struct file *filp, void *buf, int len)
{
	mm_segment_t oldfs;
    	int bytes;
    	oldfs = get_fs();
    	set_fs(KERNEL_DS);
    	bytes = filp->f_op->read(filp, buf, len, &filp->f_pos);
    	set_fs(oldfs);
    	return bytes;
}

int wrapfs_write_file(struct file *filp, void *buf, int len)
{
    	mm_segment_t oldfs;
    	int bytes;
    	oldfs = get_fs();
    	set_fs(KERNEL_DS);
    	bytes = filp->f_op->write(filp, buf, len, &filp->f_pos);
    	set_fs(oldfs);

    	return bytes;
}

int wrapfs_write_file_pos(struct file *filp, void *buf, int len, loff_t offset)
{
    	mm_segment_t oldfs;
    	int bytes;
    	filp->f_pos = offset;
    	oldfs = get_fs();
    	set_fs(KERNEL_DS);
    	bytes = filp->f_op->write(filp, buf, len, &filp->f_pos);
    	set_fs(oldfs);

    	return bytes;
}

int check_input_output_file(struct arguments *arguments) {
	struct file *filp=NULL, *filp1=NULL;
	int err=0;
	umode_t inputFileMode, outputFileMode;
	/*start of input file*/
	filp = filp_open(arguments->input_file_name, O_RDONLY, 0);
	if (PTR_ERR(filp)==-ENOENT) {
		printk("Input File doesnot exists\n");
		err = -ENOENT;
		goto out8; //TODO
        } else {
		printk("Input File exists\n");
        }
	
	if (!filp || IS_ERR(filp)) {
		printk("Read error for input file %d\n", (int) PTR_ERR(filp));
		err = PTR_ERR(filp);
		goto out8;
        }

        inputFileMode = filp->f_inode->i_mode;

        if(!S_ISREG(inputFileMode)) {
            printk("Input File is not a regular file\n");
            err = -EISDIR;
            goto out9;
        }
	
        if (!filp->f_op->read) {
		printk("Error in reading input file\n");
		err = PTR_ERR(filp);
		goto out9;
        }

	/*end of input file*/

	/*start of output file*/

	filp1 = filp_open(arguments->output_file_name, O_WRONLY, 0);
	if (PTR_ERR(filp1)==-ENOENT) {
		printk("Output File doesnot exists, have to create it but not now\n");
		goto out8_1;
	} else {
		printk("Output File exists\n");
	}

	if(!filp1 || IS_ERR(filp1)) {
                printk("Error in opening output file\n");
                err = PTR_ERR(filp1);
                goto out8_1;
        }

	outputFileMode = filp1->f_inode->i_mode;

        if(!S_ISREG(outputFileMode)) {
                printk("Output File is not a regular file\n");
                err = -EISDIR;
                goto out9;
        }

	if (filp->f_inode->i_ino == filp1->f_inode->i_ino) {
                printk("Both input and output files are same, they should be different\n");
                err = -EPERM;
                goto out9;
        }

	/*end of output file*/
out9:
        if(filp1)
            filp_close(filp1, NULL);
out8_1:
        if(filp)
            filp_close(filp, NULL);
out8:	
	return err;
}

