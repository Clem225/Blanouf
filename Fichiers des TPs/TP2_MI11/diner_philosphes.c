/*
 * diner_philosphes.c
 *
 *  Created on: 2 juin 2017
 *      Author: mi11p008
 */


/*#include "serialio.h"
#include "noyau.h"
#include "sem.h"


TACHE tacheStart();
TACHE tachePhilo();

ushort semProtectFourch, semAttente, mutex;	// semAttente et mutex servent à bloquer les philosophes lorsqu'ils ont fini de manger
ushort semFourchette[5];	// semaphore des fourchette
ushort id_philo;	// id unique par philosophe
int j;

TACHE	tacheStart(void)
{
	puts("------> EXEC tache Start");

    int i;
    s_init();

    semProtectFourch = s_cree(4);			// c'est pour éviter de prendre toutes les fourchettes de gauche (on garde tjr une fourchette)

	mutex = s_cree(1);
	semAttente = s_cree(0);

    for(i=0; i < 5; i++) {
        semFourchette[i] = s_cree(1);
    }

    for(id_philo=0; id_philo < 5; id_philo++)
    {
    	active(cree(tachePhilo));

    	//for(i = 0; i < 100000; i++);
    }


	while(1);

	fin_tache();
}

TACHE tachePhilo()
{
	uint16_t k;

	ushort id = id_philo;
    printf("------> Philosophe n° : %d demarre\n", id);

    while (1)
	{
		for (k=0; k<60000; k++);		// A VERIFIER ==> pense

		_lock_();
        printf("------> Philosophe n° : %d attend pour manger : il a faim\n", id);
        _unlock_();

        s_wait(semProtectFourch);						// on prend le semaphore semProtectFourch
        s_wait(semFourchette[ (id - 1) % 5 ]);	// on prend la fourchette de gauche
        s_wait(semFourchette[ id % 5 ]);	// on prend la fourchette de droite

		_lock_();
        printf("------> Philosophe n° : %d en train de manger\n", id);
        _unlock_();

		//for (k=0; k<30000; k++);		// A VERIFIER ==> temps d'attente pour qu'il mange

		s_signal(semProtectFourch);						// on libere le semaphore semProtectFourch
        s_signal(semFourchette[ (id - 1) % 5 ]);	// on depose la fourchette de gauche
        s_signal(semFourchette[ id % 5 ]);	// on depose la fourchette de droite

		_lock_();
        printf("------> Philosophe n° : %d a fini de manger : il pense\n", id);
        _unlock_();

		s_wait(mutex);		// c'est pour protéger le compteur j
		j++;

		if(j == 5) 			// ils ont tous fini de manger
		{
			for(k=0; k < 5; k++)
				s_signal(semAttente);		// on libere les tâches pour qu'ils se retapent un grec

			j = 0;							// on réinitialise j à 0
			s_signal(mutex);

	        printf("------> Fin du repas\n", id);

	        //while(1);
			fin_tache();					// A VOIR
		}
		else
		{
			s_signal(mutex);
			s_wait(semAttente);				// on bloque la tâche

	        //while(1);
			//fin_tache();					// A VOIR
		}

    }
}

int main()
{
  serial_init(115200);
  puts("Test noyau");
  puts("Noyau preemptif");
  puts("*******************DEBUT*********************\n\n\n\n\n");

  start(tacheStart);

  return(0);
}*/
