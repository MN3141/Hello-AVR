#include <avr/io.h>
#define COMMAND() PORTD &= ~(1<<PORTD3); // DC is set to command on 0
#define DATA()    PORTD |= (1<<PORTD3);  // DC is set to data    on 1
#define RESET_LOW() PORTD &= ~(1<<PORTD2);
#define RESET_HIGH() PORTD |= (1<<PORTD2);

void delay(int param){
	param = param*20;//default 1.25us
	for(int i=0;i<param;i++){
		asm volatile("nop");
	}
}

void spi_transfer(uint8_t data){
	PORTB &= ~(1<<PORTB2);		// set ss low
	SPDR = data;				// send data
	asm volatile("nop");		//
	while(!(SPSR & (1<<SPIF))); //wait for transfer to complete
	PORTB |= (1 << PORTB2);		// set ss high
}

void send_command(uint8_t command){
	COMMAND();
	spi_transfer(command);
}

void send_data(uint8_t data){
	DATA();
	spi_transfer(data);
}

void setup(){
	
	SPCR = (1<<MSTR)  | //Enable master mode
		   (1<<SPE)   | //Enable spi
		   (1<<SPR1)  | //
		   (1<<SPR0)  | //Set clk to 16MHz/128=125kHZ
		   (1<<SPIE);	//Enable interrupts to know when a transfer is completed

	DDRB = (1<<PORTB3) | //MOSI pin
		   (1<<PORTB2) | //SS   pin
	       (1<<PORTB5);  //CLK  pin
	DDRD = (1<<PORTD2) | //RST -LCD
	       (1<<PORTD3);  //DC  -LCD
	PORTD = 0;
	
	RESET_LOW(); //reset the display
	delay(1);//1.25uS
	RESET_HIGH();//pull reset high
	delay(1);
	
	send_command(0x01);//software reset
	delay(1);
	send_command(0x11);//exit sleep mode
	delay(120);//150uS, minimum is 120uS
	
	send_command(0x39);//idle mode on for 8 color mode
	delay(1);
	
}	
int main(void)
{
	setup();
	
    while(1);
}

