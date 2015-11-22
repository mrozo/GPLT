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


VOID InitSerial (
  volatile USART_t                    *Usart,
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
  Usart->CTRLA = 0;
  Usart->BAUDCTRLB = BYTE1(BaudRateRegisterValues[ClockFrequency][Speed]);
  Usart->BAUDCTRLA = BYTE0(BaudRateRegisterValues[ClockFrequency][Speed]);
  Usart->CTRLC = USART_CHSIZE_8BIT_gc | USART_CMODE_ASYNCHRONOUS_gc;
  Usart->CTRLB = USART_TXEN_bm | USART_RXEN_bm;

}

VOID inline SendChar(
  volatile USART_t                    *Usart,
  BYTE                                 Character
)
{
  _delay_us(100);
  while( !(Usart->STATUS & USART_DREIF_bm) );
  Usart->DATA = Character;
}


VOID SendString(
  volatile USART_t                    *Usart,
  CHAR8                               *StringBuffer
)
{
  while (*StringBuffer != '\0') {
    SendChar(Usart,*StringBuffer);
    StringBuffer++;
  }
}

CHAR8 ReadChar (
  volatile USART_t                    *Usart
){
  return Usart->DATA;
}

VOID WaitForChar (
  volatile USART_t                    *Usart
){

  while (!IsRxDataReady(Usart)){}
}

BOOLEAN IsRxDataReady (
  volatile USART_t                    *Usart
){
  return (Usart->STATUS & USART_RXCIF_bm)? TRUE: FALSE;
}

RETURN_STATUS ReadLine (
  volatile USART_t                    *Usart,
  CHAR8                               *LineBuffer,
  UINT16                               BufferSize
){
  UINT16                               CharsRead = 0;
  CHAR8                               *LineBufferPosition = LineBuffer;
  RETURN_STATUS                        Status;

  SendDebugCode(1);

  while (TRUE) {
    SendDebugCode(2);
    WaitForChar(Usart);
    *LineBufferPosition = ReadChar(Usart);

    if(*LineBufferPosition == CR_CHAR){
      *LineBufferPosition = NULL_CHAR;
      Status = SUCCESS;
      break;
    }

    LineBufferPosition++;
    CharsRead++;

# TODO: poprawic
    if (CharsRead >= (BufferSize-1)){
      SendDebugCode(3);
      Status = BUFFER_TOO_SMALL;
      *LineBufferPosition = NULL_CHAR;
      break;
    }
  }

  SendDebugCode(4);
  if (Status == SUCCESS) {
    *LineBufferPosition = NULL_CHAR;
    SendDebugCode(5);
  }

  return Status;
}
