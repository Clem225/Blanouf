/*
 * sem.h
 *
 *  Created on: 26 mai 2017
 *      Author: mi11p008
 */

#ifndef SEM_H_
#define SEM_H_

#include <stdint.h>

#define MAX_SEM 15
//#define ushort int

typedef struct {
  short taches[MAX_TACHES];
  short debut_file;
  short fin_file;
} FIFO;

typedef struct {
	FIFO file;     /* File circulaire des tâches en attente */
	short valeur ; /* compteur du sémaphore e(s) */
	short compteur;
} SEMAPHORE ;

void s_init( void );
ushort s_cree( short v );
void s_close( ushort n );
void s_wait( ushort n );
void s_signal ( ushort n );

#endif /* SEM_H_ */
