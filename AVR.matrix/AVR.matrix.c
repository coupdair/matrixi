#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>

//SETTING: ArduinoMega pin 22-37 = PA0-7,PC7-0 (different orders)
//16 bit = 2x8bit = PORTA and PORTC
//lowest 8 bit part
#define LED_DDR0   DDRA
#define LED_PORT0 PORTA
//LED map of the port
  //line 2 and 3: swap PA1 and PA2, i.e. 23 and 24 pin order
  //line 5 and 6: swap PA5 and PB6, i.e. 27 and 28 pin order
  //bit PXN                76543210
#define LED_MAP0  \
                         0b00000001, \
                         0b00000100, \
                         0b00000010, \
                         0b00001000, \
                                     \
                         0b00010000, \
                         0b01000000, \
                         0b00100000, \
                         0b10000000
//highest 8 bit part
#define LED_DDR1   DDRC
#define LED_PORT1 PORTC
//LED map of the port
  //all bit order reversed (e.g. PC7 is first bit)
  //line 2 and 3: swap PC1 and PC2, i.e. 36 and 35 pin order
  //line 5 and 6: swap PC5 and PC6, i.e. 32 and 33 pin order
  //bit PXN                76543210
#define LED_MAP1  \
                         0b10000000, \
                         0b00100000, \
                         0b01000000, \
                         0b00010000, \
                                     \
                         0b00001000, \
                         0b00000010, \
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
  //initialise port as LED output
  LED_DDR0=255;//LED.matrix output low
  LED_DDR1=255;//LED.matrix output high
  //change LED as bit matrix
  while(1)
  {
    //split 16 bit number in 2x 8 bit numbers
    low=(unsigned char)value;
    high=(unsigned char)(value>>8);
    //LED mapping
    low= map8(low, map0);
    high=map8(high,map1);
    //LED.matrix set
    LED_PORT0=low;
    LED_PORT1=high;
    //wait
    _delay_ms(250);
    //increment
    ++value;
  }//while (i.e. infinite loop)
  return (0);
}

