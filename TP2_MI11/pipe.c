/*
 * pipe.c
 *
 *  Created on: 2 juin 2017
 *      Author: mi11p008
 */

/*Permet d'initialiser le tableau de pipe tel que
tous les pipes soient inutlisés */

#include "pipe.h"
#include "noyau.h"
#define TAILLE_MESSAGE 10


//TACHE tacheStart();
TACHE tacheA();
TACHE tacheB();
uint16_t tA, tB;
int pipe1, pipe2;


void init_pipes()
{
	unsigned int i;
	for (i=0;i<MAX_PIPES;i++)
		_pipe[i].pr_w=MAX_TACHES; //Tube inutilisé
}




/*Ouvre un nouveau pipe*/
unsigned int p_open(unsigned int redacteur, unsigned int lecteur)
{
	//VérifIER si les tâches sont créées
	if (_contexte[redacteur].status == NCREE || _contexte[lecteur].status == NCREE)
		return -1;

	//Vérifier qu’il n’existe pas de tube avec ces 2 taches
	unsigned int i;
	for (i=0 ; i<MAX_PIPES ; i++)
	{
		if (_pipe[i].pr_w == redacteur && _pipe[i].pr_r == lecteur)
			//Il existe un tube avec ces 2 taches
			return -1;
	}

	//Trouver un tube non utilisé
	i=0;
	while ( (_pipe[i].pr_w != MAX_TACHES) && (i < MAX_PIPES) )
		i++;
	if (i == MAX_PIPES) //Aucun tube n'est libre
		return -2;

	//Initialisation du tube
	_pipe[i].pr_w = redacteur;
	_pipe[i].pr_r = lecteur;
	_pipe[i].is = _pipe[i].ie = 0;
	_pipe[i].ocupp = 0; //Données restantes (0 au départ)


	//Retourner le numéro du tube créé
	return i;
}


/*Ferme un pipe*/
void p_close (unsigned int conduit)
{
	_pipe[conduit].pr_w = MAX_TACHES;
	/* FAUT-IL SUPPRIMER LES VALEURS DU TABLEAU tube ?*/
}

/*Lit un certain nombre de données sur un pipe*/
void p_read  (int tube, uchar* donnees, int quantite)
{
	//Vérifier que le tube existe et que la tâche en est propriétaire
	if ( (_pipe[tube].pr_r != _tache_c) )
	{
		printf("Tache non autorisee a lire dans le pipe\n");
		return;
	}

	//Lire les données à partir du tampon
	int i = 0;
	for (i=0 ; i < quantite ; i++)
	{
		//Vérifier que le tampon n’est pas vide, sinon endormir la tache
		if (_pipe[tube].ocupp == 0)
		{
			printf("Tampon vide ==> endormissement de la tache %d\n", _pipe[tube].pr_r);
			dort();
		}

		donnees[i] = _pipe[tube].tube[_pipe[tube].is];
		_pipe[tube].is++;
		_pipe[tube].ocupp--;

		/*Si  le  tube  était  plein  et  si
		la  tâche  écrivain  est  suspendue	sur  une
		écriture  dans  ce  tube alors la réveiller */
		if ( (_pipe[tube].ocupp+1 == SIZE_PIPE) && (_contexte[_pipe[tube].pr_w].status == SUSP) )
			reveille(_pipe[tube].pr_w);
	}


}


/*Ecrit un certain nombre de données sur un pipe*/
void p_write(int tube, uchar* donnees, int quantite)
{
	//Vérifier que le tube existe et que la tâche en est propriétaire
	if ( (_pipe[tube].pr_w != _tache_c) )
	{
		printf("Tache non autorisee a ecrire dans le pipe\n");
		return;
	}

	//Copie des données dans le tube
	int i;
	for (i=0 ; i < quantite ; i++)
	{
		//Vérifier qu’il y a de la place dans le tampon, sinon endormir la tache
		if (_pipe[tube].ocupp == SIZE_PIPE)
		{
			printf("Plus de place dans le tampon ==> endormissement de la tache %d\n", _pipe[tube].pr_w);
			dort();
		}

		//Copie des données
		_pipe[tube].tube[_pipe[tube].ie] = donnees[i];
		_pipe[tube].ie++;
		_pipe[tube].ocupp++;

		/*Si le tube était vide et si
		la tache lectrice est suspendue sur
		une lecture de ce tube alors la réveiller*/
		if ( (_pipe[tube].ocupp-1 == 0) && (_contexte[_pipe[tube].pr_r].status == SUSP) )
			reveille(_pipe[tube].pr_r);
	}

}







/*TACHE	tacheStart(void)
{
  puts("------> EXEC tache Start");

  init_pipes();
  puts("Pipes initialises\n");

  tA = cree(tacheA);
  tB = cree(tacheB);

  pipe1 = p_open(tA,tB);	// pipe de A vers B
  pipe2 = p_open(tB,tA);	// pipe de B vers A

  active(tA);
  active(tB);


  fin_tache();
}*/

TACHE tacheA()
{
	 puts("------> EXEC tache 1");

	 uint16_t k;
	 uchar envoiA[TAILLE_MESSAGE] = "salut";
	 uchar recuA[TAILLE_MESSAGE] = "";

	 for (k=0; k<30000; k++);

     p_write(pipe1,envoiA,5);

     _lock_();
     printf("Tache 1 a envoye : %s\n", envoiA);
	 _unlock_();

	 p_read(pipe2,recuA,5);

	 _lock_();
	 printf("Tache 1 message recu : %s\n", recuA);
	 _unlock_();


	 fin_tache();
}

TACHE tacheB()
{
	 puts("------> EXEC tache 2");

	 uint16_t k;
	 uchar recuB[TAILLE_MESSAGE] = "";

	 for (k=0; k<30000; k++);

	 p_read(pipe1,recuB,5);

	 _lock_();
      printf("Tache 2 message recu : %s\n", recuB);
	 _unlock_();

	 p_write(pipe2,recuB,5);

	 _lock_();
	 printf("Tache 2 a envoye : %s\n", recuB);
	 _unlock_();


	 fin_tache();
}





/*int main()
{
	serial_init(115200);
	puts("*******************DEBUT PIPE*********************\n\n");

	start(tacheStart);
}*/
