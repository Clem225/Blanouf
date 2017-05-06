#include <stdio.h>
#include <native/task.h>
#include <analogy/os_facilities.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/sem.h>

#define TASK_PRIO_HELLO 98
#define TASK_PRIO_WORLD 97
#define TASK_PRIO_METRO 99
//#define TASK_PRIO 99
#define TASK_MODE 0
#define TASK_STKSZ 0

RT_TASK task_printf;
RT_TASK task_printf2;
RT_TASK task_metronome;
RT_SEM sem;

void task_hello()
{
	while(1)
	{
		rt_sem_p (&sem, 0);
		rt_printf("Hello\n");
	}
}

void task_world()
{
	while(1)
	{
		rt_sem_p (&sem, 0);
		rt_printf("World !\n");
		rt_sem_v (&sem);
	}
}

void task_metro()
{
	while(1)
	{
		rt_sem_v (&sem);
		rt_sem_v (&sem);
		
		rt_sem_p (&sem, 0);
		rt_task_sleep(rt_timer_ns2ticks(1000000000));
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
	int err1, err2, err3;
	
	rt_sem_create (&sem, "sem", 0, S_PRIO);
	
	err1 = rt_task_create(&task_printf, "hello", TASK_STKSZ, TASK_PRIO_HELLO, TASK_MODE);
	err2 = rt_task_create(&task_printf2, "world", TASK_STKSZ, TASK_PRIO_WORLD, TASK_MODE);
	err3= rt_task_create(&task_metronome, "metro", TASK_STKSZ, TASK_PRIO_METRO, TASK_MODE);
	if(!err1 && !err2 && !err3)
	{
		rt_task_start(&task_printf, &task_hello, NULL);
		rt_task_join(&task_printf);
		rt_task_start(&task_printf2, &task_world, NULL);
		rt_task_join(&task_printf2);
		rt_task_start(&task_metronome, &task_metro, NULL);
		rt_task_join(&task_metronome);
		
		getchar();
		
	}
		
	
	return 0;
}
