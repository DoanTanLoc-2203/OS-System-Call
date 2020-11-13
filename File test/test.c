#include<sys/syscall.h>
#include<stdio.h>
#include<unistd.h>
#include<get_proc_info.h>
#include<sys/types.h>
#include<stdint.h>
int main(){
	pid_t mypid = getpid();
	printf("PID: %d\n",mypid);
	struct procinfos info;
	if(sys_get_proc_info(mypid,&info) ==1812962)
	{
		printf("My studentID: %ld\n",info.studentID);
		printf("Current Process:\tName: %s\tPID: %d\n",info.proc.name,info.proc.pid);
		printf("Parent Process: \tName: %s\tPID: %d\n",info.parent_proc.name,info.parent_proc.pid);
		if(info.oldest_child_proc.pid==-1)
		{
			printf("Process have no children!\n");
		}
		else
		{
			printf("OlsChild Process:\tName: %s\tPID: %d\n",info.oldest_child_proc.name,info.oldest_child_proc.pid);
		}
	}
	else
	{
		printf("Cannot get infomation form the process %d\n",mypid);	
	}
	return 0;
}
