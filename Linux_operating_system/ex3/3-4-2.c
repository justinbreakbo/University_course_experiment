#include<linux/module.h>
#include<linux/init.h>
#include<linux/interrupt.h>
#include<linux/sched.h>
#include<linux/kernel.h>

static int pid;
module_param(pid,int,0644);

static int __init lkp_init(void)
{
	struct task_struct * p;
	struct vm_area_struct * temp;
	printk("The virtual memory areas(VMA)are:\n");
	p = pid_task(find_vpid(pid),PIDTYPE_PID);
	temp=p->mm->mmap;

	while(temp)
	{
		printk("start:%p\tend:%p\n",(unsigned long *)temp->vm_start,(unsigned long *)temp->vm_end);
		temp=temp->vm_next;
	}
	return 0;
}
static void __exit lkp_cleanup(void)
{
	printk("Unloading my module.\n");
	return;
}

module_init(lkp_init);
module_exit(lkp_cleanup);
MODULE_LICENSE("GPL");

