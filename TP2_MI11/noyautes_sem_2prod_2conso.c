/*
 * noyautes_sem_2prod_2conso.c
 *
 *  Created on: 9 juin 2017
 *      Author: mi11p008
 */

#include "serialio.h"
#include "noyau.h"
#include "sem.h"

#define TAILLE_TABLEAU 3

TACHE tacheStart();
TACHE tacheProd1();
TACHE tacheProd2();
TACHE tacheConso1();
TACHE tacheConso2();
uint16_t prod1, prod2, conso1, conso2;		// 2 conso et 2 prod
uint16_t fifo[TAILLE_TABLEAU];
uint16_t nb_places_libres = TAILLE_TABLEAU;
ushort sem1, sem2, semMutexConso, semMutexProd;
int l = 0, j = 0, m = 0;


TACHE	tacheStart(void)
{
  puts("------> EXEC tache Start");

  prod1 = cree(tacheProd1);
  prod2 = cree(tacheProd2);
  conso1 = cree(tacheConso1);
  conso2 = cree(tacheConso2);

  active(conso1);
  active(conso2);
  active(prod1);
  active(prod2);

  fin_tache();
}

TACHE	tacheProd1(void)
{
  puts("------> EXEC tache Prod 1");

  uint16_t k;

  while(1)
  {
	  for (k=0; k<30000; k++);
	  //for (k=0; k<10000; k++);

	  s_wait(semMutexProd);


	  if (nb_places_libres>=1)
	  {
		  _lock_();
		  printf("**PROD 1** -> Production : fifo[%d] = %d\n", l, j);
		  fifo[l]=j;
		  _unlock_();
		  j++;

		  nb_places_libres--;

		  l++;
		  if (l==TAILLE_TABLEAU)
			  l=0;
	  }
	  else
	  {

		  s_wait(sem1);		// dort()
	  }

	  s_signal(semMutexProd);


	  if (nb_places_libres<TAILLE_TABLEAU)
	  {

		  s_signal(sem2);		// reveille(conso);
	  }

  }

  fin_tache();
}

TACHE	tacheProd2(void)
{
  puts("------> EXEC tache Prod 2");

  uint16_t k;

  while(1)
  {
	  for (k=0; k<30000; k++);
	  //for (k=0; k<10000; k++);

	  s_wait(semMutexProd);

	  if (nb_places_libres>=1)
	  {
		  _lock_();
		  printf("**PROD 2** -> Production : fifo[%d] = %d\n", l, j);
		  fifo[l]=j;
		  _unlock_();
		  j++;

		  nb_places_libres--;

		  l++;
		  if (l==TAILLE_TABLEAU)
			  l=0;

	  }
	  else
	  {

		  s_wait(sem1);		// dort()
	  }

	  s_signal(semMutexProd);

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
		  printf("**CONSO 1** -> Lecture de fifo[%d] = %d\n", m, fifo[m]);
		  _unlock_();

		  nb_places_libres++;

		  m++;
		  if (m==TAILLE_TABLEAU)
			  m=0;
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
		  printf("**CONSO 2** -> Lecture de fifo[%d] = %d\n",m, fifo[m]);
		  _unlock_();

		  nb_places_libres++;

		  m++;
		  if (m==TAILLE_TABLEAU)
			  m=0;
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
  semMutexProd = s_cree(1);		// mutex entre les 2 producteurs pour les empecher de produire en même tps
  semMutexConso = s_cree(1);		// mutex entre les 2 conso pour les empecher de produire en même tps
  start(tacheStart);

  return(0);
}
