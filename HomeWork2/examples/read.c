#include <asm/unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/syscall.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>

void print_usage() {
	printf("./read <path to read from>\n");
}

int main(int argc, char * const argv[]) {
	char *path, buffer[4097];
	int file_desc, len=4096;
	if(argc!=2) {
		print_usage();
		exit(0);
	}
	path = argv[1];
	file_desc = open(path, O_RDONLY);
	if (file_desc < 0) {
		printf("Can't open the device\n");
		perror("SYSCALL ERROR ");
		exit(-1);
	}
	while(len==4096) {
		len = read(file_desc, buffer, 4096);
		if(len<0) {
			printf("read returned error : %d (errno : %d)\n", len, errno);
			perror("SYSCALL ERROR ");
			close(file_desc);
			exit(len);
		}
		buffer[len]='\0';
		printf("Data Read : %s\n", buffer);
	}
	close(file_desc);
return 0;
}
