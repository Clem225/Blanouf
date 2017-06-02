/*
 * noyaufil.h
 *
 *  Created on: 19 mai 2017
 *      Author: mi11p008
 */

#ifndef NOYAUFIL_H_
#define NOYAUFIL_H_

#include <stdint.h>

void	file_init( void );
void	ajoute ( uint16_t n );
void	retire( uint16_t t );
uint16_t	suivant( void );
void affic_queue( void );
void affic_file( void );



#endif /* NOYAUFIL_H_ */
