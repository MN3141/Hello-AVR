#include <avr/io.h>
void setup()
{
	//UCSR0A=0x00;
	UCSR0B=0x08;//enable transmission
	UCSR0C=0x06;//8 bits of data
	UBRR0L=0x67;//103
	UBRR0H=0x00;
	//UBRR0=(fOscilator/baudRate)-1
}
int main(void)
{
	//transmiting characters from A to Z
	setup();
	unsigned char symbol='A';
	while (1)
	{
		
		//if(UDR0>0x5A)
		//	UDR0=0x40;
		while((UCSR0A & (1<<5) )==0);//waiting until it is ready to transmit data
		//or UCSR0A&(1<<UDRE0)
		UDR0=symbol;
		if(symbol>'Z')
			symbol='A';
		else 
			symbol++;
	}
}

