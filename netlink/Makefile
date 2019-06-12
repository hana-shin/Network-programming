obj-m := netlink_module.o

KDIR    := /lib/modules/$(shell uname -r)/build
VERBOSE = 0

all:
	$(MAKE) -C $(KDIR) M=$(PWD) KBUILD_VERBOSE=$(VERBOSE) modules
clean:
	rm -f *.o *.ko *.mod.c Module.symvers modules.order
