/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 10  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *      Demo: https://drive.google.com/file/d/1lo_xYBovETO44vtdXTcobsWn9yhnBXb9/view?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *      #comment - not sure if my speaker is bad, but when i press the button rather than a smooth speaker sound coming out, it comes out in clicks. not sure what the problem is
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
unsigned char speaker = 0x00;

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
			PORTB = ((speaker << 4) | (blinkingLED << 3) | (threeLEDs));
			break;
		default:
			break;
	}
}

unsigned char i = 0;
enum SpeakerStates {SpeakerStart, off, on} SpeakerState;

void SpeakerTick(){
	switch(SpeakerState){
		case SpeakerStart:
			SpeakerState = off;
			break;
		case off:
			if ((~PINA & 0x01) == 0x01){
				SpeakerState = on;
			}
			else{
				SpeakerState = off;
			}
			break;
		case on:
			if ((~PINA & 0x01) == 0x00){
				SpeakerState = off;
			}
			else{
				SpeakerState = on;
			}
			break;
		default:
			SpeakerState = SpeakerStart;
			break;
	}


	switch(SpeakerState){
		case SpeakerStart:
			break;
		case off:
			speaker = 0x00;
			i = 0;
			break;
		case on:
			if (i<=2){
				speaker = 0x01;
			}
			else if (i<=4){
				speaker = 0x00;
			}
			else{
				i=0;
			}
			i++;
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
    unsigned long ThreeElapsed = 0;
    unsigned long BlinkElapsed = 0;
    const unsigned long timerPeriod = 100;
    TimerSet(10);
    TimerOn();
    ThreeLEDState = ThreeStart;
    BlinkingLEDState = BlinkingStart;
    CombineLEDState = CombineStart;
    while (1) {
	    if (ThreeElapsed >= 300){
		    ThreeLEDTick();
		    ThreeElapsed = 0;
	    }
	    if (BlinkElapsed >= 1000){
		    BlinkingTick();
		    BlinkElapsed = 0;
	    }
	    SpeakerTick();
	    CombineTick();
	    while(!TimerFlag){};
	    TimerFlag = 0;
	    ThreeElapsed += timerPeriod;
	    BlinkElapsed += timerPeriod;
    }
	
    return 0;
}
