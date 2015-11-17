/*
 * Serial.h
 *
 *  Created on: Nov 10, 2015
 *      Author: m
 */

#ifndef SERIAL_H_
#define SERIAL_H_
#include <PublicHeaders/Base.h>

/*
 * Initialize USART0 on PD2,PD3.
 * @param Speed              Desired bit rate
 * @param ClockFrequency     Current peripherial clock frequency
 * @param USART              Usart control structure
 */
void InitSerial (
  USART_t                             *USART,
  BAUD_RATE                            Speed,
  CLOCK_FREQUENCY                      ClockFrequency
);

/*
 * Send character over UART using blocking IO. Does not support 9 bit words
 * @param word               word to be sent
 * @param USART              Usart control structure
 */
void inline sendChar(
  USART_t                             *USART,
  BYTE                                 word
);

/*
 * Send a string over UART using blocking IO. Does not support 9 bit words
 * @param str                null terminated C string
 * @param USART              Usart control structure
 */
void sendString(
  USART_t                             *USART,
  CHAR8 *str
);
#endif /* SERIAL_H_ */
