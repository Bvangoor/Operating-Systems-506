#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

void print_usage() {
        printf("Usage: ./amfsctl -l|-a|-r| \"newpatt\" <mountpoint>\n");
	printf("	-l	To List Known Patterns (-l <mountpoint>)\n");
	printf("	-a	To add new pattern (-a \"newpattern\" <mountpoint>)\n");
	printf("	-r	To remove an old pattern (-r \"oldpattern\" <mountpoint>)\n");
}

struct arguments {
        char *buffer;
        int position;
        int repeat;
};


int main(int argc, char * const argv[]) {
	char *mount_point=NULL, *patt=NULL;
	int val=0, option=0, err=0;
	while ((option = getopt(argc, argv,"hl:a:r:")) != -1) {
            switch (option) {
                case 'h' :
                    print_usage();
                    exit(EXIT_FAILURE);
                    break;
                case 'l' :
		    val = 1;
                    if (argc == 3)
                        mount_point = optarg;
                    break;
                case 'a' :
		    val = 2;
                    if (argc == 4) {
                        patt = optarg;
                        mount_point = argv[optind];
		    }		    
                    break;
                case 'r' :
		    val = 3;
                    if (argc == 4) {
                        patt = optarg;
                        mount_point = argv[optind];
		    }
                    break;			
                case '?':
                    if (optopt == 'l' || optopt == 'a' || optopt == 'r')
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
	if(mount_point==NULL && patt==NULL) {
		print_usage();
                exit(EXIT_FAILURE);
	}
	if ((argc == 1)||((val==1)&&(mount_point==NULL))||((val==2)&&((mount_point==NULL)||(patt==NULL)))||((val==3)&&((mount_point==NULL)||(patt==NULL)))) {
            print_usage();
            exit(EXIT_FAILURE);
        }
//	printf("value : %d mount point : %s pattern : %s\n", val, mount_point, patt);
	int file_desc=0;
	struct arguments *input;
	input = (struct arguments*)malloc(sizeof(struct arguments));
	if(input==NULL) {
            printf("Failed to allocate memory\n");
            err = -1;
            goto out1;
        }
	input->position=0;
	input->repeat=0;
	input->buffer = (char *)malloc(4096*sizeof(char));
	if((input->buffer)==NULL) {
            printf("Failed to allocate memory\n");
            err = -1;
            goto out2;
        }
//	printf("Position before : %d Repeat before %d\n", input->position, input->repeat);
	file_desc = open(mount_point, 0);
	if (file_desc < 0) {
		printf ("Can't open device file: %s\n", 
            		mount_point);
		err = -1;
		goto out3;
	}
	if(val==1) {
		input->repeat=1;
		while(input->repeat) {
	    		err = ioctl(file_desc, 21, input);
	    		if(err) {
				printf("ioctl returned %d (errno=%d)\n", err, errno);
				perror("SYSCALL ERROR ");
				goto out3;
	    		}
//	    		printf("Position after : %d Repeat after : %d\n", input->position, input->repeat);
	    		printf("%s\n", input->buffer);
		}
	} else if(val==2) {
		strncpy(input->buffer, patt, strlen(patt));
//		printf("pattern : %s %d\n", input->buffer, strlen(input->buffer));
		err = ioctl(file_desc, 22, input);
                if(err) {
                        printf("ioctl returned %d (errno=%d)\n", err, errno);
			perror("SYSCALL ERROR ");
                        goto out3;
                }
		if(input->repeat)
			printf("pattern added succesfully\n");
		else
			printf("error in adding pattern\n");
	} else if(val==3) {
		strncpy(input->buffer, patt, strlen(patt));
//                printf("pattern : %s %d\n", input->buffer, strlen(input->buffer));
		err = ioctl(file_desc, 23, input);
                if(err) {
                        printf("ioctl returned %d (errno=%d)\n", err, errno);
			perror("SYSCALL ERROR ");
                        goto out3;
                }
		if(input->repeat)
                        printf("pattern deleted succesfully\n");
                else
                        printf("error in deleting pattern\n");
	}
	close(file_desc);
	file_desc=0; 
out3:
	if(input->buffer)
	    free(input->buffer);
out2:
	if(input)
	    free(input);
out1:
	if(file_desc)
	    close(file_desc);
	exit(err);
return 0;
}
