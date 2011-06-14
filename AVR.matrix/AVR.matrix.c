#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

//16 bit = 2x8bit = PORTL and PORTC (test PORTB)
#define LED_DDR0   DDRL
#define LED_PORT0 PORTL
#define LED_DDR1   DDRC
#define LED_PORT1 PORTC
//ArduinoMega pin 22-37 = PA0-7,PC7-0 (different orders)
//or
//ArduinoMega pin 37-30,49-42 = PC7-0,PL7-0 (same order)

int main(void)
{
  //value is 16 bit, i.e. low and high part on 2 different ports
  //initialise value at 0
  int value=0;
  unsigned char low;
  unsigned char high;
  //initialise port as LED output
  LED_DDR0=255;//LED.matrix output low
  LED_DDR1=255;//LED.matrix output high
  //change LED as bit matrix
  while(1)
  {
    low=(unsigned char)value;//! \todo test
    high=(unsigned char)(value>>8);//! \todo test
    LED_PORT0=low;//LED.matrix set
    LED_PORT1=high;//LED.matrix set
    _delay_ms(500);//wait
    ++value;//increment
  }//while (i.e. infinite loop)
  return (0);
}

