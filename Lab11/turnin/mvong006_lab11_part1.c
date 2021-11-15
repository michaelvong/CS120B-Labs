/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 11  Exercise 1
 *	Exercise Description: [optional - include for your own benefit]
 *      Demo: 
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *      #comment - not sure if my speaker is bad, but when i press the button rather than a smooth speaker sound coming out, it comes out in clicks. not sure what the problem is
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#include <timer.h>
#include <keypad.h>
#include <io.h>
#include <scheduler.h>
#endif

unsigned char x = 0x00;
unsigned char keypad = 0x00;

enum KeypadStates {start, init};

int KeypadTick(int state){
	x = GetKeypadKey();
	switch(state){
		case start:
			state = init;
			break;
		case init:
			state = init;
			break;
		default:
			state = start;
			break;
	}

	switch(state){
		case start:
			break;
		case init:
			switch(x){
				case '\0': keypad = 0x1F; break;
				case '1':	keypad = 0x01; break;
				case '2':	keypad = 0x02; break;
				case '3':	keypad = 0x03; break;
				case '4':	keypad = 0x04; break;
				case '5':	keypad = 0x05; break;
				case '6':	keypad = 0x06; break;
				case '7':	keypad = 0x07; break;
				case '8':	keypad = 0x08; break;
				case '9':	keypad = 0x09; break;
				case 'A':	keypad = 0x0A; break;
				case 'B':	keypad = 0x0B; break;
				case 'C':	keypad = 0x0C; break;
				case 'D':	keypad = 0x0D; break;
				case '*':	keypad = 0x0E; break;
				case '0':	keypad = 0x00; break;
				case '#':	keypad = 0x0F; break;
				default:	keypad = 0x1B; break;
			}
			PORTB = keypad;
			break;
		default:
			break;
	}
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRC = 0xF0;
    PORTC = 0x0F;
    /* Insert your solution below */

    static task task1;
    task *tasks[] = { &task1 };

    const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
    const char start = 0;

    task1.state = start;
    task1.period = 50;
    task1.elapsedTime = task1.period;
    task1.TickFct = &KeypadTick;

    TimerSet(50);
    TimerOn();

    unsigned short i;

    while (1) {
	    for (i=0; i<numTasks; i++){
		    if (tasks[i]->elapsedTime == tasks[i]->period){
			    tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			    tasks[i]->elapsedTime = 0;
		    }
		    tasks[i]->elapsedTime += 50;
	    }

	    while(!TimerFlag);
	    TimerFlag = 0;
    }
    return 0;
}
