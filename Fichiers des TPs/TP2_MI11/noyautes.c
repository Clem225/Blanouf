/* NOYAUTEST.C */
/*--------------------------------------------------------------------------*
 *			      Programme de tests			    *
 *--------------------------------------------------------------------------*/

#include "serialio.h"
#include "noyau.h"


/*
 ** Test du noyau preemptif. Lier noyautes.c avec noyau.c et noyaufil.c
 */

/*TACHE	tacheA(void);
TACHE	tacheB(void);
TACHE	tacheC(void);
TACHE	tacheD(void);

TACHE	tacheA(void)
{
  puts("------> EXEC tache A");
  active(cree(tacheB));
  active(cree(tacheC));
  active(cree(tacheD));
  fin_tache();
}

TACHE	tacheB(void)
{
  int i=0;
  long j;
  puts("------> DEBUT tache B");
  while (1) {
    for (j=0; j<30000L; j++);
    printf("======> Dans tache B %d\n",i);
    i++;
  }
}

TACHE	tacheC(void)
{
  int i=0;
  long j;
  puts("------> DEBUT tache C");
  while (1) {
    for (j=0; j<60000L; j++);
    printf("======> Dans tache C %d\n",i);
    i++;
  }
}

TACHE	tacheD(void)
{
  int i=0;
  long j;
  puts("------> DEBUT tache D");
  while (1) {
    for (j=0; j<120000L; j++);
    printf("======> Dans tache D %d\n",i++);
    if (i==50) noyau_exit();
  }
}*/

/*#define TAILLE_TABLEAU 3

TACHE tacheStart();
TACHE tacheProd();
TACHE tacheConso();
uint16_t prod, conso;
uint16_t fifo[TAILLE_TABLEAU];
uint16_t nb_places_libres = TAILLE_TABLEAU;

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
	  for (k=0; k<10000; k++);

	  if (nb_places_libres>=1)
	  {
		  _lock_();
		  printf("------> Production : %d = %d\n", i, j);
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
		  puts("------> Producteur dort (Cas 1 : File pleine)\n");
		  _unlock_();

		  dort();
	  }

	  if (nb_places_libres<TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("------> Reveil du conso (Cas 2 : File non vide)\n");
		  _unlock_();

		  reveille(conso);
	  }

  }

  fin_tache();
}

TACHE	tacheConso(void)
{
  uint16_t k,i=0;

  dort();

  while(1)
  {
	  for (k=0; k<30000; k++);

	  //puts("------> Consommateur");

	  if (nb_places_libres==TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("++++++> Consommateur dort (Cas 3 : File vide)\n");
		  _unlock_();

		  dort();
	  }
	  else
	  {
		  _lock_();
		  printf("++++++> Lecture de %d = %d\n", i, fifo[i]);
		  _unlock_();

		  nb_places_libres++;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
	  }

	  if (nb_places_libres==1)
	  {
		  _lock_();
		  puts("++++++> Reveil prod (Cas 4 : File non pleine)\n");
		  _unlock_();

		  reveille(prod);
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
  start(tacheStart);
  return(0);
}*/

