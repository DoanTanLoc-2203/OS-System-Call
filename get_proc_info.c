#include "get_proc_info.h"
#include <linux/kernel.h>
#include <sys/syscall.h>
long sys_get_proc_info(pid_t pid, struct procinfos * info) {
	long sys_return_value;
	sys_return_value= syscall(439,pid,info);
	return sys_return_value;
}
