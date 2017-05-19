/* NOYAUFILE.C */
/*--------------------------------------------------------------------------*
 *  gestion de la file d'attente des taches pretes et actives               *
 *  la file est rangee dans un tableau. ce fichier decrit toutes            *
 *  les primitives de base                                                  *
 *--------------------------------------------------------------------------*/
#include <stdint.h>
#include "serialio.h"
#include "noyau.h"

/* variables communes a toutes les procedures *
 *--------------------------------------------*/

static uint16_t  _file[MAX_TACHES];   /* indice=numero de tache */
				   /* valeur=tache suivante  */
static uint16_t  _queue;              /* valeur de la derniere tache */
				   /* pointe la prochaine tache a activer */

/*     initialisation de la file      *
 *------------------------------------*
entre  : sans
sortie : sans
description : la queue est initialisee vide, queue prend la valeur de tache
	      impossible
*/

void	file_init( void )
{
	_queue = F_VIDE;
}

/*        ajouter une tache dans la pile      *
 *--------------------------------------------*
entree : n numero de la tache a entrer
sortie : sans
description : ajoute la tache n en fin de pile
*/

void	ajoute ( uint16_t n )
{
	if(n > MAX_TACHES - 1)
		return;

	if(_queue == F_VIDE)
	{
		_queue = n;
		_file[_queue] = n;
	}
	else
	{
		uint16_t tmp = _file[_queue];
		_file[_queue] = n;
		_file[n] = tmp;
	}
}

/*           retire une tache de la file        *
 *----------------------------------------------*
entree : t numero de la tache a sortir
sortie : sans
description: sort la tache t de la file. L'ordre de la file n'est pas
	     modifie
*/

void	retire( uint16_t t )
{
	int i = 0;

	while(_file[i] != t)
		i++;				// i = prédecesseur de t ( 1 -> 0 -> 2 ) => avec t = 0, i = 1

	_file[i] = _file[t];	// 1 -> 2
}


/*        recherche du suivant a executer       *
 *----------------------------------------------*
entree : sans
sortie : t numero de la tache a activer
description : la tache a activer est sortie de la file. queue pointe la
	      suivante
*/
uint16_t	suivant( void )
{
	_queue = _file[_queue];
	return _queue;
}

/*     affichage du dernier element     *
 *--------------------------------------*
entree : sans
sortie : sans
description : affiche la valeur de queue
*/

void affic_queue( void )
{
	printf("Queue : %d", _file[_queue]);
}

/*     affichage de la file     *
 *------------------------------*
entree : sans
sortie : sans
description : affiche les valeurs de la file
*/

void affic_file( void )
{
	int i = 0;

	for(i = 0; i < MAX_TACHES; i++)
	{
		printf("%d -> ", _file[i] );
	}

	printf("\n");
}
