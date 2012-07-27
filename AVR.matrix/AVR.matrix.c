#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/pgmspace.h>

//TTL SETTING: ArduinoMega pin 46,48 = PL3,1
//PL1=SYNC, PL3=IN
#define TTLs_DDR   DDRL
#define TTLs_PORT PORTL
#define TTLs_PIN   PINL
#define TTL0         PL3
#define TTL1         PL1

//EXPOSURE LED SETTING: ArduinoMega pin 47 = PL2
//use PIN to toggle exposure
#define EXPO         PL2

#ifndef DELAY_TIME
#define DELAY_TIME 200
#endif
#ifndef EXPOSURE_TIME
#define EXPOSURE_TIME 50
#endif

//LED SETTING: ArduinoMega pin 22-37 = PA0-7,PC7-0 (different orders)
//16 bit = 2x8bit = PORTA and PORTC
//lowest 8 bit part
#define LED_DDR0   DDRA
#define LED_PORT0 PORTA
//LED map of the port (LED.matrix.v0.1.0 and v0.2.3)
  //line 2 and 3: swap PA1 and PA2, i.e. 23 and 24 pin order
  //line 5 and 6: swap PA5 and PB6, i.e. 27 and 28 pin order
  //bit PXN                76543210
#define LED_MAP0  \
                         0b00000100, \
                         0b00000001, \
                         0b00000010, \
                         0b00001000, \
                                     \
                         0b01000000, \
                         0b00010000, \
                         0b00100000, \
                         0b10000000
//highest 8 bit part
#define LED_DDR1   DDRC
#define LED_PORT1 PORTC
//LED map of the port (LED.matrix.v0.2.3)
  //all bit order reversed (e.g. PC7 is first bit)
  //line 2 and 3: swap PC1 and PC2, i.e. 36 and 35 pin order
  //line 5 and 6: swap PC5 and PC6, i.e. 32 and 33 pin order
  //bit PXN                76543210
#define LED_MAP1  \
                         0b10000000, \
                         0b00100000, \
                         0b00010000, \
                         0b01000000, \
                                     \
                         0b00000010, \
                         0b00001000, \
                         0b00000100, \
                         0b00000001

//ArduinoMega pin 22-37 = PA0-7,PC7-0 (different orders)
//or
//ArduinoMega pin 37-30,49-42 = PC7-0,PL7-0 (same order)


//! map a value regarding to mapping matrix
/**
 * convert binary value to LED mapped binary value regarding to mapping matrix
 * intendeed to change bits that have different order than LED positions
 * e.g. 0b0000 0010 mapped to 0b0000 0100 on Arduino port B:
 *      PB2 is mapped to be bit 1 -not bit 2 if no mapping used i.e. same 0b0000 0010 as mask-
 *
 * \param in: value to map
 * \param map: mapping matrix, i.e. 8 bit mask for setting the position of the LED
 * \return mapped value
**/
unsigned char map8(unsigned char in, unsigned char *map/*[8]*/)
{
  //bit mask
  unsigned char mask;
  //mapped value
  unsigned char out=0;
  //for loop index
  unsigned char i;
  //8 bit mapping loop
  for(i=0;i<8;++i)
  {
    mask=_BV(i);
    if((in&mask)==mask)
    {//set bit true
      out|=map[i];
    }
    else
    {//set bit false
      out&=~map[i];
    }
  }
  return out;
}//map8
//! 
/**
 * 
 * 
 * 
 * 
**/
void setLEDmatrix8(unsigned char low,unsigned char high,unsigned char *map0/*[8]*/,unsigned char *map1/*[8]*/)
{
  //LED mapping
  low= map8(low, map0);
  high=map8(high,map1);
  //LED.matrix set
  LED_PORT0=low;
  LED_PORT1=high;
}//setLEDmatrix8
//! 
/**
 * 
 * 
 * 
 * 
**/
void setLEDmatrix16(int value,unsigned char *map0/*[8]*/,unsigned char *map1/*[8]*/)
{
  //split 16 bit number in 2x 8 bit numbers
  unsigned char low=(unsigned char)value;
  unsigned char high=(unsigned char)(value>>8);
  //LED.matrix set with mapping
  setLEDmatrix8(low,high,map0,map1);
}//setLEDmatrix16
//! 
/**
 * 
 * 
 * 
 * 
**/
void testAllLED(int repeat,int delay,unsigned char *map0/*[8]*/,unsigned char *map1/*[8]*/)
{
  int i;
  int value=1;
  //loop       v times (e.g. for 2 times: 16*2)
  for(i=0;i<16*repeat;++i)
  {
    //LED ON
    setLEDmatrix16(value,map0,map1);
    //wait a while
    _delay_ms(delay);
    //increment
    value=value<<1;
    if(value==0) value=1;
  }//for loop test
}//testAllLED
//! 
/**
 * 
 * 
 * 
 * 
**/
void calibrationLEDmatrix(unsigned char *map0/*[8]*/,unsigned char *map1/*[8]*/)
{
  const int value=0b1111111111111101;
  //LED ON
  setLEDmatrix16(value,map0,map1);
}
//! 
/**
 * 
 * 
 * 
 * 
**/
int main(void)
{
//declaration
  //value is 16 bit, i.e. low and high part on 2 different ports
  //initialise value at 0
  int value=0;
  //low part of value
  unsigned char low;
  //low part map (8 bit mapping)
  unsigned char map0[8]={LED_MAP0};//LED_MAP0 is a #define
  //high part of value
  unsigned char high;
  //high part map (8 bit mapping)
  unsigned char map1[8]={LED_MAP1};//LED_MAP1 is a #define
//initialisation
  //initialise port as LED output
  LED_DDR0=255;//LED.matrix output low
  LED_DDR1=255;//LED.matrix output high
  //initialise port as TTL in/output
#ifdef EXTERNAL_TRIGGER
//single exposure
  TTLs_DDR|=_BV(TTL0);//synchronisation TTL output
  TTLs_DDR&=~_BV(TTL1);//synchronisation TTL input
//double exposure
//! \todo [next] double exposure mode (internal/external: TTL[i] with i=(++i<2)?i:0; )
//  TTLs_DDR&=~_BV(TTL0);//synchronisation TTL input for exposure 1
  //TTLs_DDR&=~_BV(TTL1);//synchronisation TTL input for exposure 2
#else
  TTLs_DDR|=_BV(TTL0);//synchronisation TTL output for exposure 1
  TTLs_DDR|=_BV(TTL1);//synchronisation TTL output for exposure 2
#endif
  //initialise port as exposure LED output
  TTLs_DDR|=_BV(EXPO);//exposure LED: ON for exposure 1, OFF for exposure 2

//test all LEDs
  //ON
  setLEDmatrix8(255,255,map0,map1);
  //wait a while
  _delay_ms(1000);
  //OFF
  setLEDmatrix8(0,0,map0,map1);
  //wait a while
  _delay_ms(500);

//test LED mapping
//  testAllLED(2,300,map0,map1);

//calibration LED.matrix
  calibrationLEDmatrix(map0,map1);
  //wait a while
  _delay_ms(1500);

//increment LED.matrix
  //set exposure LED ON
  TTLs_PORT|=_BV(EXPO);
  value=0;
  while(1)
  {
    //split 16 bit number in 2x 8 bit numbers
    low=(unsigned char)value;
    high=(unsigned char)(value>>8);
    //LED mapping
    low= map8(low, map0);
    high=map8(high,map1);
    //wait for external trigger up
#ifdef EXTERNAL_TRIGGER
//! todo [actual] . wait for external trigger UP, i.e. test digital input pin (using loop_until_bit_is_set(PIN, bit); )
    loop_until_bit_is_set(TTLs_PIN,TTL1);
#else
    _delay_ms(DELAY_TIME);
#endif
    //set SYNC TTL to up
    TTLs_PORT|=_BV(TTL0);
#ifndef EXTERNAL_TRIGGER
    //set IN TTL to up
    TTLs_PORT|=_BV(TTL1);
#endif
    //LED.matrix set ON
    LED_PORT0=low;
    LED_PORT1=high;
    //wait for external trigger down
#ifdef EXTERNAL_EXPOSURE
//! todo [actual] . wait for external trigger DOWN, i.e. test digital input pin (using loop_until_bit_is_clear(PIN, bit); )
    loop_until_bit_is_clear(TTLs_PIN,TTL1);
#else
    _delay_ms(EXPOSURE_TIME);
#endif
    //SYNC TTL to down
    TTLs_PORT&=~_BV(TTL0);
#ifndef EXTERNAL_TRIGGER
    //IN TTL to down
    TTLs_PORT&=~_BV(TTL1);
#endif
    //LED.matrix set OFF
    LED_PORT0=0;
    LED_PORT1=0;
    //increment
    ++value;
    //toggle exposure LED (OFF/ON)
    TTLs_PIN|=_BV(EXPO);
  }//while (i.e. infinite loop)
  return (0);
}

