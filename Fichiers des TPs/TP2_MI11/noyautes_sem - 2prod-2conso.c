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

TACHE	tacheStart(void)
{
  puts("------> EXEC tache Start");
  
  prod1 = cree(tacheProd1);
  prod2 = cree(tacheProd2);
  conso1 = cree(tacheConso1);
  conso2 = cree(tacheConso2);

  active(prod1);
  active(prod2);
  active(conso1);
  active(conso2);


  fin_tache();
}

TACHE	tacheProd1(void)
{
  puts("------> EXEC tache Prod");

  uint16_t j=0,k,i=0;

  while(1)
  {
	  //for (k=0; k<30000; k++);
	  for (k=0; k<10000; k++);

	  if (nb_places_libres>=1)
	  {
		  s_wait(semMutexProd);	
		  
		  _lock_();
		  printf("------> Production 1 : %d = %d\n", i, j);
		  fifo[i]=j;
		  _unlock_();
		  j++;

		  nb_places_libres--;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
		  
		  s_signal(semMutexProd);	
	  }
	  else
	  {
		  _lock_();
		  puts("------> Producteur 1 dort (Cas 1 : File pleine)\n");
		  _unlock_();

		  s_wait(sem1);		// dort()
	  }

	  if (nb_places_libres<TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("------> Reveil du conso (Cas 2 : File non vide)\n");
		  _unlock_();

		  s_signal(sem2);		// reveille(conso);
	  }

  }

  fin_tache();
}

TACHE	tacheProd2(void)
{
  puts("------> EXEC tache Prod");

  uint16_t j=0,k,i=0;

  while(1)
  {
	  //for (k=0; k<30000; k++);
	  for (k=0; k<10000; k++);

	  if (nb_places_libres>=1)
	  {
		  s_wait(semMutexProd);	
		  
		  _lock_();
		  printf("------> Production 2 : %d = %d\n", i, j);
		  fifo[i]=j;
		  _unlock_();
		  j++;

		  nb_places_libres--;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
		  
		  s_signal(semMutexProd);
	  }
	  else
	  {
		  _lock_();
		  puts("------> Producteur 2 dort (Cas 1 : File pleine)\n");
		  _unlock_();

		  s_wait(sem1);		// dort()
	  }

	  if (nb_places_libres<TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("------> Reveil du conso (Cas 2 : File non vide)\n");
		  _unlock_();

		  s_signal(sem2);		// reveille(conso);
	  }

  }

  fin_tache();
}


TACHE	tacheConso1(void)
{
  uint16_t k,i=0;

  s_wait(sem2);	// dort()

  while(1)
  {
	  for (k=0; k<30000; k++);
	  //for (k=0; k<10000; k++);


	  //puts("------> Consommateur");

	  if (nb_places_libres==TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("++++++> Consommateur dort (Cas 3 : File vide)\n");
		  _unlock_();

		  s_wait(sem2);	// dort()

	  }
	  else
	  {
		  s_wait(semMutexConso);	
		  
		  _lock_();
		  printf("++++++> Lecture de %d = %d\n", i, fifo[i]);
		  _unlock_();

		  nb_places_libres++;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
		  
		 s_signal(semMutexConso);	

	  }

	  if (nb_places_libres==1)
	  {
		  _lock_();
		  puts("++++++> Reveil prod (Cas 4 : File non pleine)\n");
		  _unlock_();

		  s_signal(sem1);	// reveille(prod);
	  }

  }

  fin_tache();
}

TACHE	tacheConso2(void)
{
  uint16_t k,i=0;

  s_wait(sem2);	// dort()

  while(1)
  {
	  for (k=0; k<30000; k++);
	  //for (k=0; k<10000; k++);


	  //puts("------> Consommateur");

	  if (nb_places_libres==TAILLE_TABLEAU)
	  {
		  _lock_();
		  puts("++++++> Consommateur dort (Cas 3 : File vide)\n");
		  _unlock_();

		  s_wait(sem2);	// dort()

	  }
	  else
	  {
		  s_wait(semMutexConso);	
		  
		  _lock_();
		  printf("++++++> Lecture de %d = %d\n", i, fifo[i]);
		  _unlock_();

		  nb_places_libres++;

		  i++;
		  if (i==TAILLE_TABLEAU)
			  i=0;
		  
		  s_signal(semMutexConso);	

	  }

	  if (nb_places_libres==1)
	  {
		  _lock_();
		  puts("++++++> Reveil prod (Cas 4 : File non pleine)\n");
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
  puts("*******************DEBUT*********************\n\n\n\n\n");

  s_init();
  sem1 = s_cree(0);		// prod
  sem2 = s_cree(0);		// conso
  semMutexProd = s_cree(1);		// mutex entre les 2 producteurs pour les empecher de produire en même tps
  semMutexConso = s_cree(1);		// mutex entre les 2 conso pour les empecher de produire en même tps
  start(tacheStart);

  return(0);
}