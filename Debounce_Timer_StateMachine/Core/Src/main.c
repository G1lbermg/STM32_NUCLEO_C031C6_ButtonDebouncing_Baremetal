/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "timer3_BSP.h"
#include "usart2_BSP.h"
#include "button_BSP.h"
#include "led_BSP.h"
#include "error_check_utilities.h"
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define PIN_0 0x0U
#define PIN_1 0x1U
#define PIN_2 0x2U
#define PIN_3 0x3U
#define PIN_4 0x4U
#define PIN_5 0x5U
#define PIN_6 0x6U
#define PIN_7 0x7U
#define PIN_8 0x8U
#define PIN_9 0x9U
#define PIN_10 0xAU
#define PIN_11 0xBU
#define PIN_12 0xCU
#define PIN_13 0xDU
#define PIN_14 0xEU
#define PIN_15 0xFU

#define NOT_PRESSED 0x1U
#define PRESSED 0x0U
#define DEBOUNCE_TIME 200U
#define LED_ON_TIME 200U

#define TMR3_FREQ 1000U


/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
static LED_t Err_LED;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

ErrorCode_t init_ErrorLED(GPIO_TypeDef *port, uint8_t pinNum);
void turn_On_ErrorLED(void);
void turn_Off_ErrorLED(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*********Error LED functions*********************/
ErrorCode_t init_ErrorLED(GPIO_TypeDef *port, uint8_t pinNum)
{
	ErrorCode_t code = init_LED(&Err_LED, port, pinNum);

	return code;
}

void turn_On_ErrorLED(void)
{
	turn_On_LED(&Err_LED);
}
void turn_Off_ErrorLED(void)
{
	turn_Off_LED(&Err_LED);
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
  LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

  /* SysTick_IRQn interrupt configuration */
  NVIC_SetPriority(SysTick_IRQn, 3);

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  /* USER CODE BEGIN 2 */

  //------------------Setting Up Error Utilities-----------------------------
  check_Error((init_ErrorLED(GPIOA, PIN_9)), __FILE__, __LINE__);
  Config_HW_Err_Indicator(turn_On_ErrorLED);

  check_Error( initUSART2(), __FILE__, __LINE__);
  Init_Error_Utilities_Logging(printMsgNL_USART2);


  //------------------Setting Up Peripherals-----------------------------
  LED_t LED1;
  check_Error((init_LED(&LED1,GPIOA, PIN_5)), __FILE__, __LINE__);

  Button_t Button1;
  check_Error(initButton(&Button1,GPIOC, PIN_13), __FILE__,__LINE__);

  check_Error(initTmr3(TMR3_FREQ),__FILE__,__LINE__);

  check_Error((printMsgNL_USART2("Nucleo Initialized!")),__FILE__,__LINE__);

  //-------------------------------------------------------------------------

  __enable_irq();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint16_t buttonState = NOT_PRESSED;
  uint32_t currentTime, ledStartTime, debounceStartTime;

  check_Error(elapsedTicks_Tmr3(&currentTime),__FILE__,__LINE__);
  check_Error(elapsedTicks_Tmr3(&ledStartTime),__FILE__,__LINE__);
  check_Error(elapsedTicks_Tmr3(&debounceStartTime),__FILE__,__LINE__);


  check_Error(turn_Off_LED(&LED1),__FILE__,__LINE__);
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	//Turn off LED after alloted time
	elapsedTicks_Tmr3(&currentTime);
	if((currentTime-ledStartTime) >= LED_ON_TIME){
		  check_Error(turn_Off_LED(&LED1),__FILE__,__LINE__);
	}

	//Register a button press then ignore everything else within debounce period
	check_Error(readButton(&Button1, &buttonState),__FILE__,__LINE__);
	if(buttonState == PRESSED &&
			((currentTime-debounceStartTime) >= DEBOUNCE_TIME)){

		check_Error((printMsgNL_USART2("Button pressed!")),__FILE__,__LINE__);
		check_Error(turn_On_LED(&LED1),__FILE__,__LINE__);

		check_Error(elapsedTicks_Tmr3(&ledStartTime),__FILE__,__LINE__);
		check_Error(elapsedTicks_Tmr3(&debounceStartTime), __FILE__, __LINE__);
	}
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  LL_FLASH_EnablePrefetch();

  LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

  /* HSE configuration and activation */
  LL_RCC_HSE_Enable();
  while(LL_RCC_HSE_IsReady() != 1)
  {
  }

  /* Set AHB prescaler*/
  LL_RCC_SetAHBPrescaler(LL_RCC_HCLK_DIV_1);

  /* Sysclk activation on the HSE */
  LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSE);
  while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSE)
  {
  }

  /* Set APB1 prescaler*/
  LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
  LL_Init1msTick(48000000);
  /* Update CMSIS variable (which can be updated also through SystemCoreClockUpdate function) */
  LL_SetSystemCoreClock(48000000);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
	Central_Error_Handler(E_ERROR_GENERIC, __FILE__, __LINE__);
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

