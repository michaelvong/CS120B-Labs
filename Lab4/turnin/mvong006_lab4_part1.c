/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 4  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, Press, Release, noPress, noRelease} state;

void TickFct(){
	switch(state){
		case Start:
		       state = Press;
	               break;
		case Press:
			if ((PINA & 0x01) == 0x01){
				state = Press;
			}		
			else{
				state = Release;
			}
			break;
		case Release:
			if ((PINA & 0x01) == 0x01){
				state = noPress;
			}
			else{
				state = Release;
			}
			break;
		case noPress:
			if ((PINA & 0x01) == 0x01){
				state = noPress;
			}
			else {
				state = noRelease;
			}
			break;
		case noRelease:
			if ((PINA & 0x01) == 0x01){
				state = Press;
			}
			else {
				state = noRelease;
			}
			break;
		default:
			state = Start;
			break;
	}


	switch (state){
		case Start:
			PORTB = 0x01;
			break;
		case Press:
			PORTB = 0x01;
			break;
		case Release:
			break;
		case noPress:
			PORTB = 0x02;
			break;
		case noRelease:
			break;
		default:
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
