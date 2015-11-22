/*
 * XMega.c
 *
 *  Created on: Nov 12, 2015
 *      Author: m
 */

#include "XMega.h"
#include <avr/io.h>
#include <Libraries/Bluetooth/Bluetooth.h>
#include <Libraries/Serial/Serial.h>
#include <Libraries/Portx/Portx.h>

void InitMainClock()
{
  //
  //http://morf.lv/modules.php?name=tutorials&lasit=29
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
  SendDebugString("$ InitBluetoothDriver\r\n");
  PORTD.OUTSET = PIN3_bm;
  PORTD.DIRSET = PIN3_bm;
  PORTD.OUTCLR = PIN2_bm;
  PORTD.DIRCLR = PIN2_bm;
  InitBluetooth (&USARTC0);
}

void InitHardware ()
{
  InitMainClock ();
  InitBluetoothDriver ();
}
