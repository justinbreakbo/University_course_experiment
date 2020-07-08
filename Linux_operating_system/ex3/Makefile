# Makefile 4.0
obj-m :=3-4-2.o
CURRENT_PATH := $(shell pwd)
LINUX_KERNEL_PATH := /usr/lib/modules/5.4.31-1-MANJARO/build

all:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) modules
clean:
	make -C $(LINUX_KERNEL_PATH) M=$(CURRENT_PATH) clean
