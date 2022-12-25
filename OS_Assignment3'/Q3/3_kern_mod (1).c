# include <linux/init.h>
# include <linux/kernel.h>
# include <linux/types.h>
# include <unistd.h>
# include <linux/sched.h>
# include <linux/pid.h>
# include <linux/module.h>
# define num 10

MODULE_LICENSE(“GPL”);
MODULE_AUTHOR(“Dev Mann”);
MODULE_DESCRIPTION(“Kernel Module to print the details of a process through it's process id.”);
MODULE_VERSION(“0.01”);

static pid_t take_inp=num;

module_param(take_inp,pid_t,0644);
MODULE_PARM_DESC(take_inp,"input pid")

static int __init process_task_struct_info_init(void)
{
    struct task_struct *giv_proc;
    pid_t pid=take_inp;
    giv_proc= pid_task(find_vpid(pid),PIDTYPE_PID);
    pr_info("The process id is as follows : %d ",giv_proc->pid);
    pr_info("\nThe user id is as follows : %d ",giv_proc->cred->uid.val);
    pr_info("\nThe process group id is as follows : %d ",giv_proc->group_leader->pid);
    pr_info("\nThe command path is as follows : %s ",giv_proc->comm);
    return 0;
}
  
static void __exit process_task_struct_info_exit(int pid)
{
    printk(KERN_INFO "The process details were successfully printed.\n");
}

module_init(process_task_struct_info_init);
module_exit(process_task_struct_info_exit);