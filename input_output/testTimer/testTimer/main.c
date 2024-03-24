#include <avr/io.h>
void setup_mode0()
{
	DDRB=0x20;
	TCCR1A=0x00;//timer 1 is set on normal mode
	TCCR1B=0x04;//prescaler is set on 256 
	TCNT1=0x00;//counting begins from 0
	OCR1A=62500;//counting stops here
	//OCCR1A=TimerPeriod/(prescaler*TimerClock)
	//1s delay
	TIMSK1=0x02;//for matching the counter with comparator A
}
void delay0()
{
	while((TIFR1&0x02)!=0x02);//while the counting is still going on
	TCNT1=0x0;//due to the fact that we have selected counter mode
			  //we have to manually reset TCNT1
	TIFR1=0x02;
}
int main(void)
{
    /* Replace with your application code */
    while (1) 
    {
    }
}

