/*
 * noyautes_sem.c
 *
 *  Created on: 2 juin 2017
 *      Author: mi11p008
 */


/* NOYAUTEST.C */
/*--------------------------------------------------------------------------*
 *			      Programme de tests			    *
 *--------------------------------------------------------------------------*/

/*#include "serialio.h"
#include "noyau.h"
#include "sem.h"

#define TAILLE_TABLEAU 3

TACHE tacheStart();
TACHE tacheProd();
TACHE tacheConso();
uint16_t prod, conso;
uint16_t fifo[TAILLE_TABLEAU];
uint16_t nb_places_libres = TAILLE_TABLEAU;
ushort sem1, sem2;

TACHE	tacheStart(void)
{
  puts("------> EXEC tache Start");
  prod = cree(tacheProd);
  conso = cree(tacheConso);

  active(prod);
  active(conso);

  //while(1);

  fin_tache();
}

TACHE	tacheProd(void)
{
  puts("------> EXEC tache Prod");

  uint16_t j=0,k,i=0;

  //for (j=0; j<30000; j++);

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
		  _lock_();
		  puts("**PROD** -> Producteur dort (Cas 1 : File pleine)\n");
		  _unlock_();

		  s_wait(sem1);		// dort()
	  }

	  if (nb_places_libres<TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("**PROD** -> Reveil du conso (Cas 2 : File non vide)\n");
		  _unlock_();

		  s_signal(sem2);		// reveille(conso);
	  }

  }

  fin_tache();
}

TACHE	tacheConso(void)
{
  uint16_t k,i=0;
  puts("------> EXEC tache Conso");

  s_wait(sem2);	// dort()

  while(1)
  {
	  //for (k=0; k<30000; k++);
	  for (k=0; k<10000; k++);


	  //puts("------> Consommateur");

	  if (nb_places_libres==TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("**CONSO** -> Consommateur dort (Cas 3 : File vide)\n");
		  _unlock_();

		  s_wait(sem2);	// dort()

	  }
	  else
	  {
		  _lock_();
		  printf("**CONSO** -> Lecture de fifo[%d] = %d\n", i, fifo[i]);
		  _unlock_();

		  nb_places_libres++;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
	  }

	  if (nb_places_libres==1)
	  {
		  _lock_();
		  puts("**CONSO** -> Reveil prod (Cas 4 : File non pleine)\n");
		  _unlock_();

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
  puts("\n\n\n*******************DEBUT*********************\n\n\n\n\n");

  printf("TAILLE DU TABLEAU : %d\n", TAILLE_TABLEAU);

  s_init();
  sem1 = s_cree(0);		// prod
  sem2 = s_cree(0);		// conso
  start(tacheStart);

  return(0);
}*/
