/*
 * DebugLib.h
 *
 * Created: 9/1/2015 7:09:22 PM
 *  Author: Administrator
 */ 

//todo SelfTestDebugLibrary

#ifndef DEBUGLIB_H_
#define DEBUGLIB_H_
#include <Libraries/BaseLib/Base.h>

#define GET_LOGGING_MASK() (LOGGING_MASK)

#define GET_LOGGING_LEVEL_STRING(TYPE) (GetLoggingLevelString ((TYPE)))

#define CPU_DEAD_LOOP() CpuDeadLoop()

#define __STRINGIFY_MACRO(x) #x
#define STRINGIFY_MACRO(x) __STRINGIFY_MACRO(x)
#define __STR__LINE__ STRINGIFY_MACRO(__LINE__)

#ifdef DEBUG
  #define IS_DEBUG_ENABLED TRUE

  /*
   * Send message over debugging interface.
   * @param TYPE             Type of the message. Can be either INFO_MESSAGE or
   *                         CRITICAL_ERROR_MESSAGE or ERROR_MESSAGE or
   *                         WARNING_MESSAGE.
   * @param MESSAGE          String to get logged.
   */
  #define DBG(TYPE,MESSAGE)                                                    \
  DEBUG_CODE(                                                                  \
    if (((GET_LOGGING_MASK ()) & (TYPE))!=0) {                                 \
      SendDebugString (GET_LOGGING_LEVEL_STRING((TYPE)));                      \
      SendDebugString (": ");                                                  \
      SendDebugLine ((MESSAGE));                                               \
    }                                                                          \
  )

  /*
   * This macro is used to insert a prefix to debug code. If a debug switch is
   * not enabled, this macro will insert nothing. Its not suggested to use it
   * manually, instead use DEBUG_CODE macro.
   */
  #define DEBUG_CODE_START()                                                   \
  do {                                                                         \
    if (IS_DEBUG_ENABLED) {                                                    \
      UINT8 __DebugCodeLocal

  /*
   * This macro is used to insert a postfix to debug code. If a debug switch is
   * not enabled, this macro will insert nothing. Its not suggested to use it
   * manually, instead use DEBUG_CODE macro.
   */
  #define DEBUG_CODE_END()                                                     \
      __DebugCodeLocal = 0;                                                    \
      __DebugCodeLocal++;                                                      \
    }                                                                          \
  } while (FALSE)

  /*
   * Compile the code only if Debug switch is enabled
   */
  #define DEBUG_CODE(code)                                                     \
    DEBUG_CODE_START();                                                        \
    code                                                                       \
    DEBUG_CODE_END()

  /*
   * Assert the EXPRESSION is TRUE, if not, send a critical error to debug the
   * interface and stop the CPU. Works only if debug switch is enabled.
   * @param EXPRESSION       Expression to be evaluated. If this expression
   *                         evaluates to 0, this causes an assertion failure
   *                         that terminates the program.
   */
  #define ASSERT(EXPRESSION)                                                   \
    DEBUG_CODE_START();                                                        \
    if((EXPRESSION) == FALSE) {                                                  \
      SendDebugString (GET_LOGGING_LEVEL_STRING(CRITICAL_ERROR_MESSAGE));      \
      SendDebugString (": Assertion failed in ");                              \
      SendDebugString (__FILE__);                                              \
      SendDebugString (":");                                                   \
      SendDebugLine (__STR__LINE__);                                           \
      CPU_DEAD_LOOP();                                                         \
    }                                                                          \
    DEBUG_CODE_END()

  /*
   * Send the 8bit code to a debug code output device
   */
  #define DBG_CODE(code)                                                       \
    DEBUG_CODE_START();                                                        \
    SendDebugCode(code);                                                       \
    DEBUG_CODE_END()

#else
//TODO czy to konieczne? wszystko i tak jest w DEBUG_CODE
  #define IS_DEBUG_ENABLED FALSE

  /*
   * Send message over debugging interface.
   * @param TYPE             Type of the message. Can be either INFO_MESSAGE or
   *                         CRITICAL_ERROR_MESSAGE or ERROR_MESSAGE or
   *                         WARNING_MESSAGE.
   * @param MESSAGE          String to get logged.
   */
  #define DBG(TYPE,MESSAGE)

  /*
   * This macro is used to insert a prefix to debug code. If a debug switch is
   * not enabled, this macro will insert nothing. Its not suggested to use it
   * manually, instead use DEBUG_CODE macro.
   */
  #define DEBUG_CODE_START()

  /*
   * This macro is used to insert a postfix to debug code. If a debug switch is
   * not enabled, this macro will insert nothing. Its not suggested to use it
   * manually, instead use DEBUG_CODE macro.
   */
  #define DEBUG_CODE_END()

  /*
   * Compile the code only if Debug switch is enabled
   */
  #define DEBUG_CODE(code)

  /*
   * Assert the EXPRESSION is TRUE, if not, send a critical error to debug the
   * interface and stop the CPU. Works only if debug switch is enabled.
   * @param EXPRESSION       Expression to be evaluated. If this expression
   *                         evaluates to 0, this causes an assertion failure
   *                         that terminates the program.
   */
  #define ASSERT(EXPRESSION)

  /*
   * Send the 8bit code to a debug code output device
   */
  #define DBG_CODE(code)                                                       \

#endif

/*
 * Initialize debug library and take over selected serial output and Port
 * @param Usart              Serial port to pass debug messages over
 * @param Port               Standard digital 8bit IO port to be used to display
 *                           debug codes
 */
void InitDebugLib(
  USART_t                             *Usart,
  PORT_t                              *Port
);

/*
 * Send a string over debug interface. It's not suggested to use it directly.
 * @param String             C String to be sent
 */
void SendDebugString(
  CONST CHAR8                         *String
);

/*
 * Send a string over debug interface and terminate it with new line sequence.
 * It's not suggested to use it directly.
 * @param String             C String to be sent
 */
void SendDebugLine(
  CONST CHAR8                         *String
);

/*
 * Send a Code indicating current state of the device. It's not suggested to use
 * it directly.
 * @param Code               Code to sent
 */
void SendDebugCode(
  UINT8                                Code
);

/*
 * Stop code execution.
 */
VOID CpuDeadLoop ( VOID );


#endif /* DEBUGLIB_H_ */
