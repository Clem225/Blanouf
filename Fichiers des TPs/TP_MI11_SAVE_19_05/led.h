/*
 * led.h
 *
 *  Created on: 31 mars 2017
 *      Author: mi11p008
 */

#ifndef LED_H_
#define LED_H_

int mask = 1 << 31;

int* gius_d = (int * ) 0x0021C320;

int* ocr1_d = (int * ) 0x0021C304;
int* ocr2_d = (int * ) 0x0021C308;

int* dr_d = (int * ) 0x0021C31C;

int * ddir_d = 0x0021C300;

int * tctl = 0x00202000;
int * tprer = 0x00202004;
int * tcmp = 0x00202008;
int * tstat = 0x00202014;

int * intennum = 0x00223008;

void setMaskOr(int* adr, int mask);
void setMaskAnd(int* adr, int mask);

#endif /* LED_H_ */
