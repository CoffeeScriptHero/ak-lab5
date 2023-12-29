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

static LIST_HEAD(list_head);

void print_hello(unsigned int num)
{
	int i;

	for (i = 0; i < num; i++) {
		struct list_s *list_ex = kmalloc(sizeof(*list_ex), GFP_KERNEL);

		if (i == 2)
			list_ex = 0;

		list_ex->timestamp_start = ktime_get();
		pr_info("Hello, world!\n");
		list_ex->timestamp_end = ktime_get();
		list_add(&list_ex->list, &list_head);
	}
}
EXPORT_SYMBOL(print_hello);

static void __exit hello1_exit(void)
{
	struct list_s *list_ex, *temp;

	list_for_each_entry_safe(list_ex, temp, &list_head, list) {
		pr_info("Time : %lld\n", list_ex->timestamp_start);
		pr_info("Spent: %lld\n", ktime_to_ns(ktime_sub(list_ex->timestamp_end, list_ex->timestamp_start)));
		list_del(&list_ex->list);
		kfree(list_ex);
	}
}


module_exit(hello1_exit);
