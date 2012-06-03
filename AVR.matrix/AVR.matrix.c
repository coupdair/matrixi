#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

//ArduinoMega pin 53-50,10-13 = PB0-7
#define LED_DDR   DDRB
#define LED_PORT PORTB
#define LED_PIN   PINB

//16 bit = 2x8bit = PORTA and PORTC

#define AP_13  PORTB7
#define AP_12  PORTB6
#define AP_11  PORTB5
#define AP_10  PORTB4
#define AP_50  PORTB3
#define AP_51  PORTB2
#define AP_52  PORTB1
#define AP_53  PORTB0

//ArduinoMega pin 41-49 = PL0-7 (PL1=48=SYNC, PL2=47=LED, PL3=46=IN)
#define TTL_DDR   DDRL
#define TTL_PORT PORTL
#define TTL_PIN   PINL

#define AP_46  PORTL3
#define AP_47  PORTL2
#define AP_48  PORTL1

int main(void)
{
  LED_DDR=255;//LED.matrix output
//  LED_DDR&=~_BV(AP_10);
  TTL_DDR=255;//LED.matrix output
  TTL_DDR&=~_BV(AP_46);
  char i,skip_nb=5;
  while(1)
  {
//    LED_PORT=0xb11111111;
//    LED_PORT=255;
    LED_PORT|=_BV(AP_13);
///    LED_PORT|=_BV(AP_10);
    //wait for first TTL
//    loop_until_bit_is_set(LED_PIN,AP_10); //wait for PIV synchronization up
    loop_until_bit_is_set(TTL_PIN,AP_46); //wait for PIV synchronization up
    LED_PORT&=~_BV(AP_13);
//    LED_PORT|=_BV(AP_12);
    TTL_PORT|=_BV(AP_47);
    //skip \c skip_nb TTL
//    loop_until_bit_is_clear(LED_PIN,AP_10); //wait for PIV synchronization down
    loop_until_bit_is_clear(TTL_PIN,AP_46); //wait for PIV synchronization down
    for(i=0;i<skip_nb;++i)
    {
      //toggle exposure LED (OFF/ON)
//      LED_PIN|=_BV(AP_12);
      TTL_PIN|=_BV(AP_47);
      //wait for next TTL
//      loop_until_bit_is_set(LED_PIN,AP_10); //wait for PIV synchronization up
//      loop_until_bit_is_clear(LED_PIN,AP_10); //wait for PIV synchronization down
      loop_until_bit_is_set(TTL_PIN,AP_46); //wait for PIV synchronization up
      loop_until_bit_is_clear(TTL_PIN,AP_46); //wait for PIV synchronization down
    }//skip loop
//    LED_PORT&=~_BV(AP_12);
    TTL_PORT&=~_BV(AP_47);
//    LED_PORT=0xb00000000;
//    LED_PORT=0;
///    LED_PORT&=~_BV(AP_10);
//    _delay_ms(1000);
  }
  return (0);
}

