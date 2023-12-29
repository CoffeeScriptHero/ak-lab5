#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/printk.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Denys Kozarenko");
MODULE_DESCRIPTION("Module prints hello world");
MODULE_LICENSE("Dual BSD/GPL");

static unsigned int num = 1;
module_param(num, uint, 0644);
MODULE_PARM_DESC(num, "counter of 'Hello world' printing");

static int __init hello2_init(void)
{
	if (num > 10) {
		BUG();
	}
	else if (num == 0 || (num >= 5 && num <= 10))
		pr_warn("num is 0 or in range [5, 10]\n");

	print_hello(num);

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Second module is uninstalled\n");
}

module_init(hello2_init);
module_exit(hello2_exit);


