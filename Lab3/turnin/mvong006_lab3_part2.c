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
    unsigned char tmpC = 0x00;
   
    /* Insert your solution below */
    while (1) {
	tmpA = PINA;
	tmpC = 0x00;
	tmpA = tmpA & 0x0F;
	if (((tmpA & 0x01) == 0x01) || ((tmpA & 0x02) == 0x02)){
		tmpC = 0x60; // tmpC = 01100000
	}
	else if (((tmpA & 0x03) == 0x03) || ((tmpA & 0x04) == 0x04)){
		tmpC = 0x70; //tmpC = 01110000
	}
	else if (((tmpA & 0x05) == 0x05) || ((tmpA & 0x06) == 0x06)){
		tmpC = 0x38; //tmpC = 00111000
	}
	else if (((tmpA & 0x07) == 0x07) || ((tmpA & 0x08) == 0x08) || (tmpA & 0x09) == 0x09){
		tmpC = 0x3C; //tmpC = 00111100
	}
	else if (((tmpA & 0x0A) == 0x0A) || ((tmpA & 0x0B) == 0x0B) || ((tmpA & 0x0C) == 0x0C)){
		tmpC = 0x3E; //tmpC = 00111110
	}
	else if (((tmpA & 0x0D) == 0x0D) || ((tmpA & 0x0E) == 0x0E) || ((tmpA & 0x0F) == 0x0F)){
		tmpC = 0x3F; //tmpC = 00111111
	}
	else {
		tmpC = 0x40; //tmpC = 01000000
	}
	PORTC = tmpC;
    }
	
    return 0;
}
