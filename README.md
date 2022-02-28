# STM32F4-UART-Drivers
UART Bare Metal Drivers for STM32F4 Family of Microcontrollers. The Driver contains APIs for the user to Send & Receive Data via UART.
Supports BAUD RATE From 300 To 1000000 BAUD. All 3 USART Peripherals i.e USART1, USART2 & USART6 Are Available To Use.

*NOTE: On The STM32F411E-DISCO Board The USART1 Can't Use GPIOA Pins (Although This Functionality Has Still Been Provided)*

# Keywords:
1. UARTx => x = (1, 2, 6)
2. GPIOy => y = (A, B, C, D)
3. UART_BAUDRATE => 300 To 1000000
4. UART1_USE_GPIOA
5. UART1_USE_GPIOB
6. UART2_USE_GPIOA
7. UART2_USE_GPIOD
8. UART6_USE_GPIOC
9. UART_Init
10. UART_SendChar
11. UART_SendString
12. UART_ReadChar
13. UART_ReadString

# API Usage:
1. UART_Init(*UARTx*, *UARTx_USE_GPIOy*, *UART_BAURDRATE*);
2. UART_SendChar(*UARTx*, *character*);
3. UART_SendString(*UARTx*, *string*);
4. UART_ReadChar(*UARTx*);
5. UART_ReadString(*UARTx*, *buffer*);
**Make Sure To Have A Large Enough Buffer To Store Data For UART_ReadString()**
