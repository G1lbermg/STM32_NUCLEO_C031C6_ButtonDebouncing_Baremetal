#include "error_check_utilities.h"

// --- ERROR Logger ---------------------------------------------------
#ifdef LOGGING_ENABLE

ErrorCode_t (*Central_Log_Function)(char *, ...);

 // This function just prevents null pointer crashes if the user doesn't to initialize logger.
 ErrorCode_t Default_Log_Function(char *message, ...) {
     (void)message;
     return E_OK;
 }


 //Initialize Error Utilities Logging
 void Init_Error_Utilities_Logging(ErrorCode_t (*printFxn)(char *, ...)) {
     if (printFxn != 0) {
         Central_Log_Function = printFxn;
     }
 }

#endif

// --- CENTRAL ERROR HANDLER ---------------------------------------------------
void Central_Error_Handler(ErrorCode_t errorCode, const char *file, int line)
{
 /********************** 1. Identify Logging Critical Failure ***********************/
    if (errorCode == E_USART_INIT_FAILED || errorCode == E_USART_CLOCK_ENABLE_FAILED) {

      //  ERROR_LED_ON();

        // Skip all logging and enter safe state
        __disable_irq();

        while (1)
        {
            // The debugger can inspect the local variables (errorCode, file, line)
            // in the stack frame of this function.
        }
    }

 /************* 2. LOGGING IS POSSIBLE (Proceed with Tiered Policy) *******************/

    // --- POLICY TIER 2: MINOR/WARNINGS (Log and Continue) ---
    if (errorCode == E_INVALID_ARGUMENT || errorCode == E_USART_BUFFER_OVERFLOW) {

    	#ifdef LOGGING_ENABLE
        Central_Log_Function("WARNING: Code %d at %s:%d", errorCode, file, line);
		#endif

        return;
    }

    // --- POLICY TIER 1: MAJOR/RETRYABLE ERRORS (Log and Continue/Notify) ---
    if (errorCode == E_USART_TX_TIMEOUT || errorCode == E_GPIO_INIT_FAILED) {

		#ifdef LOGGING_ENABLE
    	Central_Log_Function("MAJOR ERROR: Code %d at %s:%d", errorCode, file, line);
		#endif

        // This function RETURNS, allowing the main loop to continue.
        return;
    }

    // --- POLICY TIER 0: CRITICAL/FATAL ERRORS (Log and HALT) ---
    // Any error not caught above (e.g., clock errors, generic errors) is fatal.
	#ifdef LOGGING_ENABLE
    Central_Log_Function("FATAL ERROR: Code %d at %s:%d", errorCode, file, line);
	#endif

    // Enter Safe State and Halt
 //   ERROR_LED_ON();
    __disable_irq();
    while (1)
    {
        // Indicate fatal error state
    }
}
