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
	printf("./write <file to write to>\n");
}

int main(int argc, char * const argv[]) {
	char *path, buffer[4096];
	int file_desc, len=4096, s_len;
	if(argc!=2) {
		print_usage();
		exit(0);
	}
	path = argv[1];
	file_desc = open(path, O_WRONLY|O_CREAT, 0644);
	if (file_desc < 0) {
		printf("Can't open the device\n");
		perror("SYSCALL ERROR ");
		exit(-1);
	}
	strncpy(buffer, "Im good file", 4096);
	while(len==4096) {
		len = write(file_desc, buffer, strlen(buffer));
		if(len<0) {
			printf("write returned error : %d (errno : %d)\n", len, errno);
			perror("SYSCALL ERROR ");
			close(file_desc);
			exit(len);
		}
		printf("Data wrote : %s\n", buffer);
	}
	close(file_desc);
return 0;
}
