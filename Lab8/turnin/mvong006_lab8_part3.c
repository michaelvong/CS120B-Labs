/*	Author: Michael Vong
 *  Partner(s) Name: none
 *	Lab Section:
 *	Assignment: Lab 8  Exercise 3
 *	Exercise Description: [optional - include for your own benefit]
 *      Demo:
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
    unsigned short max = 0xFF;
    ADC_init();
    /* Insert your solution below */
    while (1) {
	a = ADC;
	unsigned char temp = (char)a;
	if (temp >= max/2){
		PORTB = 0xFE;
	}
	else {
		PORTB = 0xFF;
	}
    }
	
    return 0;
}
