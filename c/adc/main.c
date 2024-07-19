#include <avr/io.h>
#include <avr/interrupt.h>
#define COEF 5
volatile static uint8_t convertDone=1;

ISR(ADC_vect){
	convertDone =1;
}

int main(void)
{
	DDRD |=0xFC;
	DDRB |= 1;
	DIDR0 |=(1<<ADC0D);
	ADMUX |=(1<<REFS0);
	ADCSRA |=(1<<ADEN)|(0b111<<ADPS0)|(1<<ADIE)|(1<<ADSC);
	sei();
	uint16_t result=0;
	
    while (1){
		if(convertDone == 1){
			//D D D D D D B
			//2 3 4 5 6 7 0
			//G F A B E D C
			result=ADCL|(ADCH<<8);
			uint16_t a = result*COEF;
			if(a<1000 && a>=0)	 {PORTD=0xF8;	PORTB=1;}
			if(a<2000 && a>=1000){PORTD=(1<<5); PORTB=1;}
			if(a<3000 && a>=2000){PORTD=0xF4;	PORTB=0;}
			if(a<4000 && a>=3000){PORTD=0xB4;	PORTB=1;}
			if(a<5000 && a>=4000){PORTD=0x2c;	PORTB=1;}
			//if(a<=5000 && a>4000){PORTD=0x96;	PORTB=1;} 5 nu pot afisa 
			
			convertDone=0;
			ADCSRA |=(1<<ADSC);
			
		}
	}
}

