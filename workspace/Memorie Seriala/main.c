#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define interrupts() SREG |= (1<<7)
uint16_t address = 0x8D54;
char out[16];

//1000_1101_0101_0100
//10AA_AAAA_AAAA_AAAA
//adresa:3412 - NR MATRICOL
//SALDORFEAN ANDREI

void send_byte(unsigned char byte){
  while(!(UCSR0A&5));
  UDR0 = byte;
}

void send_command(unsigned int command){
  send_byte(command>>8);
  send_byte(command);  
}

void send_message(char *message){
  for(;*message != "\0";){
    send_command(address);
    send_byte(*message);
    message++;
    address++;
  }
}

void setup(){
  UCSR0B = 0b11000; //activare port serial
  UCSR0C = 0b00111110;//configurare comunicare (8 biti de date, paritate impara, 2 biti de stop)
  UBRR0  = 415; //2400 biti pe secunda
}

int main(void){
  setup();
  send_command(0x000f);//Activare scriere
  send_message(address,"SALDORFEAN ANDREI");
  while(1);
}
