#include <button_BSP.h>

ErrorCode_t initButton(Button_t *button, GPIO_TypeDef *port, uint8_t pinNum)
{
	//Check for NULL Pointer
	if(button == 0)
		return E_INVALID_ARGUMENT;

	//Check if the pin is valid
	if(pinNum > 15)
		return E_GPIO_INVALID_PIN;;

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
		return E_GPIO_INVALID_PORT;//not a valid port
	}

		/****************************Pin Setup*****************************/
    //Set button as input with pull up resistor
	port->MODER &= ~((1 << (pinNum * 2)) | (1 << (pinNum * 2 + 1)));

	port->PUPDR &= ~((1 << (pinNum * 2)) | (1 << (pinNum * 2 + 1)));
	port->PUPDR |= (1<< (pinNum * 2));

	/****************************Mask Setup*****************************/
	button->port = port;
	button->readMask = (1<<pinNum);

	return E_OK;
}


ErrorCode_t readButton(Button_t *button, uint16_t *readData)
{
	//Check for NULL Pointer
	if(button == 0 || readData == 0)
		return E_INVALID_ARGUMENT;

	*readData = (button->port->IDR & button->readMask);

	return E_OK;
}



