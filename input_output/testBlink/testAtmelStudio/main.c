#define  F_CPU 16000000UL
#include <avr/io.h>
#include<util/delay.h>
int main (void)
{
	DDRD=DDRD|1;//setare mod pin 0
	while(1)
	{
		PORTD=PORTD|1;//setare pin 0 HIGH
		//delay(100); delay() are nevoie de functia setup ca sa functioneze
		_delay_ms(1000);
		PORTD=PORTD & 11111110;
		_delay_ms(1000);
	}
	return 0;
}
