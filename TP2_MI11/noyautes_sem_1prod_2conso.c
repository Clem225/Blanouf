/*
 * noyautes_sem_1prod_2conso.c
 *
 *  Created on: 9 juin 2017
 *      Author: mi11p008
 */


/*#include "serialio.h"
#include "noyau.h"
#include "sem.h"

#define TAILLE_TABLEAU 3

TACHE tacheStart();
TACHE tacheProd();
TACHE tacheConso1();
TACHE tacheConso2();
uint16_t prod, conso1, conso2;		// 2 conso et 1 prod
uint16_t fifo[TAILLE_TABLEAU];
uint16_t nb_places_libres = TAILLE_TABLEAU;
ushort sem1, sem2, semMutexConso;
int l = 0, j = 0;


TACHE	tacheStart(void)
{
  puts("------> EXEC tache Start");

  prod = cree(tacheProd);
  conso1 = cree(tacheConso1);
  conso2 = cree(tacheConso2);

  active(conso1);
  active(conso2);
  active(prod);

  fin_tache();
}

TACHE	tacheProd(void)
{
  puts("------> EXEC tache Prod");

  uint16_t j=0,k,i=0;

  while(1)
  {
	  for (k=0; k<30000; k++);
	  //for (k=0; k<10000; k++);

	  if (nb_places_libres>=1)
	  {
		  _lock_();
		  printf("**PROD** -> Production : fifo[%d] = %d\n", i, j);
		  fifo[i]=j;
		  _unlock_();
		  j++;

		  nb_places_libres--;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
	  }
	  else
	  {

		  s_wait(sem1);		// dort()
	  }

	  if (nb_places_libres<TAILLE_TABLEAU)
	  {

		  s_signal(sem2);		// reveille(conso);
	  }

  }

  fin_tache();
}


TACHE	tacheConso1(void)
{
  uint16_t k;

  puts("------> EXEC tache Conso 1");

  s_wait(sem2);	// dort()

  while(1)
  {
	  //for (k=0; k<30000; k++);
	  for (k=0; k<10000; k++);


	  //puts("------> Consommateur");

	  s_wait(semMutexConso);


	  if (nb_places_libres==TAILLE_TABLEAU)
	  {
		  s_wait(sem2);	// dort()

	  }
	  else
	  {
		  _lock_();
		  printf("**CONSO 1** -> Lecture de fifo[%d] = %d\n", l, fifo[l]);
		  _unlock_();

		  nb_places_libres++;

		  l++;
		  if (l==TAILLE_TABLEAU)
			  l=0;
	  }

	  s_signal(semMutexConso);

	  if (nb_places_libres==1)
	  {

		  s_signal(sem1);	// reveille(prod);
	  }

  }

  fin_tache();
}

TACHE	tacheConso2(void)
{
  uint16_t k;

  puts("------> EXEC tache Conso 2");

  s_wait(sem2);	// dort()

  while(1)
  {
	  //for (k=0; k<30000; k++);
	  for (k=0; k<10000; k++);


	  //puts("------> Consommateur");

	  s_wait(semMutexConso);

	  if (nb_places_libres==TAILLE_TABLEAU)
	  {

		  s_wait(sem2);	// dort()

	  }
	  else
	  {
		  _lock_();
		  printf("**CONSO 2** -> Lecture de fifo[%d] = %d\n",l, fifo[l]);
		  _unlock_();

		  nb_places_libres++;

		  l++;
		  if (l==TAILLE_TABLEAU)
			  l=0;
	  }

	  s_signal(semMutexConso);


	  if (nb_places_libres==1)
	  {

		  s_signal(sem1);	// reveille(prod);
	  }

  }

  fin_tache();
}

int main()
{
  serial_init(115200);
  puts("Test noyau");
  puts("Noyau preemptif");
  puts("*******************DEBUT*********************\n\n\n\n\n");

  printf("TAILLE DU TABLEAU : %d\n", TAILLE_TABLEAU);

  s_init();
  sem1 = s_cree(0);		// prod
  sem2 = s_cree(0);		// conso
  semMutexConso = s_cree(1);		// mutex entre les 2 producteurs pour les empecher de produire en même tps
  start(tacheStart);

  return(0);
}*/
