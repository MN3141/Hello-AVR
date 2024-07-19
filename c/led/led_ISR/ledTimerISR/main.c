#include <avr/io.h>
#include <avr/interrupt.h>
//#define cli() asm volatile("cli"::)
//#define sei() asm volatile("sei"::)
//ele sunt definite in avr/interrupt.h
//practic ele modifica valoarea bitului I din registrul SREG
volatile int counter=5;
void setup()
{
	DDRB=0x3C;//the pins are configured after the schematic found on "schematic.pdf"
	DDRC=0x00;
	PORTB=0xFF;
	TCCR1A=0x00;
	TCCR1B=0x04;
	OCR1A=62500;//1s timer
	TCNT1=0;
	TIMSK1=0x02;
}
ISR(TIMER1_COMPA_vect)
{
	TCNT1=0;
	if(counter==2)
	counter=5;
	else counter--;
	
}
int main(void)
{
	cli();//echivalent cu noInterrupts();
	setup();
	sei();//echivalent cu interrupts()
	while (1)
	{
		PORTB=0xFF;
		if((PINC&0x01)==0)
			PORTB&=(1<<counter);
		else
			PORTB^=(1<<counter);
		
	}
}

