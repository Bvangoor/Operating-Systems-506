#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>
#include <ctype.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <fcntl.h>
#include "arguments.h"

#ifndef __NR_submitjob
#error submitjob system call not defined
#endif

static void hexdump(unsigned char *buf, unsigned int len)
{
        while (len--)
                printf("%02x", *buf++);

        printf("\n");
}

#define NETLINK_USER 31

#define MAX_PAYLOAD 1024 /* maximum payload size*/
struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;
struct msghdr msg;

void printmillionnumbers() {
	int i;
	for (i=1;i<=1000000;i++)
		printf("%d ", i);
	printf("\n");
}


void print_args(struct arguments* temp) {
        printf("unique code : %d\n", temp->unique_code);
        printf("operation type : %d\n", temp->operation_type);
        printf("input file name : %s\n", temp->input_file_name);
        printf("output file name : %s\n", temp->output_file_name);
        printf("algorithm name : %s\n", temp->algorithm_name);
        printf("password : "); hexdump((unsigned char*)temp->pass_phrase, strlen(temp->pass_phrase));
        printf("delete orig file : %d\n", temp->delete_orig_file);
	printf("Process ID : %d\n", temp->pid);
}

struct arguments* allocate_arguments(int input_file_len, int output_file_len, int algorithm_len, int pass_phrase_len) {
        struct arguments *temp=NULL;
        temp=(struct arguments*)malloc(sizeof(struct arguments));
        if(!temp) {
                printf("Failed to allocate space\n");
                return NULL;
        }
        temp->input_file_name=NULL;
        if(input_file_len>0) {
                temp->input_file_name=(char *)malloc((input_file_len+1)*sizeof(char));
                if(!temp->input_file_name) {
                        printf("Failed to allocate space\n");
                        return NULL;
                }
        }
        temp->output_file_name=NULL;
        if(output_file_len>0) {
                temp->output_file_name=(char *)malloc((output_file_len+1)*sizeof(char));
                if(!temp->output_file_name) {
                        printf("Failed to allocate space\n");
                        return NULL;
                }
        }
        temp->algorithm_name=NULL;
        if(algorithm_len>0) {
                temp->algorithm_name=(char *)malloc((algorithm_len+1)*sizeof(char));
                if(!temp->algorithm_name) {
                        printf("Failed to allocate space\n");
                        return NULL;
                }
        }
        temp->pass_phrase=NULL;
        if(pass_phrase_len>0) {
                temp->pass_phrase=(char *)malloc((pass_phrase_len+1)*sizeof(char));
                if(!temp->pass_phrase) {
                        printf("Failed to allocate space\n");
                        return NULL;
                }
        }
        return temp;
}

void free_arguments(struct arguments *temp) {
        if(!temp)
                return ;
        if(temp->pass_phrase)
                free(temp->pass_phrase);
        if(temp->algorithm_name)
                free(temp->algorithm_name);
        if(temp->output_file_name)
                free(temp->output_file_name);
        if(temp->input_file_name)
                free(temp->input_file_name);
        if(temp)
                free(temp);
}

void print_usage() {
        printf("Usage:  submitjob -t \"operation\" -i <inputfile(s)> -o <outputfile> -n \"algorithms name\" -p \"passwordKey\" -e <extraflag> -u <unique code> -k <position>\n");
	printf("	-o	To specify the operation to be submited <encryption, decryption, list, remove, reorder>\n");
	printf("	-i	input file\n");
	printf("	-o	output file \n");
	printf("	-n	algorithm name (ex: AES, MD5)(Suppoted only CBC(AES))\n");
	printf("	-p	password key \n");
	printf("	-e	extra flags (1 for delete/overwrite inputfile)(Not supported No effect)\n");
	printf("	-u	unique code (used only in case of remove job)\n");
	printf("        -k      position to change (used only in case of reorder job)\n");
	printf("Recomended options : \n");
	printf("encryption :	submitjob -t \"encrypt\" -i <inputfile> [-o] <outputfile> -n <algorithm name> -p \"passwordkey\" [-e]\n");
	printf("decryption :	submitjob -t \"decrypt\" -i <inputfile> [-o] <outputfile> -n <algorithm name> -p \"passwordkey\" [-e]\n");
	printf("list the jobs : submitjob -t \"list\" \n");
	printf("remove the job : submitjob -t \"remove\" -u <unique id of job to remove> \n");
	printf("reorder the job : submitjob -t \"reorder\" -u <unique id of job to remove> -k <position to change>\n");
}

int check_operation(char *optarg) {
	if(strcmp(optarg, STR_ENCRYPTION)==0)
		return 1;
	if(strcmp(optarg, STR_DECRYPTION)==0)
		return 2;
	if(strcmp(optarg, STR_LIST_JOBS)==0)
		return 5;
	if(strcmp(optarg, STR_REMOVE_JOB)==0)
		return 6;
	if(strcmp(optarg, STR_REORDER_JOB)==0)
                return 7;
	return -1;
}

int main(int argc, char * const argv[])
{
	int rc, argslen, operation_type=0, unique_code=0, delete_orig_file=0, option=0, input_file_len=0, output_file_len=0, algorithm_len=0, pass_phrase_len=0, flags, rat=-1, pos = 0; 
	char *input_file_name=NULL, *output_file_name=NULL, *algorithm_name=NULL, *pass_phrase=NULL, *temp_output_file_name=NULL;
	struct jobs_list *list=NULL;
	while ((option = getopt(argc, argv,"ht:i:o:n:p:u:k:e")) != -1) {
		switch (option) {
			case 'h' :
				print_usage();
				exit(EXIT_FAILURE);
                    		break;
			case 't' :
				operation_type = check_operation(optarg);
				if(operation_type == -1) {
					printf("Operation Not Supported\n");
					print_usage();
                                	exit(EXIT_FAILURE);
				}
                                break;
			case 'i' :
				input_file_name = optarg;
				break;
			case 'o' :
				output_file_name = optarg;
				break;
			case 'n' :
				algorithm_name = optarg;
				break;
			case 'p' :
				pass_phrase = optarg;
				break;
			case 'e' :
				delete_orig_file = 1;
				break;
			case 'u' :
				unique_code = atoi(optarg);
				break;
			case 'k' :
				pos = atoi(optarg);
				break;
			case '?' :
                    		if (optopt == 't' || optopt == 'i' || optopt == 'o' || optopt == 'n' || optopt == 'p')
                        		fprintf (stderr, "Option -%c requires arguments.\n", optopt);
                    		else if (isprint (optopt))
                        		fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                    		else
                        		fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
                    			print_usage();
                    			return 1;
                	default:
                    		print_usage();
                    		exit(EXIT_FAILURE);
		}
	}
//	printf("operation : %d\n", operation_type);
	if (operation_type == 0) {
		print_usage();
		exit(EXIT_FAILURE);
	}
	if (!input_file_name) {
		if(operation_type!=5 && operation_type!=6 && operation_type!=7) {
			printf("Provide an input file\n");
			print_usage();
                	exit(EXIT_FAILURE);
		}
	}
	
	if (!output_file_name) {
		if(operation_type!=5 && operation_type!=6 && operation_type!=7) {
			if(delete_orig_file!=1) {
				printf("Provide an output file or enable overide option\n");
                        	print_usage();
                        	exit(EXIT_FAILURE);
			}
                }
	}
	
	if (!algorithm_name) {
		if (operation_type!=5 && operation_type!=6 && operation_type!=7) {
			printf("algorithm name required for this operation\n");
			print_usage();
                	exit(EXIT_FAILURE);
		}
	}
	
	if (!pass_phrase) {
		if (operation_type==1 || operation_type==2) {
			printf("password required for this operation\n");
			print_usage();
                	exit(EXIT_FAILURE);
		}
	}
	
	if (unique_code==0) {
		if (operation_type==6||operation_type==7) {
			printf("provide unique code to remove/reorder that task\n");
                        print_usage();
                        exit(EXIT_FAILURE);
		}
	}
	if (pos==0) {
		if (operation_type==7) {
                        printf("provide position to reorder that task starting with 1.\n");
                        print_usage();
                        exit(EXIT_FAILURE);
                }
	}
	if((pass_phrase)&&(strlen(pass_phrase)<6)) {
        	printf("Password key should be atleast 6 characters long\n");
            	rc = -1;
		exit(rc);
        }


	if ((!output_file_name)&&(operation_type!=5)&&(operation_type!=6)&&(delete_orig_file==1)&&(operation_type!=7)) {
                temp_output_file_name = (char *)malloc((strlen(input_file_name)+5)*sizeof(char));
		if(!temp_output_file_name) {
			printf("failed to allocate memory\n");
			goto out;
		}
		strncpy(temp_output_file_name, input_file_name, strlen(input_file_name));
               	strcat(temp_output_file_name, ".tmp");
               	temp_output_file_name[(strlen(input_file_name)+5)]='\0';
               	output_file_name = temp_output_file_name;
         }

	if(input_file_name)
		input_file_len=strlen(input_file_name);
	if(output_file_name)
		output_file_len=strlen(output_file_name);
	if(algorithm_name)
		algorithm_len=strlen( algorithm_name );
	if(pass_phrase)
		pass_phrase_len=MD5_DIGEST_LENGTH;
	
	struct arguments *args=NULL;
	args = allocate_arguments(input_file_len, output_file_len, algorithm_len, pass_phrase_len);
	if (!args) {
		printf("Failed to allocare space for arguments\n");
		rc=-1;
		goto out;
	}
	if(input_file_name)
		strcpy(args->input_file_name, input_file_name);
	if(output_file_name)
		strcpy(args->output_file_name, output_file_name);
	if(algorithm_name)
		strcpy(args->algorithm_name, algorithm_name);
	if(pass_phrase) {
		MD5((unsigned char*)pass_phrase, strlen(pass_phrase), (unsigned char*)(args->pass_phrase));
		args->pass_phrase[MD5_DIGEST_LENGTH] = '\0';
	}
//	printf("passphrase : %s and len : %d MD5_DIGEST_LENGTH : %d\n", args->pass_phrase, strlen(args->pass_phrase), MD5_DIGEST_LENGTH);
	args->unique_code = unique_code;
	args->position = pos;
	args->operation_type=operation_type;	
	args->delete_orig_file=delete_orig_file;
	args->pid = getpid();
//	print_args(args);	
	if(args->operation_type==5) { /*List the jobs*/
		printf("list the jobs\n");
		int i = 1;
		list = (struct jobs_list*)malloc(sizeof(struct jobs_list));
		if(!list) {
			printf("failed to allocate space for list\n");
			rc = -1;
			goto out; //TODO CLEANUP
		}
		list->count = 0;
		args->list = (void*)list;
		argslen = 10;
                void *dummy = (void *) args;
                rc = syscall(__NR_submitjob, dummy, argslen);
                if (rc == 0)
                        printf("syscall returned %d\n", rc);
		else {
			printf("syscall returned %d (errno=%d)\n", rc, errno);
                        perror("SYSCALL ERROR ");
			goto out;
		}
		//printf("list count obtained from kernel : %d\n", list->count);
		//printf("pid obtained from kernel : %d\n", ((struct jobs_list*)(args->list))->pid[0]);
		if(list->count==0) {
			printf("No Pending Jobs to print\n");
		} else {
			printf("Process ID	Unique ID	Job Type\n");
			printf("----------------------------------------\n");
			while (i<=list->count) {
				printf("%d		%d		%s\n", list->pid[i], list->uid[i], (list->Jid[i]==1)?(STR_ENCRYPTION):(STR_DECRYPTION));
				i++;
			}
		}
		
	} else if (args->operation_type==6) { /*Remove the job*/
		printf("remove job called with unique id %d \n", args->unique_code);
		argslen = 10;
                void *dummy = (void *) args;
                rc = syscall(__NR_submitjob, dummy, argslen);
                if (rc == 0)
                        printf("Job removed successfully\n");
                else {
                        printf("syscall returned %d (errno=%d)\n", rc, errno);
                        perror("SYSCALL ERROR ");
                        goto out;
                }
	} else if (args->operation_type==7) { /*change the priority*/
		printf("reorder the job with unique id %d to poistion %d\n", args->unique_code, args->position);
                argslen = 10;
                void *dummy = (void *) args;
                rc = syscall(__NR_submitjob, dummy, argslen);
                if (rc == 0)
                        printf("Job reordered successfully\n");
                else {
                        printf("syscall returned %d (errno=%d)\n", rc, errno);
                        perror("SYSCALL ERROR ");
                        goto out;
                }
	} else {
		sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    		if (sock_fd < 0) {
        		rc = -1;
			goto out;
		}


	/* Set socket to non-blocking */ 

		if ((flags = fcntl(sock_fd, F_GETFL, 0)) < 0) { 
    			/* Handle error */ 
			printf("Error in setting socket to non-blocking\n");
			goto out;
		}	 


		if (fcntl(sock_fd, F_SETFL, flags | O_NONBLOCK) < 0) { 
    			/* Handle error */ 
			printf("Error in setting socket to non-blocking\n");
                	goto out;
		} 

		memset(&src_addr, 0, sizeof(src_addr));
    		src_addr.nl_family = AF_NETLINK;
    		src_addr.nl_pid = getpid();

    		bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

        	memset(&dest_addr, 0, sizeof(dest_addr));
        	dest_addr.nl_family = AF_NETLINK;
        	dest_addr.nl_pid = 0; /* For Linux Kernel */
        	dest_addr.nl_groups = 0; /* unicast */
    		nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
		memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
        	nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
        	nlh->nlmsg_pid = getpid();
        	nlh->nlmsg_flags = 0;

	        iov.iov_base = (void *)nlh;
	        iov.iov_len = nlh->nlmsg_len;
       		msg.msg_name = (void *)&dest_addr;
        	msg.msg_namelen = sizeof(dest_addr);
        	msg.msg_iov = &iov;
		msg.msg_iovlen = 1;

		argslen = 10;
		void *dummy = (void *) args;
  		rc = syscall(__NR_submitjob, dummy, argslen);
		if (rc == 0)
			printf("syscall returned %d\n", rc);
		else if (rc > 0) {
			printf("Job with unique code : %d submitted successfuly\n", rc);
		} else {
			printf("Job failed to submit\n");
			printf("syscall returned %d (errno=%d)\n", rc, errno);
			perror("SYSCALL ERROR ");
			goto out;
		}
		while(rat==-1) {
			printf("Doing some thing lets say printing million numbers\n");
//		printmillionnumbers();
			sleep(1);
			rat = recvmsg(sock_fd, &msg, 0);
		}
//	printf("received value : %d\n", recvmsg(sock_fd, &msg, 0));
		rc = *(int*)NLMSG_DATA(nlh);
		errno = -rc;
//    	printf("Received message payload: %d\n", rc);
    		close(sock_fd);
		if (rc == 0)	
			printf("Job execution returned : %d\n", rc);
		else {
			printf("syscall returned %d (errno=%d)\n", rc, errno);
                	perror("SYSCALL ERROR ");
		}
	}
	
out:
	if(nlh)
		free(nlh);
	if(temp_output_file_name)
		free(temp_output_file_name);
	if(list)
		free(list);
	if(args)
		free_arguments(args);
	exit(rc);
}
