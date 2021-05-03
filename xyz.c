#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>



/* performs a depth-first traversal of the list of tasks in the system. */

void DFS(struct task_struct *ptr) {

	struct list_head *list;
	struct task_struct *child;
	
	
	if (thread_group_leader(ptr))
		printk(KERN_INFO ">>>All Processe Name and ID in order:%s [%d]<<<\n", ptr->comm, ptr->pid);

        if(ptr->pid < 100){
                printk(KERN_INFO "Processes Having ID < 100 in order Name, ID and Priority:%s [%d] [%d]",ptr->comm,ptr->pid,ptr->prio);
                printk(KERN_INFO "\n");
        }
	if(ptr->state == 0){
		printk(KERN_INFO ">>>Runnable Processes Name and ID in order:%s [%d]<<<",ptr->comm, ptr->pid);
		printk(KERN_INFO "\n");
	}
	if(ptr->comm == "gedit"){
		printk(KERN_INFO ">>>Process named 'gedit' Parent Name and ID in order:%s [%d]<<<",ptr->parent->comm, ptr->parent->pid);
		printk(KERN_INFO "\n");
	}
	list_for_each(list, &ptr->children) {
		child = list_entry(list, struct task_struct, sibling);
		DFS(child);
	}
}
int simple_init(void)
{
	struct task_struct *task;
	struct list_head *list;
	struct task_struct *c;
	printk(KERN_INFO "Loading XYZ Module\n");
	DFS(&init_task);
	return 0;
}
void simple_exit(void) 
{
	printk(KERN_INFO "Removing XYZ Module\n");
}

module_init( simple_init );

module_exit( simple_exit );



MODULE_LICENSE("GPL");

MODULE_DESCRIPTION("XYZ Module");

MODULE_AUTHOR("Utku Polat");
