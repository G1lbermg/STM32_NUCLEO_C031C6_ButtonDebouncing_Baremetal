# Button Debouncing
## STM32 NUCLEO-C031C6 Bare Metal Implementation

Bare-metal C implementation for button debouncing on the STM32C031C6. The repository contains two versions: one uses the SysTick timer to debounce using blocking methods, and the other uses the MCU's Timer 3 to debounce with two simple non-blocking state machines. Both projects utilize USART to print the button state. Initialization for clocks and debug is done via CubeMX; all other configuration (GPIO, UART, and Timers) is handled via direct memory-mapped register access. A multi-tiered error handler, is also included in each project. The handler is integrated into all BSP's and enables the system to recover gracefully from common faults and protect itself from critical ones. Depending on the user's preference, the error handler can provide error logging using USART and/or indicate critical errors with an external led.  

### 🛠️ STM32 Nucleo Setup

| Category | Details |
| :--- | :--- |
| **Hardware** | NUCLEO-C031C6 (ARM Cortex-M0+) |
| **Debugger** | ST-LINK V2-1 (SWD interface) |
| **IDE** | STM32CubeIDE 2.0.0 |
| **Toolchain** | GNU Tools for STM32 (13.3.rel1) |
| **Libraries** | STM32 LL, CMSIS STM32C0xx, CMSIS STM32C031xx |

---

### 💡 Implementation Versions

#### **Version 1: Systick Timer (Blocking)**
User button toggles the onboard LED. Debouncing is performed by creating a blocking delay using the Systick timer.  
* **Input:** PC13 (B1 USER Button)
* **Output:** PA5 (Onboard User LED4)

<img width="850" height="667" alt="Nucleo Button Debouncing" src="https://github.com/user-attachments/assets/d7a996df-2ec1-47fc-b5d7-38a5443a4351" />


#### **Version 2: Timer 3 (Non-blocking)**
User button toggles the onboard LED. Debouncing is performed using Timer 3 by creating two simple non-blocking state machines. 
* **Input:** PC13 (B1 USER Button)
* **Output:** PA5 (Onboard User LED4)

<img width="749" height="600" alt="Debouncing State Machine" src="https://github.com/user-attachments/assets/846402cc-9398-45f9-bd19-366cf4ec3a8b" />

---

### 🚀 How to Run
   1. **Import:** `Debounce_SysTick_Blocking` or `Debounce_Timer_StateMachine` sub folder as STM32CubeIde project
   2. **Configure:** (Optional) Adjust error logging and indicator settings in `error_check_utilities.h`.
   3. **Build & Flash:** Select **Project > Build**, then use the **Run** or **Debug** icons.
   5. **Monitor**:
      * Open serial terminal and set to **9600 Baud**.
      * Press Button and observe the LED toggling and messages printed to the terminal.
