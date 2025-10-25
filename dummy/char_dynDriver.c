#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h> // for copy_to_user, copy_from_user

#define DEVICE_NAME "simple_char"
#define BUFFER_SIZE 1024

static int major_number;
static char message[BUFFER_SIZE];
static short message_length;
static int device_open_count = 0;

// Function prototypes
static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char __user *, size_t, loff_t *);

static struct file_operations fops =
{
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release,
};

// Called when the module is loaded
static int __init simple_char_init(void)
{
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ALERT "SimpleChar failed to register a major number\n");
        return major_number;
    }
    printk(KERN_INFO "SimpleChar: registered with major number %d\n", major_number);
    return 0;
}

// Called when the module is unloaded
static void __exit simple_char_exit(void)
{
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "SimpleChar: unregistered successfully\n");
}

// Open device
static int dev_open(struct inode *inodep, struct file *filep)
{
    device_open_count++;
    printk(KERN_INFO "SimpleChar: Device opened %d time(s)\n", device_open_count);
    return 0;
}

// Read from device
static ssize_t dev_read(struct file *filep, char __user *buffer, size_t len, loff_t *offset)
{
    int errors = copy_to_user(buffer, message, message_length);
    if (errors == 0) {
        printk(KERN_INFO "SimpleChar: Sent %d characters to the user\n", message_length);
        return message_length; // Number of bytes read
    } else {
        printk(KERN_INFO "SimpleChar: Failed to send %d characters to the user\n", errors);
        return -EFAULT;
    }
}

// Write to device
static ssize_t dev_write(struct file *filep, const char __user *buffer, size_t len, loff_t *offset)
{
    if (len > BUFFER_SIZE) {
        printk(KERN_WARNING "SimpleChar: Message too long, truncating\n");
        len = BUFFER_SIZE;
    }
    copy_from_user(message, buffer, len);
    message_length = len;
    printk(KERN_INFO "SimpleChar: Received %zu characters from the user\n", len);
    return len;
}

// Close device
static int dev_release(struct inode *inodep, struct file *filep)
{
    printk(KERN_INFO "SimpleChar: Device successfully closed\n");
    return 0;
}

module_init(simple_char_init);
module_exit(simple_char_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A simple Linux character driver");
MODULE_VERSION("1.0");




