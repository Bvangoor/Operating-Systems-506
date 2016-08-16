#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#define ENCRYPTION	1
#define STR_ENCRYPTION	"encrypt"

#define DECRYPTION	2
#define STR_DECRYPTION	"decrypt"

#define COMPRESSION	3
#define STR_COMPRESSION	"compress"

#define DECOMPRESSION	4
#define STR_DECOMPRESS	"decompress"

#define LIST_JOBS	5
#define STR_LIST_JOBS	"list"

#define REMOVE_JOB	6
#define STR_REMOVE_JOB	"remove"

#define REORDER_JOB 7
#define STR_REORDER_JOB "reorder"

#define MAX_JOBS 10


struct arguments {
	int unique_code; /*Some thing like process id*/
	
	int operation_type; /*encryption, decryption, compression, decompression, list jobs, remove job*/

	char *input_file_name; /*can be more than one*/

	char *output_file_name; /*output file*/

	char *algorithm_name;   /*cipher name, compression name, checksum name for encryption, compression, checksum*/

	char *pass_phrase;  /*pass key used in ecryption/decryption*/

	int delete_orig_file;  /*flag to delete input file*/
	
	int pid; /*Process ID for kernel to know which one called*/
	
	int position; /*for passing position to reorder the job*/

	void *list; /*extensibility for list operations*/
};

struct jobs_list {
	int pid[MAX_JOBS];
	int uid[MAX_JOBS];
	int Jid[MAX_JOBS];
	int count;
};



extern void print_args(struct arguments* );

extern struct arguments* allocate_arguments(int, int, int, int);

extern void free_arguments(struct arguments *);

#endif
