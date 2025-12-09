# Button Debouncing
## STM32 NUCLEO-C031C6 Bare Metal Implementation

Minimal C implementation for button debouncing on the STM32C031C6. The repository contains two versions: one using the SysTick timer for debouncing (V1), and the other using the MCU's Timer 3 (V2). Both projects utilize UART to print the button state. Initialization for clocks and debug is done via CubeMX; all other configuration (GPIO, UART, and Timers) is handled via direct memory-mapped register access. A basic error handler is also included in each project.  

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
   2. **Build:** Select Project > Build Project
   3. **Flash:** use Run or Debug icons
