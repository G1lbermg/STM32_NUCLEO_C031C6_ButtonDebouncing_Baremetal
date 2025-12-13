#include "error_check_utilities.h"

// --- ERROR LED ---------------------------------------------------
#ifdef ERROR_LED_ENABLE

 // This function prevents null pointer crashes if the user doesn't initialize LED_ON function
static void Default_LED_On(void)
{
	(void) 0;
}

void (*Err_LED_On)(void) = Default_LED_On;

void init_Error_LED_ON(void(*On_Function)(void))
{
	// Only update if the user passed a valid function
		if (On_Function != 0)
			Err_LED_On = On_Function;
		else
			Err_LED_On = Default_LED_On;
}

#endif



// --- ERROR Logger ---------------------------------------------------
#ifdef LOGGING_ENABLE


 // This function prevents null pointer crashes if the user doesn't initialize logger.
static ErrorCode_t Default_Log_Function(char *message, ...)
 {
     (void) message;
     return E_OK;
 }


ErrorCode_t (*Central_Log_Function)(char *, ...) = Default_Log_Function;

 //Initialize Error Utilities Logging
 void Init_Error_Utilities_Logging(ErrorCode_t (*printFxn)(char *, ...))
 {
     if (printFxn != 0)
         Central_Log_Function = printFxn;
     else
    	 Central_Log_Function = Default_Log_Function;
 }

#endif

// --- CENTRAL ERROR HANDLER ---------------------------------------------------
void Central_Error_Handler(ErrorCode_t errorCode, const char *file, int line)
{
 /********************** 1. Identify Logging Critical Failure ***********************/
    if (errorCode == E_USART_INIT_FAILED || errorCode == E_USART_CLOCK_ENABLE_FAILED) {

		#ifdef ERROR_LED_ENABLE
    	Err_LED_On();
		#endif

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
	#ifdef ERROR_LED_ENABLE
	Err_LED_On();
	#endif

    __disable_irq();
    while (1)
    {
        // The debugger can inspect the local variables (errorCode, file, line)
        // in the stack frame of this function.
    }
}
