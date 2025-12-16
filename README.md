# Button Debouncing
## STM32 NUCLEO-C031C6 Bare Metal Implementation

Bare-metal C implementation for button debouncing on the STM32C031C6. The repository contains two versions: one uses the SysTick timer to debounce using blocking methods (V1), and the other uses the MCU's Timer 3 to debounce with a simple non-blocking state machine (V2). Both projects utilize USART to print the button state. Initialization for clocks and debug is done via CubeMX; all other configuration (GPIO, UART, and Timers) is handled via direct memory-mapped register access. A multi-tiered error handler, is also included in each project. The handler is integrated into all BSP's and enables the system to recover gracefully from common faults and protect itself from critical ones. Depending on the user's preference, the error handler can provide error logging using USART and/or indicate critical errors with an external led.  

### 1. Hardware Setup

   * **Board:** NUCLEO-C031C6
   * **MCU:** STM32C031C6 (ARM Cortex-M0+)
   * **Debugger:** ST-LINK V2-1 (SWD interface)
   * **Onboard LED:** Configured to PA5 (User LED 4)
   * **Onboard Button:** Configured to PC13 (B1 USER)

### 2. Software Setup

  * **IDE:** STM32CubeIDE 2.0.0
  * **Programming Languages:** C
  * **Toolchain:** GNU Tools for STM32 (13.3.rel1)
  * **Libraries & Header Files:** 
    * STM32 LL libraries
    * CMSIS STM32C0xx
    * CMSIS STM32C031xx (memory map)

### 3. How to Run
   1. **Import:** "Debounce Ver1" or "Debounce Ver2" sub folder as STM32CubeIde project
   2. **Setup (Option):** Review and adjust the error handler logging and LED indicator settings within the error_check_utilities.h file
   3. **Build:** Select Project > Build Project
   4. **Flash:** use Run or Debug icons
   5. **Run**:
      * Open serial terminal and set to 9600 Baud
      * Press Button and observe the LED toggling and messages printed to the terminal
