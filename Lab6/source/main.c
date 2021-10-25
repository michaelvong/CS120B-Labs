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
#include <avr/interrupt.h>
#endif

enum States{start, led0, led1, led2} state;

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	_avr_timer_cntcurr = _avr_timer_M;
	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR(){
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

void TimerSet (unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void TickFct(){
	switch(state){
		case start:
			state = led0; //first led
			break;
		case led0:
			state = led1; //second led
			break;
		case led1:
			state = led2; //third led
			break;
		case led2:
			state = led0; //back to first
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case start:
			break;
		case led0:
			PORTB = 0xFE; //light 1
			break;
		case led1:
			PORTB = 0xFD; //light2
			break;
		case led2:
			PORTB = 0xFB; //light3
			break;
		default:
			PORTB = 0xFF;
			break;
	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
	    
    TimerSet(100);
    TimerOn();
    /* Insert your solution below */
    while (1) {
	TickFct();
	while(!TimerFlag) {};
	TimerFlag = 0;
    }
	
    return 0;
}
