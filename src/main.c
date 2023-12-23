//#include <avr/io.h>
#include <stdint.h>
#define DDB5 5
#define PORTB5 5
volatile uint8_t* PORTB_ADDRESS = (volatile uint8_t*) 0x25;
volatile uint8_t* DDRB_ADDRESS = (volatile uint8_t*) 0x24;

//#define F_CPU 16000000UL   //Arduino UNO - Clock Frequency 16MHz


void delay_ms_custom(uint16_t ms) {
    uint16_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 3200; j++) //Ajustado 16000/4
            asm volatile("nop"); // Delay for 1ms
}

int main(void){
  //DDRB = DDRB | (1 << DDB5);
  *DDRB_ADDRESS = *DDRB_ADDRESS | (1 << DDB5);

  while(1) {
  *PORTB_ADDRESS = *PORTB_ADDRESS | (1 << PORTB5);  
  //PORTB = PORTB | (1 << PORTB5);
  delay_ms_custom(1000);
  *PORTB_ADDRESS = *PORTB_ADDRESS & ~(1 << PORTB5);
  //PORTB = PORTB & ~(1 << PORTB5);
  delay_ms_custom(1000);
}
  return 0;
}