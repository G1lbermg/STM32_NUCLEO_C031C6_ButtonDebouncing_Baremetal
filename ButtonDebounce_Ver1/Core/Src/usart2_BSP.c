#include <usart2_BSP.h>

#define CARRIAGE_RETURN 13U
#define NEW_LINE 10U

ErrorCode_t initUSART2(void)
{
	/**************Setting up pin PA2 to transmit: **************/

	SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);

	//Set pin to usart2 mode
	CLEAR_BIT(GPIOA->MODER, GPIO_MODER_MODE2);
	SET_BIT(GPIOA->MODER,GPIO_MODER_MODE2_1);

	CLEAR_BIT(GPIOA->AFR[0], GPIO_AFRL_AFSEL2);
	SET_BIT(GPIOA->AFR[0], GPIO_AFRL_AFSEL2_0);


	/***************Protocol to setup internal peripheral according to the manual for transmission: **************/
	//Enable clock
	SET_BIT(RCC->APBENR1, RCC_APBENR1_USART2EN);

	//Define word length
	CLEAR_BIT(USART2->CR1, USART_CR1_M1);
	CLEAR_BIT(USART2->CR1, USART_CR1_M0);

	//Set over-sampling to 16
	CLEAR_BIT(USART2->CR1, USART_CR1_OVER8);

	//Define Baud rate
	//USARTDIV = 48Mhz/9600baud = 0x1388U
	WRITE_REG(USART2->BRR, 0x1388);

	//Program number of stop bits
	CLEAR_BIT(USART2->CR2, USART_CR2_STOP_0);
	CLEAR_BIT(USART2->CR2, USART_CR2_STOP_1);

	//Enable the UE bit
	SET_BIT(USART2->CR1, USART_CR1_UE);

	//Set the Transmit enable bit
	SET_BIT(USART2->CR1, USART_CR1_TE);

	return E_OK ;
}

ErrorCode_t printMsg_USART2(char *message, ...)
{
	if (message == NULL) {
	        return E_INVALID_ARGUMENT;
	}

	char buff[128];
	uint32_t count;
	ErrorCode_t err = E_OK, tx_err;

	va_list args;
	va_start(args, message);
	count = vsnprintf(buff,sizeof(buff),message, args);
	va_end(args);

	if (count >= sizeof(buff) || count < 0) {
		// Truncated message will be sent but error is still signaled.
		err = E_USART_BUFFER_OVERFLOW;
	}

	for(char *p = buff; *p != '\0'; p++){
		// Error will be propagated to main
		tx_err = transmitByte_USART2(*p);
		if (tx_err != E_OK) {
			return tx_err;
		}
	}

	return err;
}

ErrorCode_t printMsgNL_USART2(char *message, ...)
{
	if (message == NULL) {
	        return E_INVALID_ARGUMENT;
	}

	char buff[128];
	uint32_t count;
	ErrorCode_t err = E_OK, tx_err;

	va_list args;
	va_start(args, message);
	count = vsnprintf(buff,sizeof(buff),message, args);
	va_end(args);

	if (count >= sizeof(buff) || count < 0) {
	        // Truncated message will be sent but error is still signaled.
	        err = E_USART_BUFFER_OVERFLOW;
	}

	for(char *p = buff; *p != '\0'; p++){
		// Error will be propagated to main
		tx_err = transmitByte_USART2(*p);
	    if (tx_err != E_OK)
	    	return tx_err;
	}

	tx_err = transmitByte_USART2(CARRIAGE_RETURN);
	if (tx_err != E_OK)
		return tx_err;

	tx_err = transmitByte_USART2(NEW_LINE);
	if (tx_err != E_OK)
		return tx_err;

	return err;
}

ErrorCode_t transmitByte_USART2(const char byte)
{
	uint32_t timeout_counter = 0;
	const uint32_t MAX_TIMEOUT = 0xFFFFU;

	//write data in the USART_TDR register. Check the USART_ISR -> TC bit before sending next data frame
	while(!(USART2->ISR & USART_ISR_TC)){
		// If transmit takes too long then timeout
		if (timeout_counter > MAX_TIMEOUT) {
			return E_USART_TX_TIMEOUT;
		}
		timeout_counter++;
	}
	WRITE_REG(USART2->TDR, byte);

	return E_OK;
}

