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

enum States {init, start, set, reset, plus, minus, toPlus, toMinus} state;

void TickFct(){
	switch(state){
		case init:
			state = start;
			break;
		case start:
			state = set;
			break;
		case set:
			if ((PINA & 0x03) == 0x03){
				state = reset;
			}
			else if ((PINA & 0x02) == 0x02){
				state = toMinus;
			}
			else if ((PINA & 0x01) == 0x01){
				state = toPlus;
			}
			break;
		case toPlus:
			state = plus;
			break;
		case plus:
			if ((PINA & 0x01) == 0x01){
				state = plus;
			}
			else {
				state = set;
			}
			break;
		case toMinus:
			state = minus;
			break;
		case minus:
			if ((PINA & 0x02) == 0x02){
				state = minus;
			}
			else {
				state = set;
			}
			break;
		case reset:
			if ((PINA & 0x03) == 0x03){
				state = reset;
			}
			else {
				state = set;
			}
			break;
		default:
			state = start;
			break;
	}


	switch(state){
		case init:
			break;
		case start:
			PORTC = 0x07;
			break;
		case set:
			break;
		case plus:
			break;
		case toPlus:
			if (PORTC < 0x09){
				PORTC = PORTC + 1;
			}
			break;
		case minus:
			break;
		case toMinus:
			if (PORTC > 0x00){
				PORTC = PORTC - 1;
			}
			break;
		case reset:
			PORTC = 0x00;
			break;
		default:
			PORTC = 0x07;
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
