/*
 * STM32F411xx_UART.h
 *
 * Created on: Feb 28, 2022
 * Author: Devashish Lahariya
*/

#ifndef STM32F411XX_UART_H_
#define STM32F411XX_UART_H_

#include "STM32F411xx_GPIO.h"

//USART -> SR
#define USART_PE	 	0U
#define USART_FE	 	1U
#define USART_NF	 	2U
#define USART_ORE	 	3U
#define USART_IDLE	 	4U
#define USART_RXNE	 	5U
#define USART_TC	 	6U
#define USART_TXE	 	7U
#define USART_LBD	 	8U
#define USART_CTS	 	9U

//USART -> BRR
#define DIV_Fraction 	0U
#define DIV_Mantissa 	4U

//USART -> CR1
#define USART_SBK		0U
#define USART_RWU		1U
#define USART_RE		2U
#define USART_TE		3U
#define USART_IDLEIE	4U
#define USART_RXNEIE	5U
#define USART_TCIE		6U
#define USART_TXEIE		7U
#define USART_PEIE		8U
#define USART_PS		9U
#define USART_PCE		10U
#define USART_WAKE		11U
#define USART_M			12U
#define USART_UE		13U
#define USART_OVER8		15U

//USART -> CR2
#define USART_ADD		0U
#define USART_LBDL		5U
#define USART_LBDIE		6U
#define USART_LBCL		8U
#define USART_CPHA		9U
#define USART_CPOL		10U
#define USART_CLKEN		11U
#define USART_STOP		12U
#define USART_LINEN		14U

//USART -> CR3
#define USART_EIE		0U
#define USART_IREN		1U
#define USART_IRLP		2U
#define USART_HDSEL		3U
#define USART_NACK		4U
#define USART_SCEN		5U
#define USART_DMAR		6U
#define USART_DMAT		7U
#define USART_RTSE		8U
#define USART_CTSE		9U
#define USART_CTSIE		10U
#define USART_ONEBIT	11U

//USART -> GTPR
#define USART_PSC		0U
#define USART_GT		8U

#define USART1_CLK_ENABLE() (RCC -> APB2ENR |= (1 << USART1EN))
#define USART2_CLK_ENABLE() (RCC -> APB1ENR |= (1 << USART2EN))
#define USART6_CLK_ENABLE() (RCC -> APB2ENR |= (1 << USART6EN))

#define USART1_CLK_DISABLE() (RCC -> APB2ENR &= ~(1 << USART1EN))
#define USART2_CLK_DISABLE() (RCC -> APB1ENR &= ~(1 << USART2EN))
#define USART6_CLK_DISABLE() (RCC -> APB2ENR &= ~(1 << USART6EN))

#define UART1_GPIOA_TX		9U
#define UART1_GPIOA_RX		10U
#define UART1_GPIOB_TX		6U
#define UART1_GPIOB_RX		7U

#define UART2_GPIOA_TX		2U
#define UART2_GPIOA_RX		3U
#define UART2_GPIOD_TX		5U
#define UART2_GPIOD_RX		6U

#define UART6_GPIOC_TX		6U
#define UART6_GPIOC_RX		7U

void UART1_USE_GPIOA(void);
void UART1_USE_GPIOB(void);
void UART2_USE_GPIOA(void);
void UART2_USE_GPIOD(void);
void UART6_USE_GPIOC(void);

void UART_Init(USART_PERIPHERALS_t* UART, void(*remap_func)(void), uint32_t _baudrate);
void UART_Deinit(USART_PERIPHERALS_t* UART);
void UART_SendChar(USART_PERIPHERALS_t* UART, uint8_t _data);
void UART_SendString(USART_PERIPHERALS_t* UART, const char* str);
char UART_ReadChar(USART_PERIPHERALS_t* UART);
void UART_ReadString(USART_PERIPHERALS_t* UART, char* _buffer);
void UART_Printf(USART_PERIPHERALS_t* UART, char* format, ...);

#endif /* STM32F411XX_UART_H_ */
