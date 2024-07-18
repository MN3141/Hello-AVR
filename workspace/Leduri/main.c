#include <avr/io.h>
char out;
/*
*
**
***
****
***
**
*

*/
char data = 1;
void setup(){ 
  DDRB = 0b1111;
}
int main(void){
  setup();
  PORTB = data;
  while(1){
    for(int i=0;i<4;i++){
      data <<= 1;
      data += 1;
      PORTB = data;
    }
    for(int i=0;i<4;i++){
      data >>= 1;
      PORTB = data;
    }
  }
}
