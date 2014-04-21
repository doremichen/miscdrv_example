#include <linux/module.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/delay.h>
#include <linux/slab.h> /* kmalloc() */
#include <linux/wait.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/xlog.h>

#define __DEBUG__

#ifdef __DEBUG__
    #define DEBUGI(format, ...) printk(KERN_INFO "[miscdrv]"format"\n",##__VA_ARGS__)
    #define DEBUGE(format, ...) printk(KERN_ERR "[miscdrv]"format"\n",##__VA_ARGS__)
#else
    #define DEBUGI(format, ...)
    #define DEBUGE(format, ...)
#endif

#define MYDRV_SIZE 0x200

#define MYDRIVER_MINOR  174 

static const char misc_shortname[] = "misc_drv_example";

struct MyMiscDrv
{
  unsigned char mem[MYDRV_SIZE];
  long count;      
};

static struct MyMiscDrv *MyMiscDevp = NULL;

static int mydriver_open(struct inode* inode, struct file* filp)
{
    struct MyMiscDrv *devp = NULL;
    DEBUGI("[%s] enter\n", __FUNCTION__);
    filp->private_data = MyMiscDevp;
    devp = filp->private_data;
    devp->count++;
    
    return 0;   
}    


static int mydriver_release(struct inode* inode, struct file* filp)
{
    struct MyMiscDrv *devp = filp->private_data;
    DEBUGI("[%s] enter\n", __FUNCTION__);
    devp->count--;
    return 0;   
} 

static ssize_t mydriver_read(struct file* filp, char __user *buf, size_t size, loff_t* offp)
{
    unsigned long p = *offp;
    unsigned int count = size;
    int ret = 0;
    struct MyMiscDrv *devp = filp->private_data;
    DEBUGI("[%s] enter\n", __FUNCTION__);
    DEBUGI("[%s] p = %lu\n", __FUNCTION__, p);
    if(p >= MYDRV_SIZE) {
        DEBUGE("[%s] Read error...\n", __FUNCTION__);
        return count ? -ENXIO : 0;      
    } 
    else {
        count = MYDRV_SIZE - p;    
    }    
    
    DEBUGI("[%s] buf = %s\n", __FUNCTION__, buf);
            
    if(copy_to_user((void *)buf, (void *)(devp->mem + p), count)) {
        DEBUGE("[%s] copy_to_user fail...\n", __FUNCTION__);    
        ret = -EFAULT;           
    }
    else {
        *offp += count;
        ret = count;            
        DEBUGI("[%s] read %u bytes(s) from %lu\n", __FUNCTION__, count, p);
        DEBUGI("[%s] devp->mem = %s\n", __FUNCTION__, devp->mem);
    }
    
    return ret;  
}   

static ssize_t mydriver_write(struct file* filp, const char __user *buf, size_t size, loff_t* offp)
{
    unsigned long p = *offp;
    int ret = 0;
    unsigned int count = size;
    struct MyMiscDrv *devp = filp->private_data;
    DEBUGI("[%s] enter\n", __FUNCTION__);
    if(p >= MYDRV_SIZE) {
        DEBUGE("[%s] Read error...\n", __FUNCTION__);
        return count ? -ENXIO : 0;      
    } 
    else {
        count = MYDRV_SIZE - p;    
    }  
    
    //clear memory
    memset(devp->mem, 0, MYDRV_SIZE);
    
    DEBUGI("[%s] buf = %s\n", __FUNCTION__, buf);
    
    if(copy_from_user((void *)(devp->mem + p), (void *)buf, count)) {
        DEBUGE("[%s] copy_from_user fail...\n", __FUNCTION__);    
        ret = -EFAULT;           
    }
    else {
        *offp += count;
        ret = count;
            
        DEBUGI("[%s] written %u bytes(s) from %lu\n", __FUNCTION__, count, p);
        DEBUGI("[%s] devp->mem = %s\n", __FUNCTION__, devp->mem);
    }
    
    
    return ret;     
}    

/*
* ioctl member field is removed from linux 2.6.11, new drivers could use 
* the improved interface (unlocked_ioctl/compat_ioctl). 
*/
static const struct file_operations mydriver_fops = {
  
  .owner = THIS_MODULE,
  .read =  mydriver_read,
  .write =  mydriver_write,
  .open =  mydriver_open,  
  .release =  mydriver_release,  
    
};

static struct miscdevice mydriver_device = {
    .minor = MYDRIVER_MINOR,
    .name = misc_shortname,
    .fops = &mydriver_fops,
};
 
static int __init misc_drv_init(void)
{
    int ret = 0;
    DEBUGI("[%s] enter\n", __FUNCTION__);
    
    MyMiscDevp = kmalloc(sizeof(struct MyMiscDrv), GFP_KERNEL);
    
    if(!MyMiscDevp) {
        DEBUGE("[%s] kmalloc fail...\n", __FUNCTION__);
        ret =  -ENOMEM;
        goto fail_malloc;
    }
    
    memset(MyMiscDevp, 0, sizeof(struct MyMiscDrv));
    
    ret = misc_register(&mydriver_device);
    if (ret) {
        DEBUGE("[%s] misc register error\n", __FUNCTION__);   
    }
    
    return 0;
fail_malloc:
               
    return ret;
}
 
static void __exit misc_drv_exit(void)
{
    DEBUGI("Goodbye\n");
    
    misc_deregister(&mydriver_device);
    
    kfree(MyMiscDevp);
}
 
module_init(misc_drv_init);
module_exit(misc_drv_exit);

MODULE_DESCRIPTION("Hello Misc drv example !!");
MODULE_AUTHOR("Bo-Yi Wu <appleboy.tw AT gmail.com>");
MODULE_LICENSE("GPL");