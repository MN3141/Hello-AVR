#include <avr/io.h>
#include <avr/interrupt.h>
// #define SLAVE
#define MASTER

#ifdef SLAVE
ISR(SPI_STC_vect){
	UDR0 = SPDR;
}
#endif

#ifdef MASTER
volatile int flag=0;
ISR(TIMER1_COMPA_vect){
	flag =1;
	TCNT1=0;
	TIFR1 =2;
}
#endif

#ifdef MASTER
void setup_master(){
	SPCR =   (1<<SPIE)|(1<<SPE)|   (1<<MSTR)|      (1<<SPR0)|(1<<SPR1);
	PRR &= ~(1<<PRSPI);
	TCCR1A = 0;
	TCCR1B = 0b00001101;
	TCCR1C = 0;
	OCR1A = 15625;
	TIMSK1 = 2;
	TIFR1 = 2;
	
	DDRB = 0b00101100; // Set MOSI, SCK, and SS as outputs
	
	UCSR0A = 0;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00101110;
	UBRR0 = 103;
	
	sei();
}
#endif
#ifdef SLAVE
void setup_slave(){

	SPCR =  (1<<SPIE)|   (1<<SPE)|   (0<<MSTR);
	PRR &= ~(1<<PRSPI);

	DDRB = 0b00001000; // Set MISO as output, others as input
	
	UCSR0A = 0;
	UCSR0B = 0b00011000;
	UCSR0C = 0b00101110;
	UBRR0 = 103;
	sei();
}
#endif
int main(void)
{
	#ifdef MASTER
	setup_master();
	#endif
	#ifdef SLAVE
	setup_slave();
	#endif
	#ifdef MASTER
	while (1){
		if(flag){
			UDR0 ='1';
			PORTB &= ~(1<<PORTB2); // Drive SS low
			SPDR = 0x31;
			PORTB |= (1 << PORTB2); //set SS
			flag = 0;
		}
	}
	#endif
	#ifdef SLAVE
	while(1);
	#endif
}