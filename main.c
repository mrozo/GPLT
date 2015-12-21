/*
 * main.c
 *
 * Created: 9/1/2015 4:34:35 PM
 *  Author: Administrator
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <Libraries/BaseLib/Base.h>
#include <Hardware/XMega/XMega.h>
#include <Libraries/Serial/Serial.h>
#include <Libraries/DebugLib/DebugLib.h>

VOID Int2Str (UINT8 input, CHAR8 output[3]) {
  UINT8 digit;

  digit = input%10;
  output[2] = (CHAR8)(digit + '0');
  input-=digit;
  input/=10;

  digit = input%10;
  output[1] = (CHAR8)(digit + '0');
  input-=digit;
  input/=10;

  digit = input%10;
  output[0] = (CHAR8)(digit + '0');
  input-=digit;
  input/=10;
}

int main (
  VOID
)
{
  InitHardware ();
  DBG (INFO_MESSAGE, __DATE__);
  DBG (INFO_MESSAGE, __TIME__);
  DBG (INFO_MESSAGE, "$ Witaj przyjacielu!");

  DBG (INFO_MESSAGE, "LOGGING_LEVEL test start");
  DBG (INFO_MESSAGE, "INFO_MESSAGE");
  DBG (DEBUG_CODE_MESSAGE, "DEBUG_CODE_MESSAGE");
  DBG (WARNING_MESSAGE, "WARNING_MESSAGE");
  DBG (ERROR_MESSAGE, "ERROR_MESSAGE");
  DBG (CRITICAL_ERROR_MESSAGE, "CRITICAL_ERROR_MESSAGE");
  DBG (INFO_MESSAGE, "LOGGING_LEVEL test stop");

  DBG (INFO_MESSAGE, "Assert test start");
  DBG (INFO_MESSAGE, "First - ASSERT(TRUE)");
  ASSERT (TRUE);
  //DBG (INFO_MESSAGE, "Second - ASSERT(FALSE)");
  //ASSERT (FALSE);
  DBG (INFO_MESSAGE, "After Assert test:");


  UINT8                                ButtonInput=0;
  UINT8                                LedOutput=0;
  UINT8 i=0;
  CHAR8                                Buf[4] = { NULL_CHAR };

  //LEDPORT
  PORTB.DIRSET = BIT0 | BIT1 | BIT2;
  PORTF.DIRSET = BIT3 | BIT4 | BIT5 | BIT6 | BIT7;


  //BUTTON PORT

  PORTA.DIRCLR = BIT0 | BIT1 | BIT2 | BIT5 | BIT6 | BIT7;
  PORTC.DIRCLR = BIT0 | BIT1;
  PORTC.PIN0CTRL = PORT_OPC_PULLUP_gc;
  PORTC.PIN1CTRL = PORT_OPC_PULLUP_gc;
  PORTA.PIN0CTRL = PORT_OPC_PULLUP_gc;
  PORTA.PIN1CTRL = PORT_OPC_PULLUP_gc;
  PORTA.PIN2CTRL = PORT_OPC_PULLUP_gc;
  PORTA.PIN5CTRL = PORT_OPC_PULLUP_gc;
  PORTA.PIN6CTRL = PORT_OPC_PULLUP_gc;
  PORTA.PIN7CTRL = PORT_OPC_PULLUP_gc;

  PORTC.DIRCLR = BIT0 | BIT1;
  //extrino ma wbudowane pullupy na c1/c0
  //PORTC.PIN0CTRL = PORT_OPC_PULLUP_gc;
  //PORTC.PIN1CTRL = PORT_OPC_PULLUP_gc;

  while (1) {
    _delay_ms(1000);
    ButtonInput = (~PORTA.IN) & (BIT0 | BIT1 | BIT2 | BIT5 | BIT6 | BIT7);
    ButtonInput = ButtonInput| (((~PORTC.IN) & (BIT0 | BIT1))<<3);

    LedOutput = ButtonInput;

    PORTB.OUTSET = (BIT0 | BIT1 | BIT2) & LedOutput;
    PORTB.OUTCLR = (BIT0 | BIT1 | BIT2) & (~LedOutput);
    PORTF.OUTSET = (BIT3 | BIT4 | BIT5 | BIT6 | BIT7) & LedOutput;
    PORTF.OUTCLR = (BIT3 | BIT4 | BIT5 | BIT6 | BIT7) & (~LedOutput);

    Int2Str(ButtonInput, Buf);
    DBG (INFO_MESSAGE, Buf);
    i++;
  }
  return 0;
}

//TODO DBG() test
//TODO LOGGING_LEVEL test
//TODO DEBUG_CODE()
//TODO ASSERT() test
//TODO DEBUG/RELEASE switch
//FIXME DBG_CODE(code) powoduje port^=code (PORTX_t NIE jest zgodny z PORT_t)!
