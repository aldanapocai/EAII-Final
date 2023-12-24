#include <stdint.h>

#define PORTD_ADDRESS *((volatile uint8_t*) 0x2B) //Port D Data Register
#define DDRD_ADDRESS *((volatile uint8_t*) 0x2A) //Port D Data Direction Register
#define PIND_ADDRESS *((volatile uint8_t*) 0x29) //Port D Input Pins AddresS
#define PORTD2 2 //Arduino D2
#define DDD2 2
#define PIND2 2

#define PORTB_ADDRESS *((volatile uint8_t*) 0x25) //Port B Data Register
#define DDRB_ADDRESS *((volatile uint8_t*) 0x24) //Port B Data Direction Register
#define PORTB5 5 //Arduino LED
#define DDB5 5
#define PORTB1 1 //Arduino D9
#define DDB1 1


void delay_ms_custom(uint16_t ms) {
  uint16_t i, j;
  for (i = 0; i < ms; i++)
    for (j = 0; j < 3200; j++) //Ajustado 16000/4
      asm volatile("nop"); // Delay for 1ms
}

int main(void) {
  // Set PD2 as input and PB5, PB1 as output
  DDRD_ADDRESS = DDRD_ADDRESS & ~(1 << DDD2);  // PD2 as input
  DDRB_ADDRESS = DDRB_ADDRESS | (1 << DDB5);   // PB5 as output
  DDRB_ADDRESS = DDRB_ADDRESS | (1 << DDB1);   // PB1 as output

  while (1) {
    // Read the state of PD2
    if (PIND_ADDRESS & (1 << PIND2)) {
      PORTB_ADDRESS = PORTB_ADDRESS | (1 << PORTB5); //LED HIGH
      //set PD7 motor to 180° using pulse width modulation
      for (int Hz = 0; Hz < 50; Hz++) {
        uint16_t pausa = (180*2000.0/200.0) + 500;
        PORTB_ADDRESS = PORTB_ADDRESS | (1 << PORTB1); //PB1 HIGH
        delay_ms_custom(pausa/1000); //Delay 2300 microseconds
        PORTB_ADDRESS = PORTB_ADDRESS & ~(1 << PORTB1); //PB1 LOW
        delay_ms_custom((2300 - pausa)/1000);
      }
      delay_ms_custom(15000); //wait 15 seconds
    } else {
      // PD2 is low, set PB5 low
      PORTB_ADDRESS = PORTB_ADDRESS & ~(1 << PORTB5);
    }

    // Custom delay of 500 milliseconds
    delay_ms_custom(500);
  }

  return 0;
}