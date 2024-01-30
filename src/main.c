#include <stdint.h>

#define PORTD_ADDRESS *((volatile uint8_t*) 0x2B) //Port D Data Register
#define DDRD_ADDRESS *((volatile uint8_t*) 0x2A) //Port D Data Direction Register
#define PIND_ADDRESS *((volatile uint8_t*) 0x29) //Port D Input Pins Address
#define PORTD2 2 //Arduino D2
#define DDD2 2
#define PIND2 2

#define PORTB_ADDRESS *((volatile uint8_t*) 0x25) //Port B Data Register
#define DDRB_ADDRESS *((volatile uint8_t*) 0x24) //Port B Data Direction Register
#define PORTB5 5 //Arduino LED
#define DDB5 5
#define PORTB1 1 //Arduino D9
#define DDB1 1

void delay_us_custom(long us) {
  uint16_t i, j;
  for (i = 0; i < us; i++) {
    for (j = 0; j < 4; j++) { //Ajustado 8000/4/1000
      asm volatile("nop"); // Delay for 1us
    }
  }
}
void delay_ms_custom(long ms) {
  uint16_t i, j;
  for (i = 0; i < ms; i++) {
    for (j = 0; j < 2000; j++) { //Ajustado 16000/8-> 2MHz
      asm volatile("nop"); // Delay for 1ms
    }
  }
}

void setServoAngle(uint8_t angle) {
  // Calculate pulse width based on the desired angle (adjust these values)
  uint16_t pulseWidth = 600 + (angle * 10);
  for (int Hz = 0; Hz < 50; Hz++) {
    // Send the PWM signal
    PORTB_ADDRESS = PORTB_ADDRESS | (1 << PORTB1); // PB1 HIGH
    delay_us_custom(pulseWidth); // Convert pulse width to seconds
    PORTB_ADDRESS = PORTB_ADDRESS & ~(1 << PORTB1); //PB1 LOW
    delay_us_custom(20000 - pulseWidth); // Remaining time in the period
  }
}

int main(void) {
  // Set PD2 as input and PB5, PB1 as output
  DDRD_ADDRESS = DDRD_ADDRESS & ~(1 << DDD2);  // PD2 as input
  DDRB_ADDRESS = DDRB_ADDRESS | (1 << DDB5);   // PB5 as output
  DDRB_ADDRESS = DDRB_ADDRESS | (1 << DDB1);   // PB1 as output

  while (1) {
    if (PIND_ADDRESS & (1 << PIND2)) {
      // PD2 is high, set PB5 low
      PORTB_ADDRESS = PORTB_ADDRESS & ~(1 << PORTB5);
      
      // Rotate to 180°
      setServoAngle(180);
      delay_ms_custom(10000); //wait 10s

      // Rotate to 0°
      setServoAngle(0);
      delay_us_custom(5000);      
    } else {
      // PD2 is low, set PB5 high
      PORTB_ADDRESS = PORTB_ADDRESS | (1 << PORTB5);
    }
  }
}