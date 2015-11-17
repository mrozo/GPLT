/*
 * Bluetooth.c
 *
 *  Created on: Nov 12, 2015
 *      Author: m
 */

#include <avr/io.h>
#include "Bluetooth.h"

#define BTHC05_LED_PORT                PORTD
#define BTHC05_LED_PIN                 BIT5
#define BTHC05_KEY_PORT                PORTD
#define BTHC05_KEY_PIN                 BIT4

RETURN_STATUS InitBluetooth ()
{
  BTHC05_LED_PORT.DIRCLR = BTHC05_LED_PIN;
  BTHC05_KEY_PORT.DIRSET = BTHC05_KEY_PIN;
  BTHC05_KEY_PORT.OUTSET = BTHC05_KEY_PIN;

  return SUCCESS;
}
