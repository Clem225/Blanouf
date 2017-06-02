/*
 * pipe.c
 *
 *  Created on: 2 juin 2017
 *      Author: mi11p008
 */

/*Permet d'initialiser le tableau de pipe tel que
tous les pipes soient inutlisés */

#include "pipe.h"

void init_pipes()
{
	int i = 0;
	for (int i;i<MAX_PIPES;i++)
		_pipe[i].pr_w=MAX_TACHES; //Tube inutilisé
}




/*Ouvre un nouveau pipe*/
unsigned p_open(unsigned redacteur, unsigned lecteur)
{
	if (/*Vérif si les tâches ne sont pas créées*/)
		return -1;

	//Vérifier qu’il n’existe pas de tube avec ces 2 taches
	int i = 0 ;
	for (int i ; i<MAX_PIPES ; i++)
	{
		if (_pipe[i].pr_w == redacteur && _pipe[i].pr_r == lecteur)
			//Il existe un tube avec ces 2 taches
			/* QUESTION : Dans l'autre sens possible ? Avec une autre tache possible ? */
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
void p_close (unsigned conduit)
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
		printf("Tache non autorisee a lire dans le pipe");
		return;
	}

	//Lire les données à partir du tampon
	int i = 0;
	for (int i ; i < quantite ; i++)
	{
		//Vérifier que le tampon n’est pas vide, sinon endormir la tache
		if (_pipe[tube].ocupp == 0)
		{
			printf("Tampon vide ==> endormissement de la tache %d", _pipe[tube].pr_r);
			dort();
		}

		donnees[i] = _pipe[tube].tube[_pipe[tube].is];
		_pipe[tube].is++;
		_pipe[tube].ocupp--;

		/*Si  le  tube  était  plein  et  si
		la  tâche  écrivain  est  suspendue	sur  une
		écriture  dans  ce  tube alors la réveiller */
		if ( (_pipe[tube].occup+1 == SIZE_PIPE) && (_pipe[tube].pr_w est suspendue une écriture dans ce tube) )
			reveille(_pipe[tube].pr_w);
	}
}


/*Ecrit un certain nombre de données sur un pipe*/
void p_write(tube, donnees, quantité)
{
	//Vérifier que le tube existe et que la tâche en est propriétaire
	if ( (_pipe[tube].pr_w != _tache_c) )
	{
		printf("Tache non autorisee a ecrire dans le pipe");
		return;
	}

	//Copie des données dans le tube
	int i = 0;
	for (int i ; i < quantite ; i++)
	{
		//Vérifier qu’il y a de la place dans le tampon, sinon endormir la tache
		if (_pipe[tube].occup == SIZE_PIPE)
		{
			printf("Plus de place dans le tampon ==> endormissement de la tache %d", _pipe[tube].pr_w);
			dort();
		}

		//Copie des données
		_pipe[tube].tube[_pipe[tube].ie] = donnees[i];
		_pipe[tube].ie++;
		_pipe[tube].occup++;

		/*Si le tube était vide et si
		la tache lectrice est suspendue sur
		une lecture de ce tube alors la réveiller*/
		if ( (_pipe[tube].occup-1 == 0) && (_pipe[tube].pr_r est suspendue sur une lecture de ce tube) )
			reveille(_pipe[tube].pr_r);
	}
}
