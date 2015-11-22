/*
 * Base.h
 *
 *
 * Created: 9/1/2015 5:39:09 PM
 * Author: Administrator
 */ 


#ifndef _BASE_H_
#define _BASE_H_

#include <avr/io.h>
/*
  Macro used to indicate the indicate the parameter INPUTa function definition is optional
*/
#define OPTIONAL


typedef uint8_t                        UINTN;
/*

*/
#define BIT0                           (1)
#define BIT1                           (1<<1)
#define BIT2                           (1<<2)
#define BIT3                           (1<<3)
#define BIT4                           (1<<4)
#define BIT5                           (1<<5)
#define BIT6                           (1<<6)
#define BIT7                           (1<<7)
#define BIT8                           (1<<8)
#define BIT9                           (1<<9)
#define BIT10                          (1<<10)
#define BIT11                          (1<<11)
#define BIT12                          (1<<12)
#define BIT13                          (1<<13)
#define BIT14                          (1<<14)
#define BIT15                          (1<<15)
#define BIT16                          (1<<16)
#define BIT17                          (1<<17)
#define BIT18                          (1<<18)
#define BIT19                          (1<<19)
#define BIT20                          (1<<20)
#define BIT21                          (1<<21)
#define BIT22                          (1<<22)
#define BIT23                          (1<<23)
#define BIT24                          (1<<24)
#define BIT25                          (1<<25)
#define BIT26                          (1<<26)
#define BIT27                          (1<<27)
#define BIT28                          (1<<28)
#define BIT29                          (1<<29)
#define BIT30                          (1<<30)
#define BIT31                          (1<<31)

#define PIN(n)                         (1<<(n))
/*
#define PIN0                           PIN(0)
#define PIN1                           PIN(1)
#define PIN2                           PIN(2)
#define PIN3                           PIN(3)
#define PIN4                           PIN(4)
#define PIN5                           PIN(5)
#define PIN6                           PIN(6)
#define PIN7                           PIN(7)*/
#define PIN8                           PIN(8)
#define PIN9                           PIN(9)
#define PIN10                          PIN(10)
#define PIN11                          PIN(11)
#define PIN12                          PIN(12)
#define PIN13                          PIN(13)
#define PIN14                          PIN(14)
#define PIN15                          PIN(15)
#define PIN16                          PIN(16)
#define PIN17                          PIN(17)
#define PIN18                          PIN(18)
#define PIN19                          PIN(19)
#define PIN20                          PIN(20)
#define PIN21                          PIN(21)
#define PIN22                          PIN(22)
#define PIN23                          PIN(23)
#define PIN24                          PIN(24)
#define PIN25                          PIN(25)
#define PIN26                          PIN(26)
#define PIN27                          PIN(27)
#define PIN28                          PIN(28)
#define PIN29                          PIN(29)
#define PIN30                          PIN(30)
#define PIN31                          PIN(31)

#define BYTE(data,n)                   (((UINT8 *) &(data))[(n)])
#define BYTE0(data)                    (BYTE((data),(0)))
#define BYTE1(data)                    (BYTE((data),(1)))
#define BYTE2(data)                    (BYTE((data),(2)))
#define BYTE3(data)                    (BYTE((data),(3)))
#define BYTE4(data)                    (BYTE((data),(4)))
#define BYTE5(data)                    (BYTE((data),(5)))
#define BYTE6(data)                    (BYTE((data),(6)))
#define BYTE7(data)                    (BYTE((data),(7)))

#define COMPILE_TIME_BYTE(data,n)      (data)<<((n)*8)
#define COMPILE_TIME_BYTE0(data)       (COMPILE_TIME_BYTE((data),(0)))
#define COMPILE_TIME_BYTE1(data)       (COMPILE_TIME_BYTE((data),(1)))
#define COMPILE_TIME_BYTE2(data)       (COMPILE_TIME_BYTE((data),(2)))
#define COMPILE_TIME_BYTE3(data)       (COMPILE_TIME_BYTE((data),(3)))
#define COMPILE_TIME_BYTE4(data)       (COMPILE_TIME_BYTE((data),(4)))
#define COMPILE_TIME_BYTE5(data)       (COMPILE_TIME_BYTE((data),(5)))
#define COMPILE_TIME_BYTE6(data)       (COMPILE_TIME_BYTE((data),(6)))
#define COMPILE_TIME_BYTE7(data)       (COMPILE_TIME_BYTE((data),(7)))

typedef void                           VOID;
#define CONST                          const

#define NULL ((VOID*)0))

typedef __UINT8_TYPE__                 BYTE;
typedef __INT8_TYPE__                  CHAR8;
typedef __UINT16_TYPE__                CHAR16;

typedef __UINT8_TYPE__                 UINT8;
typedef __UINT16_TYPE__                UINT16;
typedef __UINT32_TYPE__                UINT32;

typedef __INT8_TYPE__                  INT8;
typedef __INT16_TYPE__                 INT16;
typedef __INT32_TYPE__                 INT32;

typedef UINTN                          BOOLEAN;
#define TRUE  ((BOOLEAN)(1==1))
#define FALSE ((BOOLEAN)(2==1))

/*
  Register 
*/
typedef UINTN                          REGISTERN;
typedef UINT8                          REGISTER8;
typedef UINT16                         REGISTER16;
typedef UINT32                         REGISTER32;

/*
  Digital output value register
*/
typedef REGISTERN                      DIGITAL_OUTPUT;
/*
  Digital input value register
*/
typedef REGISTERN                      DIGITAL_INPUT;

/*
  1 byte wide bitmask
*/
typedef UINT8                          MASK8;
/*
  2 bytes wide bitmask
*/
typedef UINT16                         MASK16;
/*
  
  4 bytes wide bitmask
*/
typedef UINT32                         MASK32;
/*
  Bitmask as wide as platforms data bus is
*/
typedef UINTN                          MASKN;

/*
  Type used to indicate status of operation completion
*/
typedef UINTN                          RETURN_STATUS;

#define STATUS_CODE(code) (RETURN_STATUS)(code)

#define SUCCESS                        STATUS_CODE(0x00)
#define GENERAL_ERROR                  STATUS_CODE(0x01)
#define OUT_OF_RESOURCES               STATUS_CODE(0x02)
#define TIMEOUT                        STATUS_CODE(0x03)
#define INVALID_PARAMETER              STATUS_CODE(0x04)
#define DEVICE_ERROR                   STATUS_CODE(0x05)
#define NOT_SUPPORTED                  STATUS_CODE(0x06)
#define BUFFER_TOO_SMALL               STATUS_CODE(0x07)

/*
  Check if the given Status code is an error status code
*/
inline BOOLEAN IsError (
  RETURN_STATUS                        Status
)
{
  return (BOOLEAN)((Status!=SUCCESS)?TRUE:FALSE);
}

/*
  Check if the given Status code is a code indicating successfull operation complection
*/
inline BOOLEAN IsSuccess (
  RETURN_STATUS                        Status
)
{
  return (BOOLEAN)((Status==SUCCESS)?TRUE:FALSE);
}


typedef enum {
  b9600,
  b38400,
  b115200
} BAUD_RATE;

typedef enum {
  Minimum,
  Medium,
  Ridiculous,
} CLOCK_FREQUENCY;


#define NULL_CHAR                       ((CHAR8)0x00)
#define SOH_CHAR                        ((CHAR8)0x01)
#define STX_CHAR                        ((CHAR8)0x02)
#define ETX_CHAR                        ((CHAR8)0x03)
#define EOT_CHAR                        ((CHAR8)0x04)
#define ENQ_CHAR                        ((CHAR8)0x05)
#define ACK_CHAR                        ((CHAR8)0x06)
#define BEL_CHAR                        ((CHAR8)0x07)
#define BS_CHAR                         ((CHAR8)0x08)
#define HT_CHAR                         ((CHAR8)0x09)
#define LF_CHAR                         ((CHAR8)0x0A)
#define VT_CHAR                         ((CHAR8)0x0B)
#define FF_CHAR                         ((CHAR8)0x0C)
#define CR_CHAR                         ((CHAR8)0x0D)
#define SO_CHAR                         ((CHAR8)0x0E)
#define SI_CHAR                         ((CHAR8)0x0F)
#define DLE_CHAR                        ((CHAR8)0x10)
#define DC1_CHAR                        ((CHAR8)0x11)
#define DC2_CHAR                        ((CHAR8)0x12)
#define DC3_CHAR                        ((CHAR8)0x13)
#define DC4_CHAR                        ((CHAR8)0x14)
#define NAK_CHAR                        ((CHAR8)0x15)
#define SYN_CHAR                        ((CHAR8)0x16)
#define ETB_CHAR                        ((CHAR8)0x17)
#define CAN_CHAR                        ((CHAR8)0x18)
#define EM_CHAR                         ((CHAR8)0x19)
#define SUB_CHAR                        ((CHAR8)0x1A)
#define ESC_CHAR                        ((CHAR8)0x1B)
#define FS_CHAR                         ((CHAR8)0x1C)
#define GS_CHAR                         ((CHAR8)0x1D)
#define RS_CHAR                         ((CHAR8)0x1E)
#define US_CHAR                         ((CHAR8)0x1F)

#endif /* _BASE_H_ */
