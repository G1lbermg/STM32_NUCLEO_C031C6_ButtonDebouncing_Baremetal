#ifndef ERROR_CHECK_UTILITIES_H
#define ERROR_CHECK_UTILITIES_H

#include "error_codes.h"
#include "main.h"


void Central_Error_Handler(ErrorCode_t errorCode, const char *file, int line);

static inline void check_Error(ErrorCode_t result, const char *file, int line) {
    if (result != E_OK) {
    	//Set Break Point line below
        Central_Error_Handler(result, file, line);
    }
}

/********************Uncomment the error tools being used*****************************/

/***************ERROR MESSAGING*****************/
//Comment or uncomment depending on whether or not it's needed
#define LOGGING_ENABLE

#ifdef LOGGING_ENABLE

extern ErrorCode_t (*Central_Log_Function)(char *, ...);
void Init_Error_Utilities_Logging(ErrorCode_t (*printFxn)(char *, ...));

#endif

/***************LED INDICATORS*****************/
//Comment or uncomment depending on whether or not it's needed
#define ERROR_LED_ENABLE


#ifdef ERROR_LED_ENABLE

extern void (*Err_LED_On)(void);
void init_Error_LED_ON(void(*On_Function)(void));

#endif
/**************************************************************************************/


#endif
