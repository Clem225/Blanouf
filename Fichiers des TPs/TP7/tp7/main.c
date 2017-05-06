#include <stdio.h>
#include <native/task.h>
#include <analogy/os_facilities.h>
#include <unistd.h>
#include <sys/mman.h>

#define TASK_PRIO 99
#define TASK_MODE 0
#define TASK_STKSZ 0

RT_TASK task_printf;

void task_hello()
{
	while(1)
	{
		rt_task_sleep(rt_timer_ns2ticks(1000000000));
		
		rt_printf("Hello World !\n");
	}
}

int main()
{
	/*Question 1.1
	while(1)
	{
		sleep(1);
		printf("Hello World !\n");
	}
	*/


	/*Question 1.2*/
	mlockall(MCL_CURRENT|MCL_FUTURE);
	rt_print_auto_init(1);
	int err;
	
	err = rt_task_create(&task_printf, "hello world", TASK_STKSZ, TASK_PRIO, TASK_MODE);
	if(!err)
		rt_task_start(&task_printf, &task_hello, NULL);
		
	getchar();
	
	return 0;
}
