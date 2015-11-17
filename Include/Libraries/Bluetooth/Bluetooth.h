/*
 * Bluetooth.h
 *
 *  Created on: Nov 12, 2015
 *      Author: m
 */

#ifndef _BLUETOOTH_BLUETOOTH_H_
#define _BLUETOOTH_BLUETOOTH_H_

#include "PublicHeaders/Base.h"

/*
 * Initilize bluetooth.
 *
 * @retval SUCCESS                     Bluetooth module is ready to use
 * @retval GENERAL_ERROR               Failed to initialize bluetooth module
 * @retval NOT_SUPPORTED               Functionality is not yet supported
 */
RETURN_STATUS InitBluetooth (
  VOID
);

#endif /* INCLUDE_LIBRARIES_BLUETOOTH_BLUETOOTH_H_ */
