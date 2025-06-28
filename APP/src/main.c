#include "main.h"

int main(void)
{
    init();
    
    while (1)
    {
        loop();
    }
}

void init(void)
{
    setupHardware();
    SystickConfig(71999);
    TraceInit();
    TestLed();
}

void loop(void)
{
    GPIOC->ODR.BITS.ODR13 = !GPIOC->ODR.BITS.ODR13;
    DEBUG(LOG_WARN, "LOOP", "Nguyen %d", 28);
    delay(1000);
}

void SystickConfig(uint32_t u32Reload)
{
    /* Cau hinh systick */
    SysTick->VAL = u32Reload;
    SysTick->LOAD = u32Reload;
    SysTick->CTRL = BIT2 | BIT1 | BIT0;
}
