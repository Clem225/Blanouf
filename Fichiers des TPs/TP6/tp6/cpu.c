#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
 
#define TAILLE 10000

int main()
{
	int j = 0, min, max, moy = 0, tempstotal = 0;
	int tab[TAILLE];
	struct timeval debut, fin, res;
		
	for(j = 0; j < TAILLE; j++)
	{
		gettimeofday(&debut, NULL);

		usleep(1000);

		gettimeofday(&fin, NULL);

		timersub(&fin, &debut, &res);

		tab[j] = res.tv_sec* 1000000 + res.tv_usec;

		moy += tab[j];
	}

	/*for (j=0;j<TAILLE;j++)
		tempstotal+=tab[j];
	printf("%d\n", tempstotal);*/

	moy = moy / TAILLE - 1000;
	min = tab[0];
	max = tab[0];

	for(j = 1; j < TAILLE; j++)
	{
		if(min > tab[j])
			min = tab[j];

		if(max < tab[j])
			max = tab[j];
	}
	
	min-=1000;
	max-=1000;

	printf("Moyenne : %d\nMaximum : %d\nMinimum : %d\n", moy, max, min);

	return 0;
}
