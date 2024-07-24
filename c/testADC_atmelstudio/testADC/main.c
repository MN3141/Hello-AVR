#include <avr/io.h>
#include<util/delay.h>
#define  F_CPU 16000000UL
//we use a potentiometer and the 5V pin to simulate a battery or a sensor
int main(void)
{
	 ADMUX|=0x41;
		  //0100 AVCC reference
	      //0001 pin A1 on the Arduino board
	 ADCSRA|=0xC0;//1100 we set ADEN and ADSC bits
	 
	float resolution=5.0/1024;//for 5V reference
	float voltage=0;
    while (1) 
    {
		while(ADCSRA&(1<<6));//we are measuring while ADSC is 1
		short int val=ADCL|(ADCH<<8);//we can also set the ADC output on 8 bit mode
		voltage=val*resolution;
		ADCSRA|=1<<6;//after one measurement,ADSC becomes 0
		 //for further measurements we set ADSC to 1 again
		_delay_ms(50);
    }
}

