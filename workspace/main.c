#include <avr/io.h>

int main(){
  DDRD = (1<<2);
  while(1){
    PORTD ^= (1<<2);
  }
}
