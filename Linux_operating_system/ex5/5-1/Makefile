ifneq ($(KERNELRELEASE),) 
		obj-m := device_driver.o
else
KERNELDIR ?= /usr/lib/modules/$(shell uname -r)/build 
PWD := $(shell pwd)
default: 
		$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif 
clean:
		$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
