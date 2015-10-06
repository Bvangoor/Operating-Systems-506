#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <openssl/md5.h>
#include <openssl/sha.h>
#ifndef __NR_xcrypt
#error xcrypt system call not defined
#endif

struct myargs {
	char *inputFile;
	char *outputFile;
	char *keyBuf;
	int flags;
	int keyLen;
};

void print_usage() {
	printf("Usage: xCipher -p \"passwordKey\" -e|-d <inputfile> <outputfile>\n");
}

/*static void
hexdump(unsigned char *buf, unsigned int len)
{
	while (len--)
		printf("%02x", *buf++);

	printf("\n");
}*/


int main(int argc, char * const argv[])
{
	int encryptFlag=-1, option=0 , inputFileLen, outputFileLen, rc=0;
	char *passwd=NULL, *inputFile=NULL, *outputFile=NULL;
	while ((option = getopt(argc, argv,"hp:e:d:")) != -1) {
            switch (option) {
                case 'h' :
		    print_usage();
		    exit(EXIT_FAILURE);
                    break;
                case 'p' :
		    if (argc > 2)
		        passwd = optarg;
                    break;
                case 'e' :
		    encryptFlag=1;
		    if (argc > 4)
		        inputFile=optarg;
		    if (argc > 5) 
		        outputFile=argv[optind];
                    break;
                case 'd' :
		    encryptFlag=0;
		    if (argc > 4)
		        inputFile=optarg;
		    if (argc > 5)
                        outputFile=argv[optind];
                    break;
		case '?':
                    if (optopt == 'e' || optopt == 'd' || optopt == 'p')
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
	if (argc != 6) {
	    print_usage();
	    exit(EXIT_FAILURE);
	}
        if(strlen(passwd)<6) {
	    printf("Password key should be atleast 6 characters long\n");
	    rc = -1;
	    goto out1;
        }
	if(strcmp(inputFile, "NULL") == 0) {
	    printf("input file is NULL\n");
	    rc = -1;
	    goto out1;
	}
	inputFileLen = strlen(inputFile);
	if(strcmp(outputFile, "NULL") == 0) {
            printf("output file is NULL\n");
            rc = -1;
            goto out1;
        }
	outputFileLen = strlen(outputFile);
	struct myargs *arguments;
	arguments = malloc(sizeof(struct myargs));
	if(arguments==NULL) {
	    printf("Failed to allocate memory\n");
	    rc = -1;
	    goto out1;
	}	
	arguments->inputFile = malloc((inputFileLen+1)*sizeof(char));
	if ((arguments->inputFile)==NULL) {
	    printf("Failed to allocate memory\n");
            rc = -1;
            goto out2;
	}
	arguments->outputFile = malloc((outputFileLen+1)*sizeof(char));
	if ((arguments->outputFile)==NULL) {
	    printf("Failed to allocate memory\n");
            rc = -1;
            goto out3;
	}
	arguments->keyBuf = malloc((MD5_DIGEST_LENGTH+1)*sizeof(char));
	if((arguments->keyBuf)==NULL) {
	    printf("Failed to allocate memory\n");
            rc = -1;
            goto out4;
	}
	strcpy(arguments->inputFile, inputFile);
	if((arguments->inputFile)==NULL) {
	    printf("Input file is NULL(userlevel)\n");
            rc = -1;
            goto out5;
	}
	strcpy(arguments->outputFile, outputFile);
	if((arguments->outputFile)==NULL) {
            printf("output file is NULL(userlevel)\n");
            rc = -1;
            goto out5;
        }
	arguments->flags = encryptFlag;

        MD5((unsigned char*)passwd, strlen(passwd), (unsigned char*)(arguments->keyBuf));

	if ((arguments->keyBuf)==NULL) {
	    printf("NULL Value generated for MD5 password(userlevel)\n");
	    rc = -1; 
	    goto out5;
	}
	else {
	    arguments->keyLen = strlen(arguments->keyBuf);
	}
	void *dummy = (void *)(arguments);
  	rc = syscall(__NR_xcrypt, dummy);
	if (rc == 0)
	    printf("syscall returned %d\n", rc);
	else {
	    printf("syscall returned %d (errno=%d)\n", rc, errno);
	    perror("SYSCALL ERROR ");
	}

out5:   
	if(arguments && arguments->keyBuf)
	    free(arguments->keyBuf);
out4:
	if(arguments && arguments->outputFile)
	    free(arguments->outputFile);
out3:
	if(arguments && arguments->keyBuf)
	    free(arguments->inputFile);
out2:
	if(arguments)
	    free(arguments);
out1:
	exit(rc);
}
