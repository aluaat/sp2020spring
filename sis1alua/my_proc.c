#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/jiffies.h>

static int my_proc_show(struct seq_file *m, void *v)
{
  seq_printf(m, "procedure by Aleka \n");
  return 0;
}

static int my_proc_open(struct inode *inode, struct file *file)
{
  return single_open(file, my_proc_show, NULL);
}

static const struct file_operations my_proc_fops = {
  .owner      = THIS_MODULE,
  .open       = hello_proc_open,
  .read       = seq_read,
  .llseek     = seq_lseek,
  .release    = single_release,
};

static int __init my_proc_init(void)
{
  printk(KERN_INFO "Create /proc/my_proc\n");
  proc_create("my_proc", 0, NULL, &my_proc_fops);
  return 0;
}

static void __exit my_proc_exit(void) {
  printk(KERN_INFO "Remove /proc/my_proc\n");
  remove_proc_entry("my_proc", NULL);
}



MODULE_AUTHOR("Aluaat");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Virtual file systems");
module_init(my_proc_init);
module_exit(my_proc_exit);