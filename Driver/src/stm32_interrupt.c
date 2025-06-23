#include "stm32_interrupt.h"
#include "main.h"

extern void ButtonProcess(void);
void prvGetRegistersFromStack(uint32_t* pulFaultStackAddress);

void SysTick_Handler(void)
{
    ButtonProcess();
}

void HardFault_Handler(void)
{
    __asm volatile (
        "tst lr, #4                         \n"
        "ite eq                             \n"
        "mrseq r0, msp                      \n"
        "mrsne r0, psp                      \n"
        "ldr r1, [r0, #24]                  \n"
        "ldr r2, =prvGetRegistersFromStack  \n"
        "bx r2                              \n"
    );
}

void MemManage_Handler(void)
{
    __asm volatile (
        "tst lr, #4                         \n"
        "ite eq                             \n"
        "mrseq r0, msp                      \n"
        "mrsne r0, psp                      \n"
        "ldr r1, [r0, #24]                  \n"
        "ldr r2, =prvGetRegistersFromStack  \n"
        "bx r2                              \n"
    );
}

void BusFault_Handler(void)
{
    __asm volatile (
        "tst lr, #4                         \n"
        "ite eq                             \n"
        "mrseq r0, msp                      \n"
        "mrsne r0, psp                      \n"
        "ldr r1, [r0, #24]                  \n"
        "ldr r2, =prvGetRegistersFromStack  \n"
        "bx r2                              \n"
    );
}

void UsageFault_Handler(void)
{
    __asm volatile (
        "tst lr, #4                         \n"
        "ite eq                             \n"
        "mrseq r0, msp                      \n"
        "mrsne r0, psp                      \n"
        "ldr r1, [r0, #24]                  \n"
        "ldr r2, =prvGetRegistersFromStack  \n"
        "bx r2                              \n"
    );
}

void prvGetRegistersFromStack(uint32_t* pulFaultStackAddress)
{
    volatile uint32_t r0  = 0;
    volatile uint32_t r1  = 0;
    volatile uint32_t r2  = 0;
    volatile uint32_t r3  = 0;
    volatile uint32_t r12 = 0;
    volatile uint32_t lr  = 0;
    volatile uint32_t pc  = 0;
    volatile uint32_t psr = 0;

    r0  = pulFaultStackAddress[0];
    r1  = pulFaultStackAddress[1];
    r2  = pulFaultStackAddress[2];
    r3  = pulFaultStackAddress[3];
    r12 = pulFaultStackAddress[4];
    lr  = pulFaultStackAddress[5];
    pc  = pulFaultStackAddress[6];
    psr = pulFaultStackAddress[7];

    printf("r0  : %08X\r\n", r0);
    printf("r1  : %08X\r\n", r1);
    printf("r2  : %08X\r\n", r2);
    printf("r3  : %08X\r\n", r3);
    printf("r12 : %08X\r\n", r12);
    printf("lr  : %08X\r\n", lr);
    printf("pc  : %08X\r\n", pc);
    printf("psr : %08X\r\n", psr);

    // Soft reset
}

void EXTIConfig(void)
{
    /* Cau hinh ngat EXTI1 */
    AFIO->EXTICR1.BITS.EXTI1 = 0x00;
    EXTI->IMR.BITS.MR1 = 0x01;
    EXTI->FTSR.BITS.TR1 = 0x01;
    
    /* Cau hinh ngat NVIC */
    NVIC_EnableIRQ(EXTI1_IRQn);
    NVIC_SetPriority(EXTI1_IRQn, 0X01);
    
    /* Bat ngat toan cuc */
    __ASM("CPSIE I");
}

void USB_LP_CAN1_RX0_IRQHandler(void)
{
    if (USB->ISTR.BITS.RESET != RESET)
    {
        USB_ResetCallBack();
    }
    
    if (USB->ISTR.BITS.CTR != RESET)
    {
        USB_TransactionCallBack();
    }
    
    if (USB->ISTR.BITS.ERR != RESET)
    {
        USB->ISTR.BITS.ERR = 0;
    }
    
    if (USB->ISTR.BITS.SOF != RESET)
    {
        USB->ISTR.BITS.SOF = 0;
    }
    
    if (USB->ISTR.BITS.ESOF != RESET)
    {
        USB->ISTR.BITS.ESOF = 0;
    }
    
    if (USB->ISTR.BITS.SUSP != RESET)
    {
        USB->ISTR.BITS.SUSP = 0;
    }
}
