/*S? se realizeze o aplica?ie care transmite pe portul serial caracterul
recep?ionat (a?a cum a venit) dac? SW1 nu este ap?sat ?i îl converte?te din liter?
mare în liter? mic? (dac? este cazul) în cazul în care SW1 este ap?sat*/
#include <avr/io.h>
unsigned char data=0;
void setup()
{
	DDRC=0x00;
	//UCSR0A=0x00;
	UCSR0B=0x08;//enable transmission
	UCSR0C=0x06;//8 bits of data
	UBRR0L=0x67;//103
	UBRR0H=0x00;
	//UBRR0=(fOscilator/baudRate)-1
	
}
int main(void)
{
    while (1) 
    {
		while((UCSR0A&0x80)==0);
		data=UDR0;
		while((UCSR0A&0x20)==0);
		if(
		((PINC & 0x02)==0) &&
		((UDR0 &(1<<5))!=0)
		
		)
			UDR0=data^(1<<5);
		else
			UDR0=data;
		
    }
}

