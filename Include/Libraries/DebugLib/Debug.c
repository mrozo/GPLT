/*
 * Debug.c
 *
 * Created: 9/1/2015 5:38:38 PM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <stdio.h>
#include "DebugLib.h"
#include <Libraries/Portx/Portx.h>
#include <Libraries/Serial/Serial.h>

#define DEBUG_USART                    USARTC0

void InitDebugLib(
  VOID
)
{
  InitPortx();
  PORTC.OUTSET = PIN3_bm;
  PORTC.DIRSET = PIN3_bm;
  PORTC.OUTCLR = PIN2_bm;
  PORTC.DIRCLR = PIN2_bm;
  InitSerial(&DEBUG_USART, b115200, Ridiculous);
}

void SendDebugString(
  CONST CHAR8                         *String
)
{
  SendString(&DEBUG_USART, String);
}


void SendDebugCode(
  UINT8                                Code
)
{
  CHAR8 DebugString[] = "Debug code 0xxx\r\n";
  sprintf(DebugString+13, "%0X\r\n", Code);
  PORTX.OUT = Code;
  SendDebugString(DebugString);
}
