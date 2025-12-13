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

/********************Comment or Uncomment the error tools as needed*****************************/

/***************ERROR MESSAGING*****************/
//Comment or uncomment depending on whether or not it's needed
#define LOGGING_ENABLE

#ifdef LOGGING_ENABLE

//The function provided will be used by the Central Error Handler
//to log hardware faults
void Init_Error_Utilities_Logging(ErrorCode_t (*printFxn)(char *, ...));

#endif

/***************Hardware Error Indicators*****************/
//Comment or uncomment depending on whether or not it's needed
#define HW_ERR_INDICATE_ENABLE

#ifdef HW_ERR_INDICATE_ENABLE

//The function provided will be used by the Central Error Handler
//to enable the  hardware level error indication
void Config_HW_Err_Indicator(void(*On_Function)(void));

#endif
/**************************************************************************************/


#endif
