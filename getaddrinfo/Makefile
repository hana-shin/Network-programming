obj-m := netlink_module.o

KDIR    := /lib/modules/$(shell uname -r)/build
VERBOSE = 0

all:
	gcc -Wall -o getaddrinfo getaddrinfo.c
clean:
	rm -f getaddrinfo
