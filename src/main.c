#include <avr/io.h>

#define F_CPU 16000000UL   //Arduino UNO - Clock Frequency 16MHz


void delay_ms_custom(uint16_t ms) {
    uint16_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 3200; j++) //Ajustado 16000/4
            asm volatile("nop"); // Delay for 1ms
}

int main(void){
  DDRB = DDRB | (1 << DDB5);

  while(1) {
  PORTB = PORTB | (1 << PORTB5);
  delay_ms_custom(1000);
  PORTB = PORTB & ~(1 << PORTB5);
  delay_ms_custom(1000);
}
  return 0;
}