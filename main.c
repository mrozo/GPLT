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
  InitHardware ();
  InitDebugLib();
  while (1) {
    I++;
    SendDebugCode(I);
    _delay_ms(100);
  }
  return 0;
}
