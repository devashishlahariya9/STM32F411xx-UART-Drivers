#include "STM32F411xx_UART.h"

int main(void)
{
	UART_Init(UART6, UART6_USE_GPIOC, 9600);

	UART_SendString(UART6, "\nSTARTING STRING WRITE\n");

	UART_Printf(UART6, "INTEGER: %d | CHARACTER: %c | STRING: %s | HEX: 0x%x | FLOAT: %f | TRUNCATED FLOAT: %.2f\n", 6, 'H', "Hello!!", 55, 3.141592, 3.141592);

	UART_SendString(UART6, "\nSTRING WRITE FINISHED\n");

	while(1)
	{

	}
	return 0;
}
