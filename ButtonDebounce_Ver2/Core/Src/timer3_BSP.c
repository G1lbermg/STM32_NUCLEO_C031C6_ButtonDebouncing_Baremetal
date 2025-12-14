#include "timer3_BSP.h"

#define PSC_VALUE 7499U
#define ARR_VALUE 6399U

uint32_t volatile timeCounter3 = 0U;

void TIM3_IRQHandler(void)
{
	__disable_irq();

	// Clear the Update Interrupt Flag (UIF) if it was set by the UEV
	CLEAR_BIT(TIM3->SR, TIM_SR_UIF);

	//Increment timer
	timeCounter3++;

	__enable_irq();
}


void initTmr3(void)
{
	//Enable timer 3 clock gate
	SET_BIT(RCC->APBENR1,RCC_APBENR1_TIM3EN);

	//Set to up counting
	CLEAR_BIT(TIM3->CR1, TIM_CR1_DIR);

	//Update request only at counter overflow/underflow
	SET_BIT(TIM3->CR1, TIM_CR1_URS);

	//Enable UEV(update events)
	CLEAR_BIT(TIM3->CR1,TIM_CR1_UDIS);

	//Set prescaler to 7499, arr to 6399 to achieve 1Hz update frequency
	WRITE_REG(TIM3->PSC,PSC_VALUE);
	WRITE_REG(TIM3->ARR, ARR_VALUE);

	//Force update to registers
	WRITE_REG(TIM3->EGR,TIM_EGR_UG);

	// Clear the Update Interrupt Flag (UIF) if it was set by the UEV
	CLEAR_BIT(TIM3->SR, TIM_SR_UIF);

	//Enable update interrupts
	SET_BIT(TIM3->DIER,TIM_DIER_UIE);

	//Enable timer3 interrupt
	__NVIC_EnableIRQ(TIM3_IRQn);

	//Enable the counter
	SET_BIT(TIM3->CR1, TIM_CR1_CEN);
}



void delay1Sec(void)
{
	uint32_t startTime;

    // Read the starting time in a single critical section
	__disable_irq();
	startTime = timeCounter3;
	__enable_irq();

	// The only time we need to disable IRQs is when reading timeCounter3.
	while(1) // Loop forever until condition is met
	{
        uint32_t currentTime;

        // Read the current time (critical section around a single 32-bit read)
		__disable_irq();
		currentTime = timeCounter3;
		__enable_irq();

        // Check condition
        if (currentTime - startTime >= 1U)
        {
            break; // Exit the function after 1 second has passed
        }
	}
}
/**************************** Polling based code **********************/

/*
 #include "timer3_BSP.h"


#define PSC_VALUE 7499U
#define ARR_VALUE 6399U


void initTmr3(void)

{
	//Enable timer 3 clock gate
	SET_BIT(RCC->APBENR1,RCC_APBENR1_TIM3EN);

	//Set to up counting
	CLEAR_BIT(TIM3->CR1, TIM_CR1_DIR);

	//Update request only at counter overflow/underflow
	SET_BIT(TIM3->CR1, TIM_CR1_URS);

	//Enable UEV(update events)
	CLEAR_BIT(TIM3->CR1,TIM_CR1_UDIS);


	//Set prescaler to 7499, arr to 6399 to achieve 1Hz update frequency
	WRITE_REG(TIM3->PSC,PSC_VALUE);
	WRITE_REG(TIM3->ARR, ARR_VALUE);


	//Force update to registers
	WRITE_REG(TIM3->EGR,TIM_EGR_UG);

	//Enable the counter
	SET_BIT(TIM3->CR1, TIM_CR1_CEN);
}


void delay1Sec(void)

{
	// Clear the Update Interrupt Flag (UIF) if it was set by the UEV
	CLEAR_BIT(TIM3->SR, TIM_SR_UIF);

	//Poll until 1 second has passed by
	while(READ_BIT(TIM3->SR, TIM_SR_UIF) != 1)
		;
}

 */
