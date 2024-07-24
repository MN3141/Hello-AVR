#include <avr/io.h>

void setup()
{
	DDRB=0x3C;//the pins are configured after the schematic found on "schematic.pdf"
	DDRC=0x00;
	PORTB=0xFF;
	TCCR1A=0x00;
	TCCR1B=0x02;//10us timer
	TCNT1=0;
	OCR1A=20;
	TIMSK1=0x00;
}
void delay(uint16_t milis)
{
	//10us=0.01ms
	//10us*100=1ms
	for(uint16_t i=0;i<milis*100;i++)
	{
		while((TIFR1&0x02)!=0x02);
		TCNT1=0x0;
		TIFR1=0x02;
	}
}
void led_sequence0()
{
	for(int i=2;i<=5;i++)
	{
		PORTB^=(1<<i);
		delay(1000);
	}
	for(int i=5;i>=2;i--)
	{
		PORTB^=(1<<i);
		delay(1000);
	}
}
void led_sequence1()
{
	for(int i=5;i>=2;i--)
	{
		if((PINC&0x01)==0)//button pressed
		{
			PORTB=0x00;
			PORTB|=(1<<i);
		}
		else
		{
			PORTB=0xFF;
			PORTB^=(1<<i);
		}
		delay(3000);
	}
}
int main(void)
{
	setup();
	while (1)
	{
		led_sequence1();
	}
}

