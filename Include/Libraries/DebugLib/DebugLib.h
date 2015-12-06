/*
 * DebugLib.h
 *
 * Created: 9/1/2015 7:09:22 PM
 *  Author: Administrator
 */ 


#ifndef DEBUGLIB_H_
#define DEBUGLIB_H_
#include <PublicHeaders/Base.h>

/*
 * Initialize debug library and take over selected serial output and Port
 * @param Usart              Serial port to pass debug messages over
 * @param Port               Standart digital 8bit IO port to be used to display
 *                           debug codes
 */
void InitDebugLib(
  USART_t                             *Usart,
  PORT_t                              *Port
);

/*
 * Send a string over debug interface
 * @param String             C String to be sent
 */
void SendDebugString(
  CONST CHAR8                        *String
);

/*
 * Send a string over debug interface and terminate it with new line sequence.
 * @param String             C String to be sent
 */
void SendDebugLine(
    CONST CHAR8                         *String
);

/*
 * Send a Code indicating current state of the device.
 * @param Code               Code to sent
 */
void SendDebugCode(
  UINT8                                Code
);

#endif /* DEBUGLIB_H_ */
