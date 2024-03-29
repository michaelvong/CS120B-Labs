/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 2
 *	Exercise Description: [optional - include for your own benefit]
 *      Demo: https://drive.google.com/file/d/1fPpXnjWQMHl7CJRrXwRz-J6KiSCAh64i/view?usp=sharing
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include <avr/interrupt.h>
#endif


void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRB = 0xFF;
    PORTB = 0x00;
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRD = 0xFF;
    PORTD = 0x00;
    unsigned short a = 0x00;
    ADC_init();
    /* Insert your solution below */
    while (1) {
	a = ADC;
	PORTB =(char)a;
	PORTD = (char)(a>>8);
    }
	
    return 0;
}
