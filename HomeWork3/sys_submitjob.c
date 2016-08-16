#include <linux/linkage.h>
#include <linux/moduleloader.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/kthread.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/skbuff.h>
#include "arguments.h"
#include "file_operations.h"
#include "lists.h"
#include "encryption_decryption.h"

#define NETLINK_USER 31

struct sock *nl_sk = NULL;

static struct task_struct *thread1;

long int unique_code;

asmlinkage extern long (*sysptr)(void *arg, int argslen);

static void hexdump(unsigned char *buf, unsigned int len)
{
        while (len--)
                printk("%02x", *buf++);
        printk("\n");
}


void print_args(struct arguments* temp) {
        printk("unique code : %d\n", temp->unique_code);
        printk("operation type : %d\n", temp->operation_type);
        printk("input file name : %s\n", temp->input_file_name);
        printk("output file name : %s\n", temp->output_file_name);
        printk("algorithm name : %s\n", temp->algorithm_name);
        printk("password : "); hexdump(temp->pass_phrase, strlen(temp->pass_phrase));
        printk("delete orig file : %d\n", temp->delete_orig_file);
}

struct arguments* allocate_arguments(int input_file_len, int output_file_len, int algorithm_len, int pass_phrase_len) {
        struct arguments *temp=NULL;
        temp=(struct arguments*)kmalloc(sizeof(struct arguments), GFP_KERNEL);
        if(!temp) {
                printk("Failed to allocate space\n");
                return NULL;
        }
        temp->input_file_name=NULL;
        if(input_file_len>0) {
                temp->input_file_name=(char *)kmalloc((input_file_len)*sizeof(char), GFP_KERNEL);
                if(!temp->input_file_name) {
                        printk("Failed to allocate space\n");
                        return NULL;
                }
        }
        temp->output_file_name=NULL;
        if(output_file_len>0) {
                temp->output_file_name=(char *)kmalloc((output_file_len)*sizeof(char), GFP_KERNEL);
                if(!temp->output_file_name) {
                        printk("Failed to allocate space\n");
                        return NULL;
                }
        }
        temp->algorithm_name=NULL;
        if(algorithm_len>0) {
                temp->algorithm_name=(char *)kmalloc((algorithm_len)*sizeof(char), GFP_KERNEL);
                if(!temp->algorithm_name) {
                        printk("Failed to allocate space\n");
                        return NULL;
                }
        }
        temp->pass_phrase=NULL;
        if(pass_phrase_len>0) {
                temp->pass_phrase=(char *)kmalloc((pass_phrase_len)*sizeof(char), GFP_KERNEL);
                if(!temp->pass_phrase) {
                        printk("Failed to allocate space\n");
                        return NULL;
                }
        }
        return temp;
}

void free_arguments(struct arguments *temp) {
        if(!temp)
                return ;
        if(temp->pass_phrase) {
		printk("freeing pass phrase\n");
                kfree(temp->pass_phrase);
	}
        if(temp->algorithm_name) {
		printk("freeing algorithm\n");
                kfree(temp->algorithm_name);
	}
        if(temp->output_file_name) {
		printk("freeing output file\n");
                kfree(temp->output_file_name);
	}
        if(temp->input_file_name) {
		printk("freeing input file\n");
                kfree(temp->input_file_name);
	}
        if(temp) {
		printk("freeing main data\n");
                kfree(temp);
	}
}

asmlinkage long submitjob(void *arg, int argslen)
{
	if (arg == NULL) {
		printk("user passed NULL argument\n");
		return -EINVAL;
	}
	else {
		struct arguments *arguments=NULL;
		struct jobs_list *list=NULL;
		struct node *temp;
		int err=0, result=0, input_file_len=0, output_file_len=0, algorithm_len=0, pass_phrase_len=0;

		if(((struct arguments *)arg)->operation_type==1 || ((struct arguments *)arg)->operation_type==2) {		
			if (((struct arguments *)arg)->input_file_name == NULL) {
				printk("user level input file argument is NULL\n");
            			err = -EINVAL;
				goto out;
			} else {
				input_file_len = strnlen_user(((struct arguments*)arg)->input_file_name, 32767); //TODO get the maximum value from getname 
			}

			if (((struct arguments *)arg)->output_file_name) {
				output_file_len = strnlen_user(((struct arguments*)arg)->output_file_name, 32767);
			}
		
			if (((struct arguments *)arg)->algorithm_name) {
                        	algorithm_len = strnlen_user(((struct arguments*)arg)->algorithm_name, 32767);
                	}

			if (((struct arguments *)arg)->pass_phrase) {
                        	pass_phrase_len = strnlen_user(((struct arguments*)arg)->pass_phrase, 32767);
                	}
		}
		arguments = (struct arguments*)kmalloc(sizeof(struct arguments), GFP_KERNEL);
		if(!arguments) {
			printk("Failed to allocate space \n");
			err = -ENOMEM;
			goto out;
		}
		result = copy_from_user((void *)arguments, arg, sizeof(struct arguments));
        	if(result!=0) {
            		printk("Copying from user failed\n");
            		err = -EFAULT;
            		goto out;
        	}
		
		if(input_file_len) {
			arguments->input_file_name = (char *)kmalloc(input_file_len*sizeof(char), GFP_KERNEL);
        		if ((arguments->input_file_name)==NULL) {
            			printk("Failed to allocate kernel memory for input file\n");
            			err = -ENOMEM;
            			goto out;
        		}
        		result = strncpy_from_user(arguments->input_file_name, ((struct arguments*)arg)->input_file_name, input_file_len);
        		if(result!=(input_file_len-1)) {
            			printk("Copying input file string from user failed\n");
            			err = -EFAULT;
            			goto out;
        		}
        		if((arguments->input_file_name)==NULL) {
            			printk("Copying input file string from user failed\n");
            			err = -EFAULT;
            			goto out;
        		}
		}
		
		if(output_file_len) {
			arguments->output_file_name = (char *)kmalloc(output_file_len*sizeof(char), GFP_KERNEL);
        		if ((arguments->output_file_name)==NULL) {
            			printk("Failed to allocate kernel memory for outputfile\n");
            			err = -ENOMEM;
            			goto out;
        		} 
        		result = strncpy_from_user(arguments->output_file_name, ((struct arguments*)arg)->output_file_name, output_file_len);
        		if(result!=(output_file_len-1)) {
            			printk("Copying output file string from user failed\n");
            			err = -EFAULT;
            			goto out;
        		}
        		if((arguments->output_file_name)==NULL) {
            			printk("Copying output file string from user failed\n");
            			err = -EFAULT;
            			goto out;
        		}

                }

		if(algorithm_len) {
			arguments->algorithm_name = (char *)kmalloc(algorithm_len*sizeof(char), GFP_KERNEL);
                        if ((arguments->algorithm_name)==NULL) {
                        	printk("Failed to allocate kernel memory for outputfile\n");
                                err = -ENOMEM;
                                goto out;
                        } 
                        result = strncpy_from_user(arguments->algorithm_name, ((struct arguments*)arg)->algorithm_name, algorithm_len);
                        if(result!=(algorithm_len-1)) {
                                printk("Copying output file string from user failed\n");
                                err = -EFAULT;
                                goto out;
                        }
                        if((arguments->algorithm_name)==NULL) {
                                printk("Copying output file string from user failed\n");
                                err = -EFAULT;
                                goto out;
                        }
                }

		if(pass_phrase_len) {
			arguments->pass_phrase = (char *)kmalloc(pass_phrase_len*sizeof(char), GFP_KERNEL);
        		if ((arguments->pass_phrase)==NULL) {
            			printk("Failed to allocate kernel memory\n");
            			err = -ENOMEM;
            			goto out;	
        		}
        		result = strncpy_from_user(arguments->pass_phrase, ((struct arguments*)arg)->pass_phrase, pass_phrase_len);
        		if(result!=(pass_phrase_len-1)) {
            			printk("Copying key buf string from user failed\n");
            			err = -EFAULT;
            			goto out;
        		}
        		if((arguments->pass_phrase)==NULL) {
            			printk("Copying key buf string from user failed\n");
            			err = -EFAULT;
            			goto out;
        		}

                }
//		print_args(arguments);
		if (arguments->operation_type==5) { /*list the jobs*/
			struct node* temp=NULL;
			int i = 1;
			printk("List operations called\n");
			list = (struct jobs_list*)kmalloc(sizeof(struct jobs_list), GFP_KERNEL);
	                if(!list) {
        	                printk("Failed to allocate space \n");
                	        err = -ENOMEM;
                        	goto out1;
                	}
			err = copy_from_user((void *)list, (void *)arguments->list, sizeof(struct jobs_list));
                	if(err){
                        	printk("copy from user failed\n");
                        	goto out1;
                	}
/*			for(i=1;i<=5;i++) {
				list->pid[i]=1234;
				list->uid[i]=i;
				list->Jid[i]=i%2;
				put_user(list->pid[i], &(((struct jobs_list*)(arguments->list))->pid[i]));
				put_user(list->uid[i], &(((struct jobs_list*)(arguments->list))->uid[i]));
				put_user(list->Jid[i], &(((struct jobs_list*)(arguments->list))->Jid[i]));
			}
			list->count = 5;
			put_user(list->count, &(((struct jobs_list*)(arguments->list))->count)); */
			mutex_lock(&list_lock);
			temp = head;
			while(temp!=NULL) {
				put_user(temp->job->pid, &(((struct jobs_list*)(arguments->list))->pid[i]));
				put_user(temp->job->unique_code, &(((struct jobs_list*)(arguments->list))->uid[i]));
				put_user(temp->job->operation_type, &(((struct jobs_list*)(arguments->list))->Jid[i]));				
				temp = temp->next;
				i++;
			}
			list->count = counter;
                        put_user(list->count, &(((struct jobs_list*)(arguments->list))->count));
			mutex_unlock(&list_lock);
out1:
			free_arguments(arguments);
			if (list)
				kfree(list);
			return err;
		} else if (arguments->operation_type==6) { /*remove the job*/
			printk("Removing the Job\n");
			mutex_lock(&list_lock);
			err = delete_job(&head, arguments->unique_code);
			if(err==0)
				counter--;
			mutex_unlock(&list_lock);
			return err;	
		} else if (arguments->operation_type==7) { /*change the priority*/
			printk("reordering the job\n");
			mutex_lock(&list_lock);
			if(counter==0)	
				err = -ENODATA;
			else if ((1 <= arguments->position) && (arguments->position<=counter))
				err = reorder_list(&head, arguments->position, arguments->unique_code);
			else
				err = -ENODATA;
			mutex_unlock(&list_lock);
			return err;
		} else {
			err = check_input_output_file(arguments);
			if(err) {
				printk("error in input output files\n");
				goto out;
			}
//		printk("PRODUCER BEFORE LOCK\n");
			mutex_lock(&list_lock);
//		printk("PRODUCER AFTER LOCK\n");
			if (counter>=MAX_JOBS) {
				err = -EBUSY;
				mutex_unlock(&list_lock);
				goto out;
			}
			temp = allocate_node();
			if (!temp) {
				printk("Error in allocating memory\n");
				mutex_unlock(&list_lock);
				err = -ENOMEM;
				goto out;
			}
			unique_code++;
			arguments->unique_code = unique_code;
			err = unique_code;
			temp->job = arguments;
			insert_node(&head, temp);
			counter++;
			if(counter==1)
				wake_up_process(thread1);  //TODO Remove this after testing
//		printk("PRODUCER BEFORE UNLOCK\n");
			mutex_unlock(&list_lock);
//		printk("PRODUCER AFTER UNLOCK\n");

out:
			if(err<0)
				free_arguments(arguments);
			return err;
		}
	}
	return 0;
}

int consumer_fn(void *dummy) {
	struct node *temp;
	int err;
	struct nlmsghdr *nlh;
        int pid;
        struct sk_buff *skb_out;
        int res;
//	printk(KERN_INFO "In consumer thread\n");
	while (true) {
		temp = NULL;
		if(kthread_should_stop()) {
			goto out;
		}
		mutex_lock(&list_lock);
		if (counter==0) {
			set_current_state(TASK_INTERRUPTIBLE);
			mutex_unlock(&list_lock);
//			printk("CONSUMER AFTER UNLOCK BEFORE SLEEP\n");
    			schedule();
//			printk("CONSUMER BEFORE LOCK AFTER AWAKE\n");
			mutex_lock(&list_lock);
//			printk("CONSUMER AFTER LOCK AFTER AWAKE\n");
		}
		if (kthread_should_stop()) {
//			printk("CONSUMER SHOULD STOP 2\n");
			mutex_unlock(&list_lock);
			goto out;
		}
		temp = get_head_of_list(&head);
		counter--;
//		printk("CONSUMER BEFORE UNLOCK\n");
		mutex_unlock(&list_lock);
//		printk("CONSUMER AFTER UNLOCK\n");
		if(temp) {
                        err = encrypt_decrypt(temp->job);
			printk("Job returned vale : %d\n", err);
                        delete_node(temp);
			pid = temp->job->pid;
			skb_out = nlmsg_new(sizeof(err), 0);
			if (!skb_out) {
                		printk(KERN_ERR "Failed to allocate new skb\n");
        		} else {
				nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, sizeof(err), 0);
        			NETLINK_CB(skb_out).dst_group = 0;
        			memcpy(nlmsg_data(nlh), &err, sizeof(err));
				printk("value in kernel : %d %d\n", *(int*)nlmsg_data(nlh), err);
        			res = nlmsg_unicast(nl_sk, skb_out, pid);
        			if (res < 0)
                			printk(KERN_INFO "Error while sending bak to user\n");
			}
                }
	}
out :
	return 0;
}


static void hello_nl_recv_msg(struct sk_buff *skb)
{

/*    	struct nlmsghdr *nlh;
    	int pid;
    	struct sk_buff *skb_out;
    	int msg_size;
    	char *msg = "Hello from kernel";
    	int res;

    	printk(KERN_INFO "Entering: %s\n", __FUNCTION__);

    	msg_size = strlen(msg);

    	nlh = (struct nlmsghdr *)skb->data;
    	printk(KERN_INFO "Netlink received msg payload: %s\n", (char *)nlmsg_data(nlh));
    	pid = nlh->nlmsg_pid;

    	skb_out = nlmsg_new(msg_size, 0);
    	if (!skb_out) {
        	printk(KERN_ERR "Failed to allocate new skb\n");
        	return;
    	}

    	nlh = nlmsg_put(skb_out, 0, 0, NLMSG_DONE, msg_size, 0);
    	NETLINK_CB(skb_out).dst_group = 0; 
    	strncpy(nlmsg_data(nlh), msg, msg_size);

    	res = nlmsg_unicast(nl_sk, skb_out, pid);
    	if (res < 0)
        	printk(KERN_INFO "Error while sending bak to user\n");*/
	printk("Net link called\n");
}

static int __init init_sys_submitjob(void)
{
	struct netlink_kernel_cfg cfg = {
    		.input = hello_nl_recv_msg,
	};
	char our_thread[9] = "consumer";
	unique_code=0;
	mutex_lock(&list_lock);
	head = NULL;
	counter = 0;
	mutex_unlock(&list_lock);
    	printk(KERN_INFO "creating consumer thread\n");
    	thread1 = kthread_create(consumer_fn, NULL, our_thread);
    	if((thread1)) {
        	printk(KERN_INFO "thread succefully created\n");
        } else {
		printk(KERN_INFO "thread creation failed\n");
		return -1;
	}
//	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, 0, hello_nl_recv_msg, NULL, THIS_MODULE);
	nl_sk = netlink_kernel_create(&init_net, NETLINK_USER, &cfg);

    	if (!nl_sk) {
        	printk(KERN_ALERT "Error creating socket.\n");
        	return -1;
    	}
	if (sysptr == NULL)
		sysptr = submitjob;
	printk("installed new sys_submitjob module\n");
	return 0;
}
static void  __exit exit_sys_submitjob(void)
{
	int ret;
	if (sysptr != NULL)
		sysptr = NULL;
 	ret = kthread_stop(thread1);
	mutex_lock(&list_lock);
	if (head)
		delete_entire_list(&head);
	mutex_unlock(&list_lock);
 	if(!ret)
  		printk(KERN_INFO "Consumer Thread stopped\n");	
	netlink_kernel_release(nl_sk);
	printk("removed sys_submitjob module\n");
}
module_init(init_sys_submitjob);
module_exit(exit_sys_submitjob);
MODULE_LICENSE("GPL");
