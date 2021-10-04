/*	Author: lab
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    unsigned char tmpB = 0x00;
    unsigned char tmpA = 0x00;
    unsigned char tmpC = 0x00;
    unsigned char tmpD = 0x00;
    unsigned char tmpE = 0x00;
    unsigned char updateD = 0x00;
    unsigned short totalWeight = 0x0000;
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	tmpB = PINB;
	tmpC = PINC;
	tmpD = 0x00;
	tmpE = 0x00;
	
	totalWeight = tmpA + tmpB + tmpC;
	if (totalWeight > 0x008C){
		tmpD = 0x01;
	}
	else{
		tmpD = 0x00;
	}


	if (tmpA > tmpC){
		if((tmpA -tmpC) > 0x50){
			tmpE = 0x02;
		}
	}
	else{
		if((tmpC - tmpA) > 0x50){
			tmpE = 0x02;
		}
	}

	updateD = (totalWeight & 0x00FC) | tmpD | tmpE;
	PORTD = updateD;
    }
    return 0;
}
