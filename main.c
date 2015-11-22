/*
 * BluetoothDoer.c
 *
 * Created: 9/1/2015 4:34:35 PM
 *  Author: Administrator
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <PublicHeaders/Base.h>
#include <Hardware/XMega/XMega.h>
#include <Libraries/DebugLib/DebugLib.h>

int main (
  VOID
)
{
  UINT8 I = 0;
  CHAR8                                Buffer[16]={NULL_CHAR};
  InitHardware ();
  InitDebugLib();
  while (1) {

    SendDebugString("$ Waiting for an input\r\n");
    ReadLine(&USARTC0,Buffer,sizeof(Buffer));
    SendDebugString("Got string:\r\n");
    SendDebugString(Buffer);
    SendDebugString("\n");


  }
  return 0;
}
