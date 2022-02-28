#include "STM32F411xx_UART.h"

int main(void)
{
	UART_Init(UART6, UART6_USE_GPIOC, 9600);

	UART_SendString(UART6, "\nSTARTING STRING WRITE\n");

	UART_Printf(UART6, "UART = %d | CHARACTER: %c | STRING: %s | HEX: 0x%x\n", 6, 'H', "Hello!!", 55);

	UART_SendString(UART6, "\nSTRING WRITE FINISHED\n");

	while(1)
	{

	}
	return 0;
}
