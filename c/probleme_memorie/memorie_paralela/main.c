#include <avr/io.h>
char out;
/*
  RST = PORTB2
  CLK = PORTB1
  R/W = PORTB0 -> high
  DATA OUT = PORTD2 - D2
  DATA IN  = PORTD3 - D3
*/

void setup(){ 
  DDRB  = 0b00000111;//0x07
  DDRD  = 0b01000000;//0x04
  PORTB = 4; // Restare Memorie
  Serial.begin();
}

int main(void){
  setup();
  PORTB = 1;//Activare citire
  for(int j=0;j<16;j++){
    for(int i=0;i<8;i++){
      out = PIND;
      out = out>>1;
      PORTB |= 2; //CLK HIGH
      PORTB &= ~2;//CLK LOW
    }
    Serial.println(out);
  }

  while(1);
}
