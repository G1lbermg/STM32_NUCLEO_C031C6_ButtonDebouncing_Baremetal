#include "ledBSP.h"

uint8_t initLED(GPIO_TypeDef *port, uint8_t pinNum)
{
	//Check if the pin is valid
	if((pinNum < 0U) || (pinNum > 15U))
		return 0;

	/****************************Clock Setup*****************************/
	//Check if clock port has already been enabled, if not then enable it
	//Also check that the port is a valid one
	if(port == GPIOA) {
		RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	}
	else if(port == GPIOB) {
		RCC->IOPENR |= RCC_IOPENR_GPIOBEN;
	}
	else if(port == GPIOC) {
		RCC->IOPENR |= RCC_IOPENR_GPIOCEN;
	}
	else if(port == GPIOD) {
		RCC->IOPENR |= RCC_IOPENR_GPIODEN;
	}
	else if(port == GPIOF) {
		RCC->IOPENR |= RCC_IOPENR_GPIOFEN;
	} else{
		return 0U;//not a valid port
	}

		/****************************Pin Setup*****************************/
    // set LED pin as push-pull output, no pull up or pull down, low speed
	//Set pin as output
	port->MODER &= ~((1 << (pinNum * 2)) | (1 << (pinNum * 2 + 1)));
	port->MODER |= ((1 << (pinNum * 2)));

	//Set pin as push-pull output
	port->OTYPER &= ~ (1 << pinNum);

	//Set pin at low speed
	port->OSPEEDR &= ~((1 << (pinNum * 2)) | (1 << (pinNum * 2 + 1)));
	port->OSPEEDR |= ((1 << (pinNum * 2)));

	//Set pin to no pull up pull down
	port->PUPDR &= ~((1 << (pinNum * 2)) | (1 << (pinNum * 2 + 1)));

	return 1;
}

uint8_t turnOnLED(GPIO_TypeDef *port, uint8_t pinNum)
{
	//Check if the pin is valid
	if((pinNum < 0U) || (pinNum > 15U))
		return 0;

	//Also check that the port is a valid one
	if(port == GPIOA
			|| port == GPIOB
			|| port == GPIOC
			|| port == GPIOD
			|| port == GPIOF) {

		port->BSRR = (1<<pinNum);

		return 1U;
	} else{
		return 0U;//not a valid port
	}
}

uint8_t turnOffLED(GPIO_TypeDef *port, uint8_t pinNum)
{
	//Check if the pin is valid
	if((pinNum < 0U) || (pinNum > 15U))
		return 0;

	//Also check that the port is a valid one
	if(port == GPIOA
			|| port == GPIOB
			|| port == GPIOC
			|| port == GPIOD
			|| port == GPIOF) {

		port->BSRR = (1<<(pinNum + 16));
	} else{
		return 0U;//not a valid port

		return 1U;
	}
}


