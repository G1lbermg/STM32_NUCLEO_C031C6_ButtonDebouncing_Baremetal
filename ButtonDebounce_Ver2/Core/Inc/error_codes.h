#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#include <stdint.h>

//Error code type is negative so that codes can also be negative.
typedef int32_t ErrorCode_t;


typedef enum
{
    // --- 0. General Status Codes (0 to -99) ---
    E_OK                          = 0,      // Successful execution

    E_ERROR_GENERIC               = -1,     // Catch-all unspecified error
    E_INVALID_ARGUMENT            = -2,     // Passed a NULL pointer or out-of-range value
    E_TIMEOUT                     = -3,     // Operation timed out
    E_NOT_INITIALIZED             = -4,     // Module was used before initialization

    // --- 1. System/Clock Errors (-100 to -199) ---
    // Start System/Clock errors from -100
    E_CLOCK_HSE_NOT_READY         = -101,   // High-Speed External (HSE) oscillator failed to stabilize
    E_CLOCK_SYSCLK_NOT_READY      = -102,   // System Clock failed to switch to the desired source
    E_CLOCK_INVALID_CONFIG        = -103,   // Configuration parameters (PLL, prescalers) are invalid

    // --- 2. GPIO/LED/Button Module Errors (-200 to -299) ---
    E_GPIO_INVALID_PORT           = -201,   // Invalid GPIO Port passed (e.g., NULL)
    E_GPIO_INVALID_PIN            = -202,   // Pin number out of the 0-15 range
    E_GPIO_INIT_FAILED            = -203,   // General initialization failure (e.g., clock enable failure)
    E_LED_WRITE_FAIL              = -204,   // Specific error during a turnOn/turnOff call

	// --- 3. USART/Communication Errors (-300 to -399) ---
	E_USART_INIT_FAILED           = -301,   // General failure during USART peripheral initialization
	E_USART_TX_TIMEOUT            = -302,   // Transmit operation timed out waiting for the TDR to be empty
	E_USART_INVALID_HANDLE        = -303,   // The provided USART handle/pointer is NULL or invalid
	E_USART_CLOCK_ENABLE_FAILED   = -304,   // Failed to enable the necessary clock for the USART module
	E_USART_BUFFER_OVERFLOW       = -305,   // Formatted message was truncated due to buffer size (128 bytes)

	// --- 4. Timer Errors (-400 to -499) ---
	E_TIMER_INIT_FAILED           = -401,   // General failure during TIMER peripheral initialization
	E_TIMER_FREQ_TOO_HIGH         = -402,   // Frequency selected during initialization was too high
	E_TIMER_CALC_ERROR            = -403,   // Prescaler plus one value was calculated to be zero
	E_TIMER_FREQ_TOO_LOW          = -404,   // Frequency selected during initialization was too low



    // --- Add more here as your project grows ---

} ErrorCode_e;

#endif
