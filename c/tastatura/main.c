#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
/*
  RST = PORTB2
  CLK = PORTB1
  R/W = PORTB0 -> high
  DATA OUT = PORTD2 - D2
  DATA IN  = PORTD3 - D3
*/
int i;
int j;
uint32_t pin;
char out[16];
int matrix[4][4] = 
{
  {1,2,3,4},
  {5,6,7,8},
  {9,10,11,12},
  {13,14,15,16}
};

void cPrint(char* msg){
  for(j=0;msg[j]!='\0';j++){
    while(!(UCSR0A & 32));
    UDR0 = msg[j];
  }
} 

void iPrint(int num){
  itoa(num,out,10);
  cPrint(out);
} 

void setup(){ 
  UCSR0B = 0b11000;
  UCSR0C = 0b00000110;
  UBRR0  = 103;
  DDRB   = 0b1111; //Coloane
  DDRD   = 0;      //Linii
  PORTD = 0xFF; // Enable pull-up resistors on PD2-PD5
  cPrint("hello\n");
}

int main(void){
  setup();
  while(1){
    for(i=0;i<4;i++){
      PORTB = ~(1<<i);
      _delay_ms(10);
      if (!(PIND & (1 << PD2))) { // Check if a button in row 1 is pressed
        iPrint(matrix[0][i]);
      }
      if (!(PIND & (1 << PD3))) { // Check if a button in row 2 is pressed
        iPrint(matrix[1][i]); 
      }
      if (!(PIND & (1 << PD4))) { // Check if a button in row 3 is pressed
        iPrint(matrix[2][i]);
      }
      if (!(PIND & (1 << PD5))) { // Check if a button in row 4 is pressed
        iPrint(matrix[3][i]);
      }
    }

  }
}
