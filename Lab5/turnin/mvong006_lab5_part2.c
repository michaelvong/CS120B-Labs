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

enum States {init, set, plus, minus, check, check2} state;

void TickFct(){
	switch(state) {
		case init:
			PORTC = 0x07;
			state = set;
			break;
		case set:
			if ((~PINA & 0x01) == 0x01){
				state = plus;
			}
			else if ((~PINA & 0x02) == 0x02){
				state = minus;
			}
			else {
				state = set;
			}
			break;
		case plus:
			state = check;
			break;
		case minus:
			state = check2;
			break;
		case check:
			if ((~PINA & 0x01) == 0x01){
				state = check;
			}
			else {
				state = set;
			}
			break;
		case check2:
			if ((~PINA & 0x02) == 0x02){
				state = check2;
			}
			else {
				state = set;
			}
		default:
			state = init;
			break;
	}

	switch(state){
		case init:
			break;
		case set:
			if ((~PINA & 0x03) == 0x03) {
				PORTC = 0;
			}
			break;
		case plus:
			if (PORTC < 0x09){
				PORTC = PORTC + 1;
			}
			break;
		case minus:
			if (PORTC > 0x00){
				PORTC = PORTC - 1;
			}
			break;
		case check:
			if ((~PINA & 0x03) == 0x03) {
				PORTC = 0;
			}
			break;
		case check2:
			if ((~PINA & 0x03) == 0x03){
				PORTC = 0;
			}
			break;
		default:
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
