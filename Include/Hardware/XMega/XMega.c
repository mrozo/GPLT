/*
 * XMega.c
 *
 *  Created on: Nov 12, 2015
 *      Author: m
 */

#include "XMega.h"
#include <avr/io.h>
#include <Hardware/Portx/Portx.h>
#include <Libraries/Bluetooth/Bluetooth.h>
#include <Libraries/DebugLib/DebugLib.h>
#include <Libraries/Serial/Serial.h>

void InitMainClock()
{
  //
  // http://morf.lv/modules.php?name=tutorials&lasit=29
  // Set up the main clock to 32MHz, Trigger protection mechanism, Enable
  // internal  32Mhz crystal
  //
  OSC_CTRL |= OSC_RC32MEN_bm;
  while(!(OSC_STATUS & OSC_RC32MRDY_bm));
  CCP = CCP_IOREG_gc;
  CLK_CTRL = CLK_SCLKSEL_RC32M_gc;
}

void InitBluetoothDriver ()
{
  DBG (INFO_MESSAGE, "$ InitBluetoothDriver\r\n");
  PORTD.OUTSET = PIN3_bm;
  PORTD.DIRSET = PIN3_bm;
  PORTD.OUTCLR = PIN2_bm;
  PORTD.DIRCLR = PIN2_bm;
  InitBluetooth (&USARTD0);
}

void InitDebugDriver ()
{
  InitPortx();
  PORTC.OUTSET = PIN3_bm;
  PORTC.DIRSET = PIN3_bm;
  PORTC.OUTCLR = PIN2_bm;
  PORTC.DIRCLR = PIN2_bm;
  InitDebugLib (&USARTC0, &PORTX);
  DBG (
      INFO_MESSAGE,
        "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"\
        "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n"
      );
  DBG (INFO_MESSAGE, "$ InitDebugDriver end\r\n");
}

void InitHardware ()
{
  InitMainClock ();
  InitDebugDriver ();
  InitBluetoothDriver ();
}
