/*
 * Bluetooth.c
 *
 *  Created on: Nov 12, 2015
 *      Author: m
 */

#include <avr/io.h>
#include <util/delay.h>
#include "Bluetooth.h"
#include <Libraries/DebugLib/DebugLib.h>
#include <Libraries/Serial/Serial.h>
#include <Libraries/BaseLib/Base.h>
#include <string.h>

#define BTHC05_LED_PORT                PORTD
#define BTHC05_LED_PIN                 BIT5
#define BTHC05_KEY_PORT                PORTD
#define BTHC05_KEY_PIN                 BIT4
#define BTHC05_PWR_GATE_PORT           PORTD
#define BTHC05_PWR_GATE_PIN            BIT0

USART_t                               *mUsart = &USARTD0; //fixme go back to using mUsart instead of USARTD0
CHAR8                                  mRxSerialBuffer[64] = {NULL_CHAR};
CHAR8                                  mTxSerialBuffer[64] = {NULL_CHAR};

CONST CHAR8                            ComandTerminator[] = {
    CR_CHAR, LF_CHAR, NULL_CHAR
};

VOID SendReceiveAtCommand (
  CHAR8                               *CommandStr,
  CHAR8                               *ResponseBuffer,
  UINT16                               BufferSize
){
  RETURN_STATUS                        Status;
  DBG (INFO_MESSAGE, "SendReceiveAtCommand : ");

  SendString(&USARTD0,"AT");
  if (CommandStr != NULL && CommandStr[0] != NULL_CHAR) { //TODO if length(command) > 0
    DBG (INFO_MESSAGE, CommandStr);
    SendString(&USARTD0,"+");
    SendString(&USARTD0,CommandStr);
  }
  SendString(&USARTD0,ComandTerminator);
  Status = ReadLine(&USARTD0, ResponseBuffer, BufferSize);
  DBG (INFO_MESSAGE, ResponseBuffer);
}

VOID SetupIO ( VOID ) {
  DBG (INFO_MESSAGE, "SetupIO");
  //
  // Setup HC-05 related pins and USART
  //
  BTHC05_PWR_GATE_PORT.DIRSET = BTHC05_PWR_GATE_PIN;
  BTHC05_PWR_GATE_PORT.OUTCLR = BTHC05_PWR_GATE_PIN;

  BTHC05_LED_PORT.DIRCLR = BTHC05_LED_PIN;
  BTHC05_KEY_PORT.DIRSET = BTHC05_KEY_PIN;
  BTHC05_KEY_PORT.OUTSET = BTHC05_KEY_PIN;
}

VOID EnablePower ( VOID ) {
  DBG (INFO_MESSAGE, "EnablePower");
  BTHC05_PWR_GATE_PORT.OUTSET = BTHC05_PWR_GATE_PIN;
  _delay_ms(1000);
}

VOID PowerOnInAtMode ( VOID ) {
  DBG (INFO_MESSAGE, "PowerOnInAtMode");
  InitSerial (&USARTD0, b38400, Ridiculous);
  BTHC05_KEY_PORT.OUTSET = BTHC05_KEY_PIN;
  _delay_ms (10);
  EnablePower ();
}

VOID PowerOnInNormalMode ( VOID ) {
  DBG (INFO_MESSAGE, "PowerOnInNormalMode");
  InitSerial (&USARTD0, b9600, Ridiculous);
  BTHC05_KEY_PORT.OUTCLR = BTHC05_KEY_PIN;
  _delay_ms(10);
  EnablePower ();
}

VOID PowerOff ( VOID ) {
  DBG (INFO_MESSAGE, "PowerOff");
  BTHC05_PWR_GATE_PORT.OUTCLR = BTHC05_PWR_GATE_PIN;
  _delay_ms(10);
}

VOID ResetIntoAtMode ( VOID ) {
  DBG (INFO_MESSAGE, "ResetIntoAtMode");
  PowerOff ();
  PowerOnInAtMode ();
}

VOID ResetIntoNormalMode ( VOID ) {
  DBG (INFO_MESSAGE, "ResetIntoAtMode");
  PowerOff ();
  PowerOnInNormalMode ();
}

RETURN_STATUS InitBluetooth (
  USART_t                             *Usart
)
{
  DBG (INFO_MESSAGE, "InitBluetooth");

  //mUsart = Usart; //FIXME ta instrukcja zawiesza CPU
  SetupIO ();

  DEBUG_CODE(
    ResetIntoAtMode ();
    SendReceiveAtCommand (NULL, mRxSerialBuffer, sizeof (mRxSerialBuffer));
    ASSERT(strstr (mRxSerialBuffer, "OK") != NULL);
    SendReceiveAtCommand ("NAME=MROZO", mRxSerialBuffer, sizeof (mRxSerialBuffer));
    ASSERT(strstr (mRxSerialBuffer, "OK") != NULL);
    SendReceiveAtCommand ("NAME", mRxSerialBuffer, sizeof (mRxSerialBuffer));
    ASSERT(strstr (mRxSerialBuffer, "+NAME:MROZO") != NULL);
    SendReceiveAtCommand("PSWD=1234",mRxSerialBuffer, sizeof (mRxSerialBuffer));
    ASSERT(strstr (mRxSerialBuffer, "OK") != NULL);
  );

  ResetIntoNormalMode ();

  return SUCCESS;
}
