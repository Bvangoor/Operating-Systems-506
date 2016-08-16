obj-m += sys_submitjob.o
INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: submitjob sys_submitjob

submitjob: submitjob.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi submitjob.c -o submitjob -lcrypto -lssl

sys_submitjob:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f submitjob
