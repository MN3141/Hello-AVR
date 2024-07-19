#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>
#define interrupts() SREG |= (1<<7)
uint16_t address = 0x8D54;
char out[16];


void setup(){ 

}

int main(void){
  setup();
  while(1);
}
