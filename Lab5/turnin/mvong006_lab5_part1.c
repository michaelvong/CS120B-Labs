/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 1
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
	
    unsigned char fuel = 0x00;
    unsigned char led = 0x00;    
    /* Insert your solution below */
    while (1) { 
	fuel = ~PINA & 0x0F; //PA3-PA0
	if (fuel == 0){
		led = 0x40; //low fuel light on: 0 1 000000
	}
	else if (fuel < 0x03){
		led = 0x60; //light and PC5: 0 1 100000
	}
	else if (fuel < 0x05){
		led = 0x70; //light and PC5, PC4: 0 1 110000
	}
	else if (fuel < 0x07){
		led = 0x38; //PC5, PC4, PC3: 0 0 111000
	}
	else if (fuel < 0x0A){
		led = 0x3C; //PC5, PC4, PC3, PC2: 0 0 111100
	}
	else if (fuel < 0x0D){
		led = 0x3E; //0 0 111110
	}
	else {
		led = 0x3F; //0 0 111111
	}
	PORTC = led;
	fuel = 0x00;
    }
	
    return 0;
}
