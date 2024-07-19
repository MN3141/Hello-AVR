#include <avr/io.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#define  F_CPU 16000000UL
volatile uint8_t lastState=0;
volatile uint8_t currentState=0;
ISR(PCINT2_vect)
{
	currentState=PIND&4;
	if(currentState!=lastState)
	{
		lastState=currentState;
		if(currentState)
		PORTD^=(1<<3);//toggling the LED using XOR
	}
}
int main(void)
{
    DDRD=0x08;
    PORTD=0x04;
	PCICR=0x04;//PORTD is selected for interrupts
	PCMSK2=0x08;//PIN3 is selected for the interrupt
    while (1)
    {
		
    }
}

