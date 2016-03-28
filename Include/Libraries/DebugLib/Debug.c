/*
 * Debug.c
 *
 * Created: 9/1/2015 5:38:38 PM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <Hardware/Portx/Portx.h>
#include <stdio.h>
#include "DebugLib.h"
#include <Libraries/Serial/Serial.h>

USART_t                               *mUsart;
PORT_t                                *mPort;

void InitDebugLib(
  USART_t                             *Usart,
  PORT_t                              *Port
)
{
  mUsart = Usart;
  mPort = Port;
  InitSerial(mUsart, b115200, Ridiculous);
}

void SendDebugString(
  CONST CHAR8                         *String
)
{
  SendString(mUsart, String);
}

void SendDebugLine(
    CONST CHAR8                         *String
)
{
  SendString(mUsart, String);
  SendString(mUsart, "\r\n");
}


void SendDebugCode(
  UINT8                                Code
)
{
  return;
  CHAR8 DebugString[] = "Debug code 0xxx\r\n";
  sprintf(DebugString+13, "%0X\r\n", Code);
  mPort->OUT = Code;
  DBG (DEBUG_CODE_MESSAGE, DebugString);
}

VOID CpuDeadLoop ( VOID ) {
  //TODO blokada przerwan, blokada DMA
  volatile UINT8 x = 0;
  DBG (CRITICAL_ERROR_MESSAGE, "CpuDeadLoop()");
  while (x!=1){}
}

