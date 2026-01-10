#include "error_check_utilities.h"

/********************** Hardware Error Indicator *******************************************/
#ifdef HW_ERR_INDICATE_ENABLE

 // This function prevents null pointer crashes if the user doesn't initialize LED_ON function
static void Default_HW_Indicate_On(void)
{
	(void) 0;
}

static void (*HW_Indicate_On)(void) = Default_HW_Indicate_On;

void Config_HW_Err_Indicator(void(*On_Function)(void))
{
	// Only update if the user passed a valid function
		if (On_Function != 0)
			HW_Indicate_On = On_Function;
		else
			HW_Indicate_On = Default_HW_Indicate_On;
}

#endif

/************************ Error Logger ******************************************************/
#ifdef LOGGING_ENABLE


 // This function prevents null pointer crashes if the user doesn't initialize logger.
static ErrorCode_t Default_Log_Function(char *message, ...)
 {
     (void) message;
     return E_OK;
 }


static ErrorCode_t (*Central_Log_Function)(char *, ...) = Default_Log_Function;

 //Initialize Error Utilities Logging
 void Init_Error_Utilities_Logging(ErrorCode_t (*printFxn)(char *, ...))
 {
     if (printFxn != 0)
         Central_Log_Function = printFxn;
     else
    	 Central_Log_Function = Default_Log_Function;
 }

#endif

/**************** CENTRAL ERROR HANDLER *********************************************/
void Central_Error_Handler(ErrorCode_t errorCode, const char *file, int line)
{
 //Double check file pointer
	const char *log_file_ptr;
	if(file == 0)
		log_file_ptr = "UNKNOWN FILE";
	else
		log_file_ptr = file;


 //------------------- 1. Identify Logging Critical Failure -----------------------
    if (errorCode == E_USART_INIT_FAILED || errorCode == E_USART_CLOCK_ENABLE_FAILED) {

		#ifdef HW_ERR_INDICATE_ENABLE
    	HW_Indicate_On();
		#endif

        // Skip all logging and enter safe state
        __disable_irq();

        while (1)
        {
            // The debugger can inspect the local variables (errorCode, file, line)
            // in the stack frame of this function.
        }
    }

 //---------- 2. LOGGING IS POSSIBLE (Proceed with Tiered Policy) -----------------

    // ++++++++ POLICY TIER 2: MINOR/WARNINGS (Log and Continue) ++++++++++++
    if (errorCode == E_INVALID_ARGUMENT || errorCode == E_USART_BUFFER_OVERFLOW) {

    	#ifdef LOGGING_ENABLE
        Central_Log_Function("WARNING: Code %d at %s,line:%d", errorCode, log_file_ptr, line);
		#endif

        return;
    }

    // +++++ POLICY TIER 1: MAJOR/RETRYABLE ERRORS (Log and Continue/Notify) +++++
    if (errorCode == E_USART_TX_TIMEOUT || errorCode == E_GPIO_INIT_FAILED) {

		#ifdef LOGGING_ENABLE
    	Central_Log_Function("MAJOR ERROR: Code %d at %s,line:%d", errorCode, log_file_ptr, line);
		#endif

        // This function RETURNS, allowing the main loop to continue.
        return;
    }

    // +++++ POLICY TIER 0: CRITICAL/FATAL ERRORS (Log and HALT) ++++++++
    // Any error not caught above (e.g., clock errors, generic errors) is fatal.
	#ifdef LOGGING_ENABLE
    Central_Log_Function("FATAL ERROR: Code %d at %s,line:%d", errorCode, log_file_ptr, line);
	#endif

    // Enter Safe State and Halt
	#ifdef HW_ERR_INDICATE_ENABLE
    HW_Indicate_On();
	#endif

    __disable_irq();
    while (1)
    {
        // The debugger can inspect the local variables (errorCode, file, line)
        // in the stack frame of this function.
    }
}
