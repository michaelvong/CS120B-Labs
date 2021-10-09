/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 1
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
    DDRB = 0x00;
    PORTB = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;

    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    unsigned char tmpC = 0x00;
    unsigned char tmpD = 0x01;
   
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	tmpB = PINB;
	tmpC = 0x00; //counter
	tmpD = 0x01; //this will be compared to tmpA

	int i = 0;
	int amountBits = 8;
	for (i=0; i<=amountBits; i++){
		if ((tmpA & tmpD) == tmpD){
			tmpC = tmpC + 1;
		}
		if ((tmpB & tmpD) == tmpD){
			tmpC = tmpC + 1;
		}	
		tmpD = tmpD * 2;
	}
	PORTC = tmpC - 2;
    }
	
    return 0;
}
