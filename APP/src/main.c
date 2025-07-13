#include "main.h"

void ram_test(void)
{
    GPIOC->ODR.BITS.ODR13 = !GPIOC->ODR.BITS.ODR13;
    DEBUG(LOG_WARN, __FUNCTION__, "Nguyen %d", 28);
    delay(1000);
}

int main(void)
{
    init();
    
    while (1)
    {
        ram_test();
    }
}

void init(void)
{
    setupHardware();
    SystickConfig(71999);
    TraceInit();
    TestLed();
    DEBUG(LOG_WARN, __FUNCTION__, "Address: %08X", ram_test);
}

void loop(void)
{
    
}

void SystickConfig(uint32_t u32Reload)
{
    /* Cau hinh systick */
    SysTick->VAL = u32Reload;
    SysTick->LOAD = u32Reload;
    SysTick->CTRL = BIT2 | BIT1 | BIT0;
}
