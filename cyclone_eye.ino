#include <avr/io.h>
#include <util/delay.h>

#define NUM_LEDS 6
#define LED_PORT PORTD           
#define LED_DDR DDRD
#define BUTTON_PIN PINB
#define BUTTON_BIT PB5


#define LED_START_POS 2

void setup() {
    LED_DDR |= 0xF8;  // 1111 1000 to set PD3-PD7 as output
    DDRB &= ~(1 << BUTTON_BIT);
    PORTB |= (1 << BUTTON_BIT);
}

void sweepingEye() {
    for (uint8_t i = 0; i < NUM_LEDS; ++i) {
        if (!buttonPressed()) {
            LED_PORT = (1 << (i + LED_START_POS));
            _delay_ms(100);
        }
    }
    for (int8_t i = NUM_LEDS - 2; i > 0; --i) {
        if (!buttonPressed()) {
            LED_PORT = (1 << (i + LED_START_POS));
            _delay_ms(100);
        }
    }
}

int buttonPressed() {
    return !(BUTTON_PIN & (1 << BUTTON_BIT));
}

void cycloneDeathStare() {
    while (1) {
        sweepingEye();
    }
}

int main() {
    setup();
    cycloneDeathStare();
    return 0;
}
