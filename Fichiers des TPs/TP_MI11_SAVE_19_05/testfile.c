/*
 * testfile.c
 *
 *  Created on: 19 mai 2017
 *      Author: mi11p008
 */

#include "noyaufil.h"

int main()
{
	file_init();

	ajoute(3);
	ajoute(5);
	ajoute(1);
	ajoute(0);
	ajoute(2);

	affic_file();

	affic_queue();
	suivant();
	affic_queue();

	affic_file();

	retire(0);
	affic_file();
	ajoute(6);
	affic_file();

	return 0;
}

