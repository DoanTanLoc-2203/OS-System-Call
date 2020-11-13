#include <linux/kernel.h>   
#include <linux/sched.h>
#include <linux/syscalls.h>

struct proc_info {
  	pid_t pid;
    	char name[16];
};
struct procinfos {
	long studentID;
	struct proc_info proc;
	struct proc_info parent_proc;
	struct proc_info oldest_child_proc;
}; 

SYSCALL_DEFINE2(sys_get_proc_info,pid_t ,pid,struct procinfos *,info)
{
    	struct task_struct *p;
	struct task_struct *OldChild;
  	struct list_head *ChildrenList;
	struct procinfos temp ;
	bool check=false;
   	temp.studentID = 1812962;
	printk(KERN_INFO "My studentID: %ld",temp.studentID);
	if(pid==-1)
	{
		check=true;
		temp.proc.pid=current->pid;//current process
		strcpy(temp.proc.name,current->comm);
		printk(KERN_INFO "(Current) pid: %d\tname: %s\n" ,temp.proc.pid,temp.proc.name);
		temp.parent_proc.pid=current->parent->pid;//parent process
		strcpy(temp.parent_proc.name,current->parent->comm);
		printk(KERN_INFO "(Parent) pid: %d\tname: %s\n" ,temp.parent_proc.pid,temp.parent_proc.name);
		ChildrenList=&current->children;//child process
		if(list_empty(ChildrenList))
		{
			temp.oldest_child_proc.pid=-1;
			strcpy(temp.oldest_child_proc.name," ");
			printk(KERN_INFO "Process have no childrent!\n");
		}
		else
		{
			OldChild = list_first_entry(ChildrenList, struct task_struct, sibling);
			temp.oldest_child_proc.pid=OldChild->pid;
			strcpy(temp.oldest_child_proc.name,OldChild->comm);
			printk(KERN_INFO "(OldChild) pid: %d\tname: %s\n" ,temp.oldest_child_proc.pid,temp.oldest_child_proc.name);
		}
	}
	else
	{
		for_each_process(p)
		{
			if(p->pid==pid)
			{
				check=true;
				temp.proc.pid=p->pid;//current process
				strcpy(temp.proc.name,p->comm);
				printk(KERN_INFO "(Current) pid: %d\tname: %s\n" ,temp.proc.pid,temp.proc.name);
				temp.parent_proc.pid=p->parent->pid;//parent process
				strcpy(temp.parent_proc.name,p->parent->comm);
				printk(KERN_INFO "(Parent) pid: %d\tname: %s\n" ,temp.parent_proc.pid,temp.parent_proc.name);
				ChildrenList=&p->children;//child process
				if(list_empty(ChildrenList))
				{
					temp.oldest_child_proc.pid=-1;
					strcpy(temp.oldest_child_proc.name," ");
					printk(KERN_INFO "Process have no childrent!\n");
				}
				else
				{
					OldChild = list_first_entry(ChildrenList, struct task_struct, sibling);
					temp.oldest_child_proc.pid=OldChild->pid;
					strcpy(temp.oldest_child_proc.name,OldChild->comm);
					printk(KERN_INFO "(OldChild) pid: %d\tname: %s\n" ,temp.oldest_child_proc.pid,temp.oldest_child_proc.name);
				}
			}
		}	
	}
	copy_to_user(info,&temp,sizeof(struct procinfos));
	if(check==true) return temp.studentID;
	else
	{
		printk(KERN_INFO "SYSCALL FAILED!\n");
		return EINVAL;
	}
	
}
