/*
 * Serial.c
 *
 *  Created on: Nov 10, 2015
 *      Author: m
 */

#include <avr/io.h>
#include "Serial.h"
#include <util/delay.h>

UINT16 BaudRateRegisterValues[3][3] = {
    { 0x000C, 0x0002, 0xFFFF }, // F_CPU=2MHZ
    { 0x0033, 0x000C, 0x0003 }, // F_CPU=8HZ
    { 0x00CF, 0x0033, 0x0010 }  // F_CPU=32MHZ
};


void InitSerial (
  USART_t                             *USART,
  BAUD_RATE                            Speed,
  CLOCK_FREQUENCY                      ClockFrequency
)
{

  //
  // Disable interrupts
  // Set baud rate
  // Set word size, parity and stop bits settings.
  // Enable RX/TX
  // enable high speed mode
  //
  USART->CTRLA = 0;
  USART->BAUDCTRLB = BYTE1(BaudRateRegisterValues[ClockFrequency][Speed]);
  USART->BAUDCTRLA = BYTE0(BaudRateRegisterValues[ClockFrequency][Speed]);
  USART->CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_ASYNCHRONOUS_gc;
  USART->CTRLB = USART_TXEN_bm | USART_RXEN_bm;

}

void inline sendChar(
  USART_t                             *USART,
  BYTE                                 word
)
{
  while( !(USART->STATUS & USART_DREIF_bm) );
  _delay_ms(1);
  USART->DATA = word;
}


void sendString(
  USART_t                             *USART,
  CHAR8 *str
)
{
  while(*str)
  {
    sendChar(USART,*str++);
  }
}
