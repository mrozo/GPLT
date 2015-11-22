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
 * Initialize USART
 * @param Usart              Usart control structure
 * @param Speed              Desired bit rate
 * @param ClockFrequency     Current peripherial clock frequency
 */
void InitSerial (
  volatile USART_t                    *Usart,
  BAUD_RATE                            Speed,
  CLOCK_FREQUENCY                      ClockFrequency
);

/*
 * Send character over UART using blocking IO. Does not support 9 bit words
 * @param Usart              Usart control structure
 * @param Char               8 bit character to be sent
 */
void inline SendChar(
  volatile USART_t                    *Usart,
  BYTE                                 Char
);

/*
 * Send a string over UART using blocking IO. Does not support 9 bit words
 * @param USART              Usart control structure
 * @param str                null terminated C string
 */
void SendString(
  volatile USART_t                    *Usart,
  CHAR8                               *String
);

/*
 * Read a single 8 bit char from USART in blocking mode. Function does not
 * any error checking
 * @param Usart              Usart control structure
 * @retval the character
 */
CHAR8 ReadChar (
  volatile USART_t                    *Usart
);

/*
 * Wait for a char on RX
 * @param Usart              Usart control structure
 */
VOID WaitForChar (
  volatile USART_t                    *Usart
);
/*
 * Check if an input buffer contains any new data
 * @param Usart              Usart control structure
 * @retval TRUE              There is a new data to be read
 * @retval FALSE             There is no new data to be read
 */
BOOLEAN IsRxDataReady (
  volatile USART_t                    *Usart
);
/*
 * Read a line from the USART. The read line will not contain '\n' and will be
 * a proper NULL terminated C String.
 * @param Usart              Usart control structure
 * @param LineBuffer         Pointer to a buffer to save the line to
 * @param BufferSize         Size of the line buffer
 * @retval SUCCESS           The line has been successfully read. The line
 *                           buffer contains the line terminated with a NULL
 *                           character.
 * @retval BUFFER_TOO_SMALL  The buffer is not big enough to read a whole line.
 *                           The LineBuffer contains a NULL terminated C String,
 *                           the USART input data buffer may not be empty
*/
RETURN_STATUS ReadLine (
  volatile USART_t                    *Usart,
  CHAR8                               *LineBuffer,
  UINT16                               BufferSize
);


#endif /* SERIAL_H_ */
