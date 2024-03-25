#include <avr/io.h>
//OBS:TINKERCAD nu e bun pt temporizator
void setup_mode0()//1s delay
{
	DDRB=0x20;
	PORTB=0xFF;
	TCCR1A=0x00;//timer 1 is set on normal mode
	TCCR1B=0x04;//prescaler is set on 256
	TCNT1=0x00;//counting begins from 0
	OCR1A=62500;//counting stops here
	//OCCR1A=TimerPeriod/(prescaler*TimerClock)
	TIMSK1=0x00;
}
void setup_mode1()//10us delay
{
	DDRB=0x20;
	PORTB=0xFF;
	TCCR1A=0x00;
	TCCR1B=0x02;
	TCNT1=0;
	OCR1A=20;
	TIMSK1=0x00;
}
void delay0()
{
	while((TIFR1&0x02)!=0x02);//while the counting is still going on
	TCNT1=0x0;//due to the fact that we have selected counter mode
	//we have to manually reset TCNT1
	TIFR1=0x00;
}
void delay1(uint16_t milis)
{
	//10us=0.01ms
	//10us*100=1ms
	for(uint16_t i=0;i<milis*100;i++)
	{
		while((TIFR1&0x02)!=0x02);
		TCNT1=0x0;
		TIFR1=0x02;//registru problematic
				   //valoarea trb sa se reseteze
	}
}
int main(void)
{
	setup_mode1();
	while (1)
	{
		PORTB^=(1<<5);
		delay1(1000);
	}
}