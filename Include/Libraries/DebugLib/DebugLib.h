/*
 * DebugLib.h
 *
 * Created: 9/1/2015 7:09:22 PM
 *  Author: Administrator
 */ 


#ifndef DEBUGLIB_H_
#define DEBUGLIB_H_
#include <PublicHeaders/Base.h>

void InitDebugLib(
  VOID
);

/*
 * Send a string over debug interface
 * @param String             C String to be sent
 */
void SendDebugString(
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
