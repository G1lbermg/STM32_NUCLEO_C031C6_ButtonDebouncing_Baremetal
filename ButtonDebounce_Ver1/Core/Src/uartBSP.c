#include "uartBSP.h"


void initUART(void)
{
	/**************Setting up pin PA2 to transmit: **************/

	SET_BIT(RCC->IOPENR, RCC_IOPENR_GPIOAEN);

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

	//Set oversampling to 16
	// Inside initUART, near the other CR1 settings:
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
}

void printMsg(char *message, ...)
{
	char buff[128];

	va_list args;
	va_start(args, message);
	vsnprintf(buff,sizeof(buff),message, args);

	va_end(args);

	for(char *p = buff; *p != '\0'; p++){
		transmitByte(*p);
	}


}

/*
void printMsg(char *message)
{
	//Check if there is a message
	if(*message == '\0')
		return;

	char *c = (char *)message;

	while(*c){
		transmitByte(*c);
		c++;
	}
}
*/

void transmitByte(const char byte)
{
	//write data in the USART_TDR register. Check the USART_ISR -> TC bit before sending next data frame
	while(!(USART2->ISR & USART_ISR_TC))
		;

	WRITE_REG(USART2->TDR, byte);
}
