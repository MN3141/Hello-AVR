#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define interrupts() SREG |= (1<<7)
#define CALIBRATION .69
volatile uint32_t i;
uint32_t data;
volatile char astept =1;
volatile int contor;
char out[16];

//D8 - TRIG
//D9 - ECHO
void print(char* msg){
  for(i=0;msg[i]!='\0';i++){
    while(!(UCSR0A & 32));
    UDR0 = msg[i];
  }
}

ISR(TIMER1_COMPA_vect)
{
  TCNT1 = 0;
  i++; // număra calupuri de 1 microsecunde
  if ((PINB & 0x02) == 0)
  {
    TIMSK1 = TIMSK1 & ~0x02; //oprim timerul
    astept = 1;
  }
}

/**
 * @name Send Impulse
 * @brief Set TRIG pin to high for 10ms and then to low to send a signal 
 * @param None
*/
void send_impulse(void){
  PORTB &= ~1;
  _delay_ms(2);
  PORTB |= 1;
  _delay_ms(10);
  PORTB &= ~1;
}

uint32_t read_echo(void){
  OCR1A = 2;
  i = 0;
  astept = 0;
  while((PINB & 2) == 0);
  TIMSK1 = 2;
  while(!astept);
  i = i*CALIBRATION;
  return i;
}

/**
 * @brief sends impulse and then it reads the ECHO pin for the distance
 * @return i
*/
unsigned long read_sensor(void){
  send_impulse();
  return read_echo();
}

void setup(){
  DDRB = 0b01; 
  UCSR0B = 0b11000;
  UCSR0C = 0b00000110;
  UBRR0 = 103;
  TCCR1A = 0x00; //0000 0000 - Normal, CTC
  TCCR1B = 0x0A; //0000 1010 - CTC,8 prescale
  print("Starting\n");
  interrupts();
}

int main(void){
  setup();
  while(1){
    _delay_ms(1000);
    data = read_sensor();
    print("Sensor: ");
    ultoa(data,out,10);
    print(out);
    print(" mm\n");
  }
}
