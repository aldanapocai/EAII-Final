#include <stdint.h>

#define DDD2 2
#define PORTD2 2
#define PIND2 2

#define DDB5 5
#define PORTB5 5
#define PORTB_ADDRESS *((volatile uint8_t*) 0x25)
#define DDRB_ADDRESS *((volatile uint8_t*) 0x24)

#define PORTD_ADDRESS *((volatile uint8_t*) 0x2B) //Port D Data Register - PIR sensor
#define DDRD_ADDRESS *((volatile uint8_t*) 0x2A) //Port D Data Direction Register - PIR sensor
#define PIND_ADDRESS *((volatile uint8_t*) 0x29) //Port D Input Pins Address - PIR sensor

void delay_ms_custom(uint16_t ms) {
  uint16_t i, j;
  for (i = 0; i < ms; i++)
    for (j = 0; j < 3200; j++) //Ajustado 16000/4
      asm volatile("nop"); // Delay for 1ms
}

int main(void) {
  // Set PD2 as input and PB5 as output
  DDRD_ADDRESS = DDRD_ADDRESS & ~(1 << DDD2);  // PD2 as input
  DDRB_ADDRESS = DDRB_ADDRESS | (1 << DDB5);   // PB5 as output

  while (1) {
    // Read the state of PD2
    if (PIND_ADDRESS & (1 << PIND2)) {
      // PD2 is high, set PB5 high
      PORTB_ADDRESS = PORTB_ADDRESS | (1 << PORTB5);
    } else {
      // PD2 is low, set PB5 low
      PORTB_ADDRESS = PORTB_ADDRESS & ~(1 << PORTB5);
    }

    // Custom delay of 500 milliseconds
    delay_ms_custom(500);
  }

  return 0;
}