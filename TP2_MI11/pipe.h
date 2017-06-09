/*
 * pipe.h
 *
 *  Created on: 2 juin 2017
 *      Author: mi11p008
 */

#ifndef PIPE_H_
#define PIPE_H_

#include "noyau.h"


#define MAX_PIPES 5
#define SIZE_PIPE 10


typedef struct
{
	ushort pr_w , pr_r ; /* redacteur & lecteur du tube */
	ushort ocupp ;  /* donnees restantes */
	uchar is, ie ;    /* pointeurs d’entree / sortie */
	uchar tube[SIZE_PIPE] ; /* Tampon */
} PIPE;

PIPE  _pipe[MAX_PIPES] ;   /* Variables tubes */


unsigned int p_open(unsigned int redacteur, unsigned int lecteur); //Allocation du conduit
void p_close (unsigned int conduit); //Libération du tube
void p_read  (int tube, uchar* donnees, int quantite); //Lecture dans un tube
void p_write(int tube, uchar* donnees, int quantite); //Ecriture dans un tube

//Ajouts

void init_pipes();

#endif /* PIPE_H_ */
