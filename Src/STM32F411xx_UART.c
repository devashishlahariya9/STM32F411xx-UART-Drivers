/*
 * STM32F411xx_UART.c
 *
 * Created on: Feb 28, 2022
 * Author: Devashish Lahariya
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "STM32F411xx_UART.h"

static void FPU_Init(void)
{
	FPU -> CPACR = (0xF << 20);

	while(!(FPU -> CPACR & (0xF << 20)));
}

void UART1_USE_GPIOA(void)		//Do Not Use If Your PORTA Is Not Free. Otherwise It Could Cause Unknown Errors.
{
	GPIOA_CLK_ENABLE();
	USART1_CLK_ENABLE();

	GPIOA -> AFRH &= ~(0xF << 4);
	GPIOA -> AFRH &= ~(0xF << 8);
	GPIOA -> AFRH |=  (AF7 << 4) | (AF7 << 8);

	GPIO_setMode(GPIOA, UART1_GPIOA_TX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_setMode(GPIOA, UART1_GPIOA_RX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
}

void UART1_USE_GPIOB(void)
{
	GPIOB_CLK_ENABLE();
	USART1_CLK_ENABLE();

	GPIOB -> AFRL &= ~(0xF << 24);
	GPIOB -> AFRL &= ~(0xF << 28);
	GPIOB -> AFRL |=  (AF7 << 24) | (AF7 << 28);

	GPIO_setMode(GPIOB, UART1_GPIOB_TX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_setMode(GPIOB, UART1_GPIOB_RX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
}

void UART2_USE_GPIOA(void)
{
	GPIOA_CLK_ENABLE();
	USART2_CLK_ENABLE();

	GPIOA -> AFRL &= ~(0xF << 8);
	GPIOA -> AFRL &= ~(0xF << 12);
	GPIOA -> AFRL |=  (AF7 << 8) | (AF7 << 12);

	GPIO_setMode(GPIOA, UART2_GPIOA_TX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_setMode(GPIOA, UART2_GPIOA_RX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
}

void UART2_USE_GPIOD(void)
{
	GPIOD_CLK_ENABLE();
	USART2_CLK_ENABLE();

	GPIOD -> AFRL &= ~(0xF << 20);
	GPIOD -> AFRL &= ~(0xF << 24);
	GPIOD -> AFRL |=  (AF7 << 20) | (AF7 << 24);

	GPIO_setMode(GPIOD, UART2_GPIOD_TX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_setMode(GPIOD, UART2_GPIOD_RX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
}

void UART6_USE_GPIOC(void)
{
	GPIOC_CLK_ENABLE();
	USART6_CLK_ENABLE();

	GPIOC -> AFRL &= ~(0xF << 24);
	GPIOC -> AFRL &= ~(0xF << 28);
	GPIOC -> AFRL |=  (AF8 << 24) | (AF8 << 28);

	GPIO_setMode(GPIOC, UART6_GPIOC_TX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
	GPIO_setMode(GPIOC, UART6_GPIOC_RX, GPIO_HIGH_SPEED, GPIO_MODE_PUSH_PULL, GPIO_MODE_AFIO);
}

void UART_Init(USART_PERIPHERALS_t* UART, void(*remap_func)(void), uint32_t _baudrate)
{
	FPU_Init();

	int product = (_baudrate * 16);
	float usart_div = (float)F_CPU / (float)product;
	int div_mantissa = usart_div;
	int div_fraction = (((float)usart_div - (float)div_mantissa) * 16);

	uint16_t brr_val = ((div_mantissa << 4) | div_fraction);

	remap_func();

	UART -> BRR = brr_val;

	UART -> CR1 |= (1 << USART_TE) | (1 << USART_RE);
	UART -> CR1 |= (1 << USART_UE);
}

void UART_Deinit(USART_PERIPHERALS_t* UART)
{
	if(UART == UART1)
	{
		RCC -> APB2RSTR |= (1 << USART1RST);
	}
	else if(UART == UART2)
	{
		RCC -> APB1RSTR |= (1 << USART2RST);
	}
	else if(UART == UART6)
	{
		RCC -> APB2RSTR |= (1 << USART6RST);
	}
}

void UART_SendChar(USART_PERIPHERALS_t* UART, uint8_t _data)
{
	while(!(UART -> SR & (1 << USART_TXE)));

	UART -> DR = _data;
}

void UART_SendString(USART_PERIPHERALS_t* UART, const char* str)
{
	for(; *str != '\0'; str++)
	{
		while(!(UART -> SR & (1 << USART_TXE)));

		UART -> DR = *str;
	}
}

char UART_ReadChar(USART_PERIPHERALS_t* UART)
{
	while(!(UART -> SR & (1 << USART_RXNE)));

	return (UART -> DR);
}

void UART_ReadString(USART_PERIPHERALS_t* UART, char* _buffer)
{
	int i = 0;
	char ch;

	do
	{
		ch = UART_ReadChar(UART);

		if(ch != '\n')
		{
			_buffer[i] = ch;
			i++;
		}
		else
		{
			_buffer[i] = '\0';
			break;
		}
	} while(1);
}

static char* convert(unsigned int num, int base)
{
    static char Representation[]= "0123456789ABCDEF";
    static char buffer[50];
    char* ptr;

    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = Representation[num % base];
        num /= base;
    }while(num != 0);

    return(ptr);
}

void UART_Printf(USART_PERIPHERALS_t* UART, char* format, ...)
{
    char* traverse;
    unsigned int i;
    char* s;

    int len = strlen(format);

    char* str = (char*)malloc(len + 1);
    strcpy(str, format);
    str[len - 1] = '\0';

    va_list arg;
    va_start(arg, format);

    for(traverse = str; *traverse != '\0'; traverse++)
    {
        while(*traverse != '%')
        {
            UART_SendChar(UART, *traverse);
        	traverse++;
        }
        traverse++;

        switch(*traverse)
        {
            case 'c': i = va_arg(arg, int);
                        UART_SendChar(UART, i);
                        break;

            case 'd': i = va_arg(arg, int);
                        if(i < 0)
                        {
                            i = -i;
                            UART_SendChar(UART, '-');
                        }
                        UART_SendString(UART, convert(i, 10));
                        break;

            case 'o': i = va_arg(arg, unsigned int);
            			UART_SendString(UART, convert(i, 8));
            			break;

            case 's': s = va_arg(arg, char*);
                        UART_SendString(UART, s);
                        break;

            case 'x': i = va_arg(arg, unsigned int);
                        UART_SendString(UART, convert(i, 16));
                        break;
        }
    }
    va_end(arg);
    free(str);
}
