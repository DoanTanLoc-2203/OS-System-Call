#include <sys/syscall.h>
#include <stdio.h>
#include <unistd.h>
int main(){
	long sys_return_value;
	unsigned long info;
	sys_return_value= syscall(439,-1,&info);
	printf("My studentID: %ld\n",sys_return_value);
	return 0;
}
