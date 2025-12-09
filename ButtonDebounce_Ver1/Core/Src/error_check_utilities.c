#include "error_check_utilities.h"
#include "main.h"

// --- CENTRAL ERROR HANDLER ---
void Central_Error_Handler(ErrorCode_t errorCode, const char *file, int line)
{
	//Function will load Error code, file number and line number onto registers before halting
	//This way we can reference them and figure out what caused the program to halt

    // --- Enter Safe State and Halt ---
    __disable_irq();

    while (1)
    {

    }
}
