/*
 * led.c
 *
 *  Created on: 31 mars 2017
 *      Author: mi11p008
 */

void setMaskOr(int* adr, int mask)
{
	*adr |= mask;
}

void setMaskAnd(int* adr, int mask)
{
	*adr &= mask;
}


/*void clearBitGius_d()
{
	*gius_d |= ~(1 << 31);
}*/


