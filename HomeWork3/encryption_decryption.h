#include <linux/crypto.h>
#include <linux/scatterlist.h>
#include <linux/random.h>
#include "arguments.h"

unsigned int nearestRoundup(int x) {
    	if ((x%16)==0)
        	return x;
    	else
        	return ((x)+(16-(x%16)));
}

static int decrypt_Cipher(char *key, char *src, char *dest, unsigned int len) {
    	struct crypto_blkcipher *blkcipher = NULL;
    	char *cipher = "cbc(aes)";
    	struct scatterlist sg_in[1];
    	struct scatterlist sg_out[1];
    	struct blkcipher_desc desc;
    	unsigned int encrypted_datalen;
    	char *iv=NULL;
    	int ret = -EFAULT;
    	encrypted_datalen = len;
    	blkcipher = crypto_alloc_blkcipher(cipher, 0, 0);
    	if (IS_ERR(blkcipher)) {
        	printk("could not allocate blkcipher handle for %s\n", cipher);
        	return -PTR_ERR(blkcipher);
    	}

    	if (crypto_blkcipher_setkey(blkcipher, key, strlen(key))) {
        	printk("key could not be set\n");
        	ret = -EAGAIN;
        	goto out;
    	}
    	desc.flags = 0;
    	desc.tfm = blkcipher;

    	iv = (char *)kmalloc(crypto_blkcipher_ivsize(blkcipher) , GFP_KERNEL);
    	if(iv==NULL) {
        	printk("Initialisation vector not initialised\n");
        	ret = -ENOMEM;
        	goto out;
    	}
    	memset(iv, 0, crypto_blkcipher_ivsize(blkcipher));
    	sg_init_table(sg_in, 1);
    	sg_set_buf(sg_in, src, encrypted_datalen);

    	sg_init_table(sg_out, 1);
    	sg_set_buf(sg_out, dest, encrypted_datalen);

    	crypto_blkcipher_set_iv(blkcipher, iv, crypto_blkcipher_ivsize(blkcipher));
    	ret = crypto_blkcipher_decrypt(&desc, sg_out, sg_in, encrypted_datalen);

    	printk("Cipher Decryption operation completed\n");
    	kfree(iv);
    	crypto_free_blkcipher(blkcipher);
    	return ret;

out:
    	if (blkcipher)
        	crypto_free_blkcipher(blkcipher);
    	if (iv)
        	kfree(iv);
    	return ret;
}

static int encrypt_Cipher(char *key, char *src, char *dest, unsigned int len, int *written) {
    	struct crypto_blkcipher *blkcipher = NULL;
    	char *cipher = "cbc(aes)";
    	struct scatterlist sg_in[2];
    	struct scatterlist sg_out[1];
    	struct blkcipher_desc desc;
    	unsigned int encrypted_datalen;
    	unsigned int padlen;
    	char pad[16];
    	char *iv=NULL;
    	int ret = -EFAULT;
    	encrypted_datalen = nearestRoundup(len);
    	padlen = encrypted_datalen - len;
    	blkcipher = crypto_alloc_blkcipher(cipher, 0, 0);
    	if (IS_ERR(blkcipher)) {
        	printk("could not allocate blkcipher handle for %s\n", cipher);
        	return -PTR_ERR(blkcipher);
    	}

    	if (crypto_blkcipher_setkey(blkcipher, key, strlen(key))) {
        	printk("key could not be set\n");
        	ret = -EAGAIN;
        	goto out;
    	}
    	desc.flags = 0;
    	desc.tfm = blkcipher;

    	iv = (char *)kmalloc(crypto_blkcipher_ivsize(blkcipher) , GFP_KERNEL);
    	if(iv==NULL) {
        	printk("Initialisation vector not initialised\n");
        	ret = -ENOMEM;
        	goto out;
    	}
    	memset(iv, 0, crypto_blkcipher_ivsize(blkcipher));
    	memset(pad, 0, sizeof pad);
    	sg_init_table(sg_in, 2);
    	sg_set_buf(&sg_in[0], src, len);
    	sg_set_buf(&sg_in[1], pad, padlen);

    	sg_init_table(sg_out, 1);
    	sg_set_buf(sg_out, dest, encrypted_datalen);
    	crypto_blkcipher_set_iv(blkcipher, iv, crypto_blkcipher_ivsize(blkcipher));
    	ret = crypto_blkcipher_encrypt(&desc, sg_out, sg_in, encrypted_datalen);

    	(*written) = encrypted_datalen;
    	printk("Cipher Encryption operation completed\n");
    	kfree(iv);
    	crypto_free_blkcipher(blkcipher);
    	return ret;

out:
    	if (blkcipher)
        	crypto_free_blkcipher(blkcipher);
    	if (iv)
        	kfree(iv);
    	return ret;
}

char giveBit(int x) {
    	if(x==0)
        	return '0';
    	else
        	return '1';
}


void buildPadding(char *array, int val) {
    	int i=0, rem, div;
    	div = val;
    	while (div > 0) {
        	rem = div%2;
        	array[i] = giveBit(rem);
       		i++;
        	div = div/2;
    	}
}


void initialisePadding(char *array) {
    	array[0]='0';
    	array[1]='0';
   	array[2]='0';
    	array[3]='0';
}

int exponential(int a, int b) {
    	if(b==0)
        	return 1;
    	else {
        	int i=1, val=1;
        	while(i<=b) {
            		val = val * a;
            		i++;
        	}
        	return val;
    	}
}

int reconstructPadding(char *array) {
    	int i, val=0;
    	for (i=0;i<4;i++) {
        	if(array[i]=='1') {
            		val = val + exponential(2,i);
        	}
    	}
    	return val;
}

void printPadding(char *array) {
    	int i;
    	for (i=0;i<4;i++)
        	printk("array[%d]=%c\n", i, array[i]);
}

bool compareKeys(char *passedKey, char *keyFromFile, int len) {
    	int i;
    	for (i=0;i<len;i++) {
        	if(passedKey[i]!=keyFromFile[i])
        	return false;
    	}
    	return true;
}


static int generate_md5(char *src, char *dest, int len) {
    	struct scatterlist sg[1];
    	struct crypto_hash *tfm;
    	struct hash_desc desc;
    	int ret = 0;
	printk("src given : %s\n", src);
	printk("length : %d\n", len);

    	tfm = crypto_alloc_hash("md5", 0, CRYPTO_ALG_ASYNC);
	printk("debugging 1\n");
    	if (IS_ERR(tfm)) {
        	ret = -EAGAIN;
        	goto out;
    	}

    	desc.tfm = tfm;
    	desc.flags = 0;
    	sg_init_table(sg, 1);
    	sg_set_buf(sg, src, len);
	printk("debugging 2\n");
    	if (crypto_hash_digest(&desc, sg, 1, dest) )
        	ret = -EAGAIN;
out :
    	crypto_free_hash(tfm);
    	return ret;
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


int encrypt_decrypt(struct arguments *job) {
	int result, paddedresult=0, padvalue, preambleWritten, temp, paddingWritten, paddingRead;
        struct file *filp=NULL, *filp1=NULL;
        struct dentry *dentry=NULL, *olddentry=NULL, *newdentry=NULL;
        char *srcbuffer, *destbuffer, *padding, *keyFromFile=NULL, *md5_hash=NULL, *tempOutFile;
        umode_t inputFileMode, outputFileMode;
        bool outFileCreated=false, renamed=false, success = false;
        int err=0;
	srcbuffer = (char *)kmalloc((PAGE_SIZE+1)*sizeof(char), GFP_KERNEL);
        if (srcbuffer==NULL) {
        	printk("Failed to allocate kernel memory for srcbuffer\n");
        	err = -ENOMEM;
        	goto out5;
        }

	destbuffer = (char *)kmalloc((PAGE_SIZE+1)*sizeof(char), GFP_KERNEL);
        if (destbuffer==NULL) {
        	printk("Failed to allocate kernel memory for destbuffer\n");
            	err = -ENOMEM;
            	goto out6;
        }

	padding = (char *)kmalloc(4*sizeof(char), GFP_KERNEL);
        if (padding==NULL) {
            	printk("Failed to allocate kernel memory for padding\n");
          	err = -ENOMEM;
            	goto out7;
        }

	initialisePadding(padding);

	result=PAGE_SIZE;

	filp = filp_open(job->input_file_name, O_RDONLY, 0);
        if (PTR_ERR(filp)==-ENOENT) {
        	printk("Input File doesnot exists\n");
            	err = -ENOENT;
            	goto out8;
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

	/*End of input file*/

	filp1 = filp_open(job->output_file_name, O_WRONLY, inputFileMode&~current_umask());
        if (PTR_ERR(filp1)==-ENOENT) {
            	printk("Output File doesnot exists, creating it\n");
            	filp1 = filp_open(job->output_file_name, O_CREAT, inputFileMode&~current_umask()); /*Creating output file if it doesnot exists with input file permissions*/
            	if(!filp1 || IS_ERR(filp1)) {
                	printk("Error in creating output file\n");
                	err = PTR_ERR(filp1);
                	goto out8_1;
            	} else {
                	printk("Output File created succesfully\n");
                	outFileCreated = true;
            	}
        } else {
            	printk("Output File exists\n");
        }

	if(!outFileCreated) {
            	if(!filp1 || IS_ERR(filp1)) {
                	printk("Error in opening output file\n");
                	err = PTR_ERR(filp1);
               		goto out8_1;
            	}
        }

	if(!outFileCreated) {
            	outputFileMode = filp1->f_inode->i_mode;
            	if(!S_ISREG(outputFileMode)) {
                	printk("Output File is not a regular file\n");
                	err = -EISDIR;
                	goto out9;
            	}
        }

	if(!outFileCreated) {
            	if (filp->f_inode->i_ino == filp1->f_inode->i_ino) {
                	printk("Both input and output files are same, they should be different\n");
                	err = -EPERM;
               		goto out9;
            	}
        }

	if(!outFileCreated) {
            	olddentry = filp1->f_path.dentry;
            	filp_close(filp1, NULL);
            	tempOutFile =  (char *)kmalloc((strlen(job->output_file_name)+5)*sizeof(char), GFP_KERNEL);
            	strncpy(tempOutFile, job->output_file_name, strlen(job->output_file_name));
            	strcat(tempOutFile, ".tmp");
            	tempOutFile[(strlen(job->output_file_name)+5)]='\0';
            	filp1 = filp_open(tempOutFile, O_WRONLY, 0);
            	if (PTR_ERR(filp1)==-ENOENT || IS_ERR(filp1)) {
                	printk("temp Output File doesnot exists, creating it\n");
            	} else {
                	printk("temp output File exists, truncating and creating new one\n");
                	dentry = filp1->f_path.dentry;
                	filp_close(filp1, NULL);
                	err = file_unlink(dentry->d_parent->d_inode, dentry);
                	if(err != 0) {
                    		printk("unlink of already existing temporary file failed\n");
                    		err = -EBUSY;
                    		goto out9;
                	}
                	printk("unlink function returned : %d\n", err);
            	}
            	filp1 = filp_open(tempOutFile, O_CREAT, outputFileMode);
            	if(!filp1 || IS_ERR(filp1)) {
                	printk("Error in creating temp output file\n");
                	err = PTR_ERR(filp1);
                	goto out8_1;
            	} else {
                	printk("temp output File created succesfully\n");
            	}
        }

	newdentry = filp1->f_path.dentry;

        if (!filp1 || IS_ERR(filp1)) {
            	printk("Write error for output file %d\n", (int) PTR_ERR(filp1));
           	 err = PTR_ERR(filp1);
            	goto out10;
        }

        if (!filp1->f_op->write) {
            	printk("Error in writing to temp output file\n");
           	 err = PTR_ERR(filp1);
            	goto out10;
        }

	md5_hash = kmalloc(17*sizeof(char), GFP_KERNEL);
        if (md5_hash==NULL) {
            	printk("Failed to allocate kernel memory for key from file\n");
            	err = -ENOMEM;
            	goto out10;
        }
	printk("Generating MD5 Hash\n");
        err = generate_md5(job->pass_phrase, md5_hash, strlen(job->pass_phrase));
        if(err != 0) {
            	printk("kernel MD5 generation failed\n");
            	goto out11;
        }
        md5_hash[strlen(job->pass_phrase)] = '\0';
	printk("completed generating MD5 Hash\n");
	if(job->operation_type==1) { //Encryption
		preambleWritten = wrapfs_write_file(filp1, (void *)(md5_hash), strlen(md5_hash)); /*Writing Key hash to the file*/
            	if(preambleWritten < 0) {
                	printk("Writing preamble failed\n");
                	err = -EFAULT;
                	goto out11;
            	}
            	paddingWritten = wrapfs_write_file(filp1, (void *)(padding), 4); /*Writing Inital Padding to the file*/
            	if (paddingWritten < 0) {
                	printk("Writing padding failed\n");
                	err = -EFAULT;
                	goto out11;
            	}
            	while(result==PAGE_SIZE) {
                	result = wrapfs_read_file(filp, (void *)srcbuffer, PAGE_SIZE);
                	if(result < 0) {
                    		printk("Reading from input file failed\n");
                   	 	err = -EFAULT;
                    		goto out11;
                	}
                	err = encrypt_Cipher(job->pass_phrase, srcbuffer, destbuffer, result, &paddedresult);
                	if (err < 0) {
                    		printk("Error occured while encrypting\n");
                    		goto out11;
                	}
                	if(paddedresult!=result) {
                    		padvalue = paddedresult - result;
                    		buildPadding(padding, padvalue);
                    		result = paddedresult;
                	}
                	result = wrapfs_write_file(filp1, (void *)destbuffer, result);
                	if (result < 0) {
                    		printk("Writing to output file failed\n");
                   		err = -EFAULT;
                    		goto out11;
                	}
            	}
            	paddingWritten = wrapfs_write_file_pos(filp1, (void *)padding, 4, preambleWritten);
            	if (paddingWritten < 0) {
                	printk("Writing padding failed\n");
                	err = -EFAULT;
                	goto out11;
            	}
	} else if (job->operation_type==2) { //Decryption
		keyFromFile = kmalloc(16*sizeof(char), GFP_KERNEL);
            	if (keyFromFile==NULL) {
                	printk("Failed to allocate kernel memory for key from file\n");
                	err = -ENOMEM;
                	goto out11;
            	}
            	temp = wrapfs_read_file(filp, (void *)keyFromFile, strlen(md5_hash));
            	if (temp != strlen(md5_hash)) {
                	printk("reading key from file failed\n");
                	err = -EFAULT;
                	goto out12;
            	}
            	if (compareKeys(md5_hash, keyFromFile, temp)) {
                	printk("Both Keys Match\n");
            	} else {
                	printk("Both keys doesnot match\n");
                	err = -EINVAL; //TODO : Return proper error Value.
                	goto out12;
            	}
            	paddingRead = wrapfs_read_file(filp, (void *)padding, 4);
            	if(paddingRead < 0) {
                	printk("Reading padding failed\n");
                	err = -EFAULT;
                	goto out12;
            	}
            	padvalue = reconstructPadding(padding);
            	if (padvalue < 0) {
                	printk("Reconstructing padding value failed(negative value not acceptable)\n");
                	err = -EFAULT;
                	goto out12;
            	}
            	printk("Pad value returned : %d\n", padvalue);
		while(result==PAGE_SIZE) {
                	result = wrapfs_read_file(filp, (void *)srcbuffer, PAGE_SIZE);
                	if (result < 0) {
                    		printk("Reading from input file failed\n");
                    		err = -EFAULT;
                    		goto out12;
                	}
                	printk("result read from file : %u\n", result);
                	err = decrypt_Cipher(job->pass_phrase, srcbuffer, destbuffer, result);
                	if (err < 0) {
                    		printk("Error occured while encrypting\n");
                    		goto out12;
                	}
                	if (result<PAGE_SIZE) {
                    		result = result - padvalue;
                	}
                	result = wrapfs_write_file(filp1, (void *)destbuffer, result);
                	if(result < 0) {
                    		printk("writing to output file failed\n");
                    		err = -EFAULT; //TODO goto
                    		goto out12;
                	}
            	}
	}
	if(!outFileCreated) {
            	err = file_rename(newdentry->d_parent->d_inode, newdentry, olddentry->d_parent->d_inode, olddentry);
            	if(err!=0) {
                	printk("renaming of tempfile to output file failed\n");
                	err = -EBUSY;
                	goto out12;
            	} else
                	renamed = true;
        } else
            	success = true;

out12:
        if(keyFromFile)
            	kfree(keyFromFile);
out11:
        kfree(md5_hash);
out10:
        if(filp1)
            	filp_close(filp1, NULL);
        if((!renamed && !outFileCreated)||(!success && outFileCreated))
            	file_unlink(newdentry->d_parent->d_inode, newdentry);
out9:
        if(filp1)
            	filp_close(filp1, NULL);
out8_1:
        if(filp)
            	filp_close(filp, NULL);
out8:
        kfree(padding);
out7:
        kfree(destbuffer);
out6:
        kfree(srcbuffer);
out5:
	return err;
}
