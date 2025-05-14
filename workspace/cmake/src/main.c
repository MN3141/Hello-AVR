#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRB = 0xFF; // Set PORTB as output
    PORTB = 0x00; // Initialize PORTB to 0
    while (1) {
        PORTB ^= 0xFF;
        _delay_ms(1000);
    }
    return 0;
}
