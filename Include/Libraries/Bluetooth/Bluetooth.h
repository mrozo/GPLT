/*
 * Bluetooth.h
 *
 *  Created on: Nov 12, 2015
 *      Author: m
 */

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include <Libraries/BaseLib/Base.h>

/*
 * Initilize HC-05 bluetooth module.
 *
 * @param Usart                        Pointer to an USART control strcuture
 * @retval SUCCESS                     Bluetooth module is ready to use
 * @retval GENERAL_ERROR               Failed to initialize bluetooth module
 * @retval NOT_SUPPORTED               Functionality is not yet supported
 */
RETURN_STATUS InitBluetooth (
  USART_t                             *Usart
);

#endif /*_BLUETOOTH_H_ */
