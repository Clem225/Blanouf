/*
 * tp2.c

 *
 *  Created on: 24 mars 2017
 *      Author: mi11p008
 */

#include "led.h"

int a;	// section COM

int b = 1;	// .data

static int c;	// .bss

char *s = "Salut";	// *s : .data | "Salut" : .rodata

#define irq_enable()           \
asm volatile(               \
"mrs    r0,cpsr\t\n"     \
"bic    r0,r0,#0x80\t\n" \
"msr    cpsr_c,r0\t\n"   \
:                        \
:                        \
: "r0")

#define irq_disable()          \
asm volatile(               \
"mrs    r0,cpsr\t\n"     \
"orr    r0,r0,#0x80\t\n" \
"msr    cpsr_c,r0\t\n"   \
:                        \
:                        \
: "r0")

void __attribute__((interrupt("IRQ"))) irq_handler(void)
{

	setMaskAnd(tstat, 0x00000000);		// on remet comp à 0

	//setMaskAnd(ddir_d, ~mask);			// eteindre led
	*ddir_d = *ddir_d ^ 1 << 31;

}

int main()	// .text
{
	int i=0;

	/*c = 42;
	a = a + b + c + s[1] + f();	// f() : UNDEF*/

	*intennum = 59;						// timer 1 = source d'interruption = 59
	irq_enable();

	setMaskOr(gius_d, mask);
	setMaskOr(ocr1_d, 0xC0000000);
	setMaskAnd(dr_d, ~mask);

	setMaskAnd(tprer, 0x0);

	setMaskAnd(tcmp, 0x00000000);		// tcmp est à 0xFFFFFFFF ==> 0x00000000
	setMaskOr(tcmp, 0x0007A120);		// on met le compteur à 500 000
	setMaskOr(tctl, 0x00000004);		// on choisit 1 Mhz de frequence (PERCLK/16 ==> voir doc)

	setMaskOr(ddir_d, mask);			// allumer led

	setMaskOr(tctl, 0x00000011);		// demarrer compteur

	while(1)
	{

		/*while((*tstat | 0x00000001) != *tstat)	// tant que comp à 0 on attend
		{

		}

		//setMaskAnd(tstat, 0x00000000);		// on remet comp à 0

		//setMaskAnd(ddir_d, ~mask);			// eteindre led

		while((*tstat | 0x00000001) != *tstat)	// tant que comp à 0 on attend
		{

		}

		//setMaskAnd(tstat, 0x00000000);		// on remet comp à 0

		//setMaskOr(ddir_d, mask);			// allumer led*/

	}

	/*while(1)
	{
		setMaskOr(ddir_d, mask);

		while()
			i++;

		i = 0;

		setMaskAnd(ddir_d, ~mask);

		while(i<1000000)
			i++;

		i = 0;

	}*/


	return a;
}
