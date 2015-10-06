obj-m += sys_xcrypt.o

INC=/lib/modules/$(shell uname -r)/build/arch/x86/include

all: xhw1 xcrypt

xhw1: xCipher.c
	gcc -Wall -Werror -I$(INC)/generated/uapi -I$(INC)/uapi xCipher.c -o xCipher -lcrypto -lssl

xcrypt:
	make -Wall -Werror -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f xCipher
