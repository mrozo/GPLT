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

VOID SendChar(
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
  CONST CHAR8                         *StringBuffer
)
{
  while ((*StringBuffer) != NULL_CHAR) {
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

RETURN_STATUS ReadBuffer (
  volatile USART_t                    *Usart,
  CHAR8                               *Buffer,
  UINT16                               BufferSize
)
{
  RETURN_STATUS                        Status = SUCCESS;
  UINT16                               CharsRead = 0;
  CHAR8                               *BufferPosition = Buffer;
//TODO dodac delay
  while (CharsRead<=BufferSize) {
    WaitForChar(Usart);
    *BufferPosition = ReadChar(Usart);
    BufferPosition++;
  }

  return Status;
}

RETURN_STATUS ReadLine (
  volatile USART_t                    *Usart,
  CHAR8                               *LineBuffer,
  UINT16                               BufferSize
){
  UINT16                               CharsRead = 0;
  CHAR8                               *LineBufferPosition = LineBuffer;
  RETURN_STATUS                        Status;

  while (TRUE) {
    WaitForChar(Usart);
    *LineBufferPosition = ReadChar(Usart);

    if(*LineBufferPosition == CR_CHAR){
      *LineBufferPosition = NULL_CHAR;
      Status = SUCCESS;
      break;
    }

    LineBufferPosition++;
    CharsRead++;

    if (CharsRead >= (BufferSize-1)){
      Status = BUFFER_TOO_SMALL;
      *LineBufferPosition = NULL_CHAR;
      break;
    }
  }

  if (Status == SUCCESS) {
    *LineBufferPosition = NULL_CHAR;
  }

  return Status;
}
