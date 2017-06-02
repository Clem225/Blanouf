/*
 * sem.c
 *
 *  Created on: 26 mai 2017
 *      Author: mi11p008
 */

#include "noyau.h"
#include "sem.h"

SEMAPHORE _sem[MAX_SEM];

void s_init( void )
{
	int i;

	for(i = 0; i < MAX_SEM; i++)
	{
		_sem[i].valeur = -1000;		// -1 = pas créer
	}
}

ushort s_cree( short v )
{
	int i = 0;

	if (v >= MAX_TACHES)
		return -1;			// a voir (on retourne -1 en cas d'erreur ?)

	while(i<MAX_SEM && _sem[i].valeur != -1000)	// on cherche un emplacement libre
		i++;

	if(i >= MAX_SEM)
		return -1;			// a voir

	_sem[i].valeur = v;
	_sem[i].file.debut_file = 0;	// pas necessaire je pense
	_sem[i].file.fin_file = 0;

	return i;
}

void s_close( ushort n )
{
	if(n >= MAX_SEM || n < 0)
		return;

	_sem[n].valeur = -1000;
}

void s_wait( ushort n )
{
	if(n >= MAX_SEM || n < 0)
		return;

	if(_sem[n].valeur == -1000)
		return;

	_lock_();						// zone critique car si plusieurs tâches modifient le semaphore en meme temps => PLS

	_sem[n].valeur--;				// décrémenter e(s)

	if(_sem[n].valeur < 0)
	{
		_sem[n].file.taches[_sem[n].file.fin_file] = _tache_c;		// si e(s) < 0 alors bloquer la tâche ayant effectué la requête et mettre celle-ci dans la file f(s) ( à vérifier)
		_sem[n].file.fin_file = _sem[n].file.fin_file + 1;		// incrémente la fin de la file
		_sem[n].file.fin_file = (_sem[n].file.fin_file) % MAX_TACHES; // si fin_file < MAX_TACHES => fin_file sinon => on revient au debut de la file
	
		dort();	 //  C DANS LE IF PUTAIN !!!
	}

	_unlock_();
}

void s_signal ( ushort n )
{
	short tache;

	if(n >= MAX_SEM || n < 0)
		return;

	if(_sem[n].valeur == -1000)		// pas crée
		return;

	_lock_();						// zone critique car si plusieurs tâches modifient le semaphore en meme temps => PLS

	_sem[n].valeur++;				// incrémenter e(s)

	if(_sem[n].valeur <= 0)
	{
		tache = _sem[n].file.taches[_sem[n].file.debut_file]; 	// si e(s) <= 0 alors sortir une tâche de la file f(s) et la relancer (à vérifier)
		_sem[n].file.debut_file = _sem[n].file.debut_file + 1;		// incrémente début de la file
		_sem[n].file.debut_file = (_sem[n].file.debut_file) % MAX_TACHES; // si debut_file < MAX_TACHES => debut_file sinon => on revient à la fin de la file
	
		reveille(tache);		 //  C DANS LE IF PUTAIN !!!
	}

	_unlock_();
}
