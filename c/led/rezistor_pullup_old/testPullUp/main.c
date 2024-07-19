#define  F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	//OBS:DO NOT USE PIN13,PIN1 or PIN0 for pull-up
		 //because those will always output 5V
	 DDRD=0x08;//PIN3-OUTPUT,PIN2-INPUT
	 PORTD=0x04;//PIN2 HIGH
	  //PIN2 HIGH,INPUT =>INPUT PULL-UP
	 int buttonState=0;
    while (1) 
    {
		buttonState=PIND&4;
		if(!buttonState)
			PORTD|=(1<<3);
		else PORTD&=~(1<<3);
		_delay_ms(50);
    }
}

