#ifndef ERROR_CHECK_UTILITIES_H
#define ERROR_CHECK_UTILITIES_H

#include "error_codes.h"

void Central_Error_Handler(ErrorCode_t errorCode, const char *file, int line);

static inline void check_Error(ErrorCode_t result, const char *file, int line) {
    if (result != E_OK) {
    	//Set Break Point line below
        Central_Error_Handler(result, file, line);
    }
}

#endif
