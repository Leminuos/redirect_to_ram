#include "stm32_driver_uart.h"
#include <stdio.h>

#if defined (__CC_ARM)
struct __FILE
{
    int handle;
    /* Whatever you require here. If the only file you are using is */
    /* standard output using printf() for debugging, no file handling */
    /* is required. */
};

/* FILE is typedef in stdio.h. */
FILE __stdout;

int fputc(int ch, FILE *f)
{
    /* Your implementation of fputc(). */
    USART_Transmiter((uint8_t)ch);
    return ch;
}
#endif

void USARTInit(void)
{
    // Config clock
    RCC->APB2ENR.BITS.IOPAEN = 0x01;
    RCC->APB2ENR.BITS.USART1EN = 0x01;
    
    // Config PA9 - Transmitter
    GPIOA->CRH.BITS.CNF9 = 0x02;
    GPIOA->CRH.BITS.MODE9 = 0x02;
    
    // Config PA10 - Receiver
    GPIOA->CRH.BITS.CNF10 = 0x02;
    GPIOA->CRH.BITS.MODE10 = 0x00;
    
    // Baud rate = 115000 => USARTDIV: 39.0625
    USART1->BRR.BITS.Fraction = 0x01;
    USART1->BRR.BITS.Mantissa = 0x27;
    
    // Transmitter enable
    USART1->CR1.BITS.TE = 0x01;
    
    // Receiver enable
    USART1->CR1.BITS.RE = 0x01;
    
    // Receiver Interrupt enable
    USART1->CR1.BITS.RXNEIE = 0x01;
    
    // USART enable
    USART1->CR1.BITS.UE = 0x01;
    
    /* Cau hinh ngat NVIC */
    NVIC_EnableIRQ(USART1_IRQn);
    NVIC_SetPriority(USART1_IRQn, 0X01);
}

void TraceInit(void)
{
    /* Enable GPIOA and USART1 clock */
    RCC->APB2ENR.BITS.IOPAEN = 0x01;
    RCC->APB2ENR.BITS.USART1EN = 0x01;

    /* Configure PA9 (TX) as Alternate Function Push Pull, 2MHz */
    CGPIOA->CRH &= ~(0xF << 4);                        // Clear bits 7:4
    CGPIOA->CRH |= GPIO_MODE9_2MHZ | GPIO_CNF9_AF_PP;

    /* Configure PA10 (RX) as Input Floating */
    CGPIOA->CRH &= ~(0xF << 8);                        // Clear bits 11:8
    CGPIOA->CRH |= GPIO_MODE10_INPUT | GPIO_CNF10_FLOAT;

    /* Configure baudrate = 115200 for 72MHz clock => USARTDIV = 39.0625
     * Mantissa = 39 = 0x27, Fraction = 1
     * BRR = 0x0271
     */
    CUSART1->BRR = (0x27 << 4) | 0x1;

    /* Enable USART1: Transmit, Receive, RX interrupt, and USART */
    CUSART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE | USART_CR1_UE;
}

void USART_Transmiter(uint8_t data)
{
    while (!(CUSART1->SR & USART_SR_TC));  // Wait until Transmission Complete
    CUSART1->DR = data;
}
