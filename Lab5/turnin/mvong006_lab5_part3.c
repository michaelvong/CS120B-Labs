/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 5  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *      Video Demo: I was not able to get a demo due to missing resources. 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


enum States {start, stage1, stage2 } state;
unsigned char i = 0x00;
unsigned char arr[] = {0x00, 0x03, 0x0C, 0x30, 0x3F};

void TickFct(){
	unsigned char A = ~PINA & 0x01;
	switch(state) {
		case start:
			if (A == 0x01){
				state = stage1;
			}
			break;
		case stage1:
			if (A == 0x01){
				state = stage2;
				i++;
			}
			else {
				state = stage1;
			}
			break;
		case stage2:
			if (A == 0x01){
				state = stage2;
			}
			else {
				state = stage1;
			}
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case start:
			PORTC = 0x00;
			i = 0x00;
			break;
		case stage1:
			if(i == 0x06){
				i = 0x00;
			}
			PORTC = arr[i];
			break;
		case stage2:
			break;
		default:
			i = 0x00;
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
