#include <stdio.h>
#include <native/task.h>
#include <analogy/os_facilities.h>
#include <unistd.h>
#include <sys/mman.h>
#include <native/sem.h>
#include <nucleus/timer.h>


#define TASK_PRIO 99
#define TASK_MODE 0
#define TASK_STKSZ 0
#define TAILLE 10000

RT_TASK task_latence;
RTIME tab[TAILLE];

void task_wait()
{
	int i;
	RTIME moy = 0, min, max;
	RTIME begin, end;
	
	min = 9999999999999;
	max = 0;
	
	for(i = 0; i < TAILLE; i++)
	{
		begin = rt_timer_read();
		rt_task_sleep(rt_timer_ns2ticks(1000000));
		end = rt_timer_read();
		
		if(min > end - begin)
			min = end - begin;

		if(max < end - begin)
		{
			max = end - begin;
		}
		
		//tab[i] = end - begin;
		moy += end - begin;
	}
	
	moy = moy / TAILLE;
	

	/*for(i = 1; i < TAILLE; i++)
	{
		if(min > tab[i])
			min = tab[i];

		if(max < tab[i])
		{
			max = tab[i];
		}
	}*/
	
	rt_printf("Moyenne :%llu \nMaximum : %llu \nMinimum : %llu\n", moy, max, min);

}


int main()
{
	mlockall(MCL_CURRENT|MCL_FUTURE);
	rt_print_auto_init(1);
	int err1;
	
	err1 = rt_task_create(&task_latence, "wait", TASK_STKSZ, TASK_PRIO, TASK_MODE);

	if(!err1)
	{
		rt_task_start(&task_latence, &task_wait, NULL);
		rt_task_join(&task_latence);
		
		getchar();
	}
		
	
	return 0;
}
