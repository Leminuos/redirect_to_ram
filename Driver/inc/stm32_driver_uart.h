#ifndef __DRIVER_UART__
#define __DRIVER_UART__

#include "stm32f103.h"
#include "stm32_hal_util.h"

typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIOA_TypeDef;

#define GPIO_MODE9_2MHZ     (0x2 << 4)      // MODE9 = bits 6:4
#define GPIO_CNF9_AF_PP     (0x2 << 6)      // CNF9  = bits 7:6

#define GPIO_MODE10_INPUT   (0x0 << 8)      // MODE10 = bits 10:8
#define GPIO_CNF10_FLOAT    (0x1 << 10)     // CNF10  = bits 11:10

typedef struct {
    volatile uint32_t SR;     // Status register
    volatile uint32_t DR;     // Data register
    volatile uint32_t BRR;    // Baud rate register
    volatile uint32_t CR1;    // Control register 1
    volatile uint32_t CR2;    // Control register 2
    volatile uint32_t CR3;    // Control register 3
    volatile uint32_t GTPR;   // Guard time and prescaler register
} USART1_TypeDef;

#define USART_SR_TC         (1 << 6)
#define USART_SR_RXNE       (1 << 5)

#define USART_CR1_UE        (1 << 13)
#define USART_CR1_TE        (1 << 3)
#define USART_CR1_RE        (1 << 2)
#define USART_CR1_RXNEIE    (1 << 5)

/* GPIOA */
#define GPIOA_BASE          0x40010800
#define CGPIOA              ((GPIOA_TypeDef*) GPIOA_BASE)

/* USART1 */
#define USART1_BASE         0x40013800
#define CUSART1              ((USART1_TypeDef*) USART1_BASE)

void USART_Transmiter(uint8_t data);

#endif /* __DRIVER_UART__ */
