#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>

static int irq;        // 模块参数-中断号
static char* interface;    // 模块参数-设备名
static int count = 0;   // 统计插入模块期间发生的中断次数

module_param(interface, charp, 0644);
module_param(irq, int, 0644);

static irqreturn_t intr_handler(int irq, void* dev_id)
{
	static long interval = 0;
	if(count == 0){
		interval = jiffies;
	}
	interval = jiffies - interval;     // 计算两次中断之间的间隔，时间单位为节拍
	printk("The interval between two interrupt is %ld\n", interval);
	interval = jiffies;
	count++;        
	return IRQ_NONE;
}

static int intr_init(void)
{
	if(request_irq(irq, &intr_handler, IRQF_SHARED, interface, &irq)){
		printk("Fails to register IRQ %d\n", irq);
		return -EIO;
	}
	printk("%s Request on IRQ %d success\n", interface,irq);
	return 0;
}

static void intr_exit(void)
{
	printk("The %d interrupts happened on irq %d\n", count, irq);
	free_irq(irq, &irq);        // 释放中断线
	printk("Freeing IRQ %d\n", irq);
	return;
}

module_init(intr_init);
module_exit(intr_exit);
MODULE_LICENSE("GPL");
