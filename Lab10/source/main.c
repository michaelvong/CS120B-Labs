/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *      Demo:https://drive.google.com/file/d/1yBmIu979UIzhhkhQjzNEWHFK_-z2Mn8c/view?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#endif

enum ThreeLEDStates {ThreeStart, zero, one, two} ThreeLEDState;
enum BlinkingLEDStates {BlinkingStart, BlinkInit, blink} BlinkingLEDState;
enum CombineLEDStates {CombineStart, CombineInit} CombineLEDState;

unsigned char threeLEDs = 0x00;
unsigned char blinkingLED = 0x00;

volatile unsigned char TimerFlag = 0;

void TimerISR(){
	TimerFlag = 1;
}

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
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

void ThreeLEDTick(){
	switch(ThreeLEDState){
		case ThreeStart:
			ThreeLEDState = zero;
			break;
		case zero:
			ThreeLEDState = one;
			break;
		case one:
			ThreeLEDState = two;
			break;
		case two:
			ThreeLEDState = zero;
			break;
		default:
			ThreeLEDState = ThreeStart;
			break;
	}

	switch(ThreeLEDState){
		case ThreeStart:
			break;
		case zero:
			threeLEDs = 0x01;
			break;
		case one:
			threeLEDs = 0x02;
			break;
		case two:
			threeLEDs = 0x04;
			break;
		default:
			break;
	}
}

void BlinkingTick(){
	switch(BlinkingLEDState){
		case BlinkingStart:
			BlinkingLEDState = BlinkInit;
			break;
		case BlinkInit:
			BlinkingLEDState = blink;
			break;
		case blink:
			BlinkingLEDState = BlinkInit;
			break;
		default:
			BlinkingLEDState = BlinkingStart;
			break;
	}

	switch(BlinkingLEDState){
		case BlinkingStart:
			break;
		case BlinkInit:
			blinkingLED = 0x00;
			break;
		case blink:
			blinkingLED = 0x01;
			break;
		default:
			break;
	}
}


void CombineTick(){
	switch(CombineLEDState){
		case CombineStart:
			CombineLEDState = CombineInit;
			break;
		case CombineInit:
			CombineLEDState = CombineInit;
			break;
		default:
			CombineLEDState = CombineStart;
	}

	switch(CombineLEDState){
		case CombineStart:
			break;
		case CombineInit:
			PORTB = ((blinkingLED << 3) | (threeLEDs));
			break;
		default:
			break;
	}
}




int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRD = 0xFF;
    PORTD = 0x00;
    /* Insert your solution below */
    unsigned long elapsed = 0;
    const unsigned long timerPeriod = 1000;
    TimerSet(150);
    TimerOn();
    ThreeLEDState = ThreeStart;
    BlinkingLEDState = BlinkingStart;
    CombineLEDState = CombineStart;
    while (1) {
	    ThreeLEDTick();
	    BlinkingTick();
	    CombineTick();
	    while(!TimerFlag){};
	    TimerFlag = 0;
    }
	
    return 0;
}
