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
	printf("./unlink <file to write to>\n");
}

int main(int argc, char * const argv[]) {
	char *path;
	int err;
	if(argc!=2) {
		print_usage();
		exit(0);
	}
	path = argv[1];
	err = unlink(path);
	if(err) {
		printf("unlink returned error : %d (errno : %d)\n", err, errno);
                perror("SYSCALL ERROR ");
	}else {
		printf("succesfull\n");
	}
return 0;
}
