/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 3  Exercise 2
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
    DDRC = 0xFF;
    PORTC = 0x00;
		
    unsigned char tmpA = 0x00;
    unsigned char tmpB = 0x00;
    unsigned char tmpC = 0x00;
   
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;

	tmpB = (tmpA >> 4) & 0x0F; //rotate front bits to back and copy it
	tmpC = (tmpA  << 4) & 0xF0; //rotate and copy

	PORTB = tmpB;
	PORTC = tmpC;
	


    }
	
    return 0;
}
