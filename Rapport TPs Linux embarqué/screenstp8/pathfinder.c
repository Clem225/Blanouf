#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h>

#include <native/task.h>
#include <native/timer.h>
#include <native/sem.h>
#include <native/mutex.h>
#include <rtdk.h>

#define TASK_MODE T_JOINABLE
#define TASK_STKSZ 0

RTIME init_time;
RT_SEM sem;
RT_SEM semReset;
RT_MUTEX mutex;


typedef struct task_descriptor{
  RT_TASK task;
  void (*task_function)(void*);			
  RTIME period;
  RTIME duration;
  int priority;
  bool use_resource;
} task_descriptor;

///////////////////////////////////////////////////////////
char* rt_task_name(void) {
  static RT_TASK_INFO info;
  rt_task_inquire(NULL,&info);

  return info.name;
}

///////////////////////////////////////////////////////////
int time_since_start(void) {
  return (rt_timer_read()-init_time)/1000000;
}

///////////////////////////////////////////////////////////
void acquire_resource(void) {

	// rt_sem_p (&sem, TM_INFINITE );		// Version non fonctionnelle avec sémaphore
	rt_mutex_acquire (&mutex, TM_INFINITE); // Version fonctionnelle avec mutex
}

///////////////////////////////////////////////////////////
void release_resource(void) {

	//  rt_sem_v (&sem);		// Version non fonctionnelle avec sémaphore
	rt_mutex_release(&mutex);	// Version fonctionnelle avec mutex
}

///////////////////////////////////////////////////////////
void busy_wait(RTIME time) 
{ 
  	static RT_TASK_INFO info;			// Info sur la tâche
  	rt_task_inquire(NULL,&info);		// Initialisation des infos dont exectime
  	RTIME begin = info.exectime;		// Recuperation du temps d'execution initial (> 0)
  
  
    while(info.exectime - begin < time)
  		  rt_task_inquire(NULL,&info);	// Mise à jour des infos dont exectime
}


void rt_task(void *cookie) { 												
  struct task_descriptor* params=(struct task_descriptor*)cookie;

  rt_printf("started task %s, period %ims, duration %ims, use resource %i\n",rt_task_name(),(int)(params->period/1000000),(int)(params->duration/1000000),params->use_resource);

  while(1) {
    rt_task_wait_period(NULL);
    if(params->use_resource) acquire_resource();
    rt_printf("doing %s    time : %d\n",rt_task_name(), time_since_start());
    busy_wait(params->duration);
    
    static RT_TASK_INFO info;			// Info sur la tâche
  	rt_task_inquire(NULL,&info);		// Initialisation des infos 
  	
	// Test du mutex avec priorité de base et priorité courrante
  	rt_printf("Name : %s  Base prio : %d  Current prio : %d\n", info.name, info.bprio, info.cprio);
    
    rt_printf("doing %s ok    time : %d\n",rt_task_name(), time_since_start());
    if(params->use_resource) release_resource();
  }
}

// Fonction de la tâche ORDO_BUS implémentant le RESET
void rt_task_ordo_bus(void *cookie) { 									

  struct task_descriptor* params=(struct task_descriptor*)cookie;

  rt_printf("started task %s, period %ims, duration %ims, use resource %i\n",rt_task_name(),(int)(params->period/1000000),(int)(params->duration/1000000),params->use_resource);

  while(1) {
    rt_task_wait_period(NULL);
    if(params->use_resource) acquire_resource();
	
	// Si la décrémentation n'est pas possible, on ne bloque pas la tâche
    if(rt_sem_p (&semReset, TM_NONBLOCK ) == -EWOULDBLOCK )		
	{
 	   rt_printf("RESET\n\n\n\n\n\n\n\n\n\n\n");	// Affichage du RESET
	   exit(-1);									// Exit du programme
	}
   
    rt_printf("doing %s    time : %d\n",rt_task_name(), time_since_start());
    busy_wait(params->duration);
    
    static RT_TASK_INFO info;			
  	rt_task_inquire(NULL,&info);		
  	
	// Test du mutex avec priorité de base et priorité courrante
  	rt_printf("Name : %s  Base prio : %d  Current prio : %d\n", info.name, info.bprio, info.cprio);
    
    rt_printf("doing %s ok    time : %d\n",rt_task_name(), time_since_start());
    if(params->use_resource) release_resource();
  }
}


// Fonction de la tâche DISTRIB_DONNEES implémentant le RESET
void rt_task_distrib_donnees(void *cookie) { 											

  struct task_descriptor* params=(struct task_descriptor*)cookie;

  rt_printf("started task %s, period %ims, duration %ims, use resource %i\n",rt_task_name(),(int)(params->period/1000000),(int)(params->duration/1000000),params->use_resource);

  while(1) {
    rt_task_wait_period(NULL);
    if(params->use_resource) acquire_resource();
    rt_printf("doing %s    time : %d\n",rt_task_name(), time_since_start());
    busy_wait(params->duration);
    
    static RT_TASK_INFO info;			
  	rt_task_inquire(NULL,&info);		
  	
	// Test du mutex avec priorité de base et priorité courrante
  	rt_printf("Name : %s  Base prio : %d  Current prio : %d\n", info.name, info.bprio, info.cprio);
    
    rt_printf("doing %s ok    time : %d\n",rt_task_name(), time_since_start());
	
    rt_sem_v (&semReset); // Incrémentation du sémaphore pour le RESET
	
    if(params->use_resource) release_resource();
    
  
  }
  
}


int create_and_start_rt_task(struct task_descriptor* desc,char* name) {
  int status=rt_task_create(&desc->task,name,TASK_STKSZ,desc->priority,TASK_MODE);
	if(status!=0) {
		printf("error creating task %s\n",name);
		return status;
	}

  status=rt_task_set_periodic(&desc->task,TM_NOW,desc->period);
  if(status!=0) {
		printf("error setting period on task %s\n",name);
		return status;
	}
	
	status=rt_task_start(&desc->task,desc->task_function,desc);
  if(status!=0) {
		printf("error starting task %s\n",name);
	}
  return status;
}



int main(void) {  
 
  /* Avoids memory swapping for this program */
  mlockall(MCL_CURRENT|MCL_FUTURE);

  rt_print_auto_init(1);

  init_time=rt_timer_read();
  
  //rt_sem_create (&sem, "sem", 0, S_PRIO); // Version non fonctionnelle avec sémaphore
  rt_mutex_create (&mutex, "mutex"); 		// Version fonctionnelle avec mutex
  rt_sem_create (&semReset, "semReset", 1, S_PRIO);	// Sémaphore pour le RESET
  
  // Initialisation, création et lancement de la tâche ORDO_BUS
  task_descriptor* ORDO_BUS_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  ORDO_BUS_Descriptor->task_function = rt_task_ordo_bus;
  ORDO_BUS_Descriptor->priority = 7;
  ORDO_BUS_Descriptor->duration = 25000000; 
  ORDO_BUS_Descriptor->period = 125000000;
  ORDO_BUS_Descriptor->use_resource = 0;
  
  create_and_start_rt_task(ORDO_BUS_Descriptor, "ORDO_BUS");  
  
  
  // Initialisation, création et lancement de la tâche DISTRIB_DONNEES
  task_descriptor* DISTRIB_DONNEES_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  DISTRIB_DONNEES_Descriptor->task_function = rt_task_distrib_donnees;
  DISTRIB_DONNEES_Descriptor->priority = 6;
  DISTRIB_DONNEES_Descriptor->duration = 25000000; 
  DISTRIB_DONNEES_Descriptor->period = 125000000;
  DISTRIB_DONNEES_Descriptor->use_resource = 1;
  
  create_and_start_rt_task(DISTRIB_DONNEES_Descriptor, "DISTRIB_DONNEES");  
  

  // Initialisation, création et lancement de la tâche PILOTAGE
  task_descriptor* PILOTAGE_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  PILOTAGE_Descriptor->task_function = rt_task;
  PILOTAGE_Descriptor->priority = 5;
  PILOTAGE_Descriptor->duration = 25000000; 
  PILOTAGE_Descriptor->period = 250000000;
  PILOTAGE_Descriptor->use_resource = 1;
  
  create_and_start_rt_task(PILOTAGE_Descriptor, "PILOTAGE");  
  
  
  // Initialisation, création et lancement de la tâche RADIO
  task_descriptor* RADIO_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  RADIO_Descriptor->task_function = rt_task;
  RADIO_Descriptor->priority = 4;
  RADIO_Descriptor->duration = 25000000; 
  RADIO_Descriptor->period = 250000000;
  RADIO_Descriptor->use_resource = 0;
  
  create_and_start_rt_task(RADIO_Descriptor, "RADIO"); 
  
  
  // Initialisation, création et lancement de la tâche CAMERA
  task_descriptor* CAMERA_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  CAMERA_Descriptor->task_function = rt_task;
  CAMERA_Descriptor->priority = 3;
  CAMERA_Descriptor->duration = 25000000; 
  CAMERA_Descriptor->period = 250000000;
  CAMERA_Descriptor->use_resource = 0;
  
  create_and_start_rt_task(CAMERA_Descriptor, "CAMERA"); 
  
  
  // Initialisation, création et lancement de la tâche MESURES
  task_descriptor* MESURES_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  MESURES_Descriptor->task_function = rt_task;
  MESURES_Descriptor->priority = 2;
  MESURES_Descriptor->duration = 50000000; 
  MESURES_Descriptor->period = 5000000000;
  MESURES_Descriptor->use_resource = 1;
  
  create_and_start_rt_task(MESURES_Descriptor, "MESURES"); 
  
  
  // Initialisation, création et lancement de la tâche METEO
  task_descriptor* METEO_Descriptor = (task_descriptor*)malloc(sizeof(task_descriptor));
  METEO_Descriptor->task_function = rt_task;
  METEO_Descriptor->priority = 1;
  METEO_Descriptor->duration = 60000000; // 40000000
  METEO_Descriptor->period = 5000000000;
  METEO_Descriptor->use_resource = 1;
  
  create_and_start_rt_task(METEO_Descriptor, "METEO"); 
  
  // Version non fonctionnelle avec sémaphore
  // rt_sem_v (&sem); // Incrémentation du sémaphore principal
    
  getchar();
  
  return  EXIT_SUCCESS;
}
