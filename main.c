/*
 * BluetoothDoer.c
 *
 * Created: 9/1/2015 4:34:35 PM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <util/delay.h>
#include <PublicHeaders/Base.h>
#include <Hardware/XMega/XMega.h>
#include <Libraries/Serial/Serial.h>
#include <Libraries/DebugLib/DebugLib.h>

int main (
  VOID
)
{
  InitHardware ();
  SendDebugLine("\r\n\r\n\r\n\r\n");
  SendDebugLine("$ Witaj przyjacielu!");

  while (1) {

  }
  return 0;
}
