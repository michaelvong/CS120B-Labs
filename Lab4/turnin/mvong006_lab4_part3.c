/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {set, init, pound, buttonY, unlockButtonY, locked} state;

void TickFct(){
	switch(state){
		case set:
			state = init;
			break;
		case init:
			if ((PINA & 0x07) == 0x04){
				state = pound;
			}
			else if ((PINA & 0x87) == 0x80){
				state = locked;
			}
			else {
				state = init;
			}
			break;
		case pound:
			if ((PINA & 0x07) == 0x04){
				state = pound;
			}
			else {
				state = buttonY;
			}
			break;
		case locked:
			if ((PINA & 0x87) == 0x80){
				state = locked;
			}
			else {
				state = init;
			}
		case buttonY:
			if ((PINA & 0x07) == 0x02){
				state = unlockButtonY;
			}
			else if (PINA == 0x00){
				state = buttonY;
			}
			else {
				state = init;
			}
			break;
		case unlockButtonY:
			if ((PINA & 0x07) == 0x02){
				state = unlockButtonY;
			}
			else {
				state = init;
			}
			break;
	}

	switch(state){
		case set:
			PORTB = 0x00;
			break;
		case init:
			break;
		case locked:
			PORTB = 0x00;
			break;
		case buttonY:
			break;
		case pound:
			break;
		case unlockButtonY:
			PORTB = 0x01;
			break;
	}
}



int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0xFF;
    PORTC = 0x00;
		 
    /* Insert your solution below */
    while (1) {
	TickFct();
    }
	
    return 0;
}
