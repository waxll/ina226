#include "iwdg.h"
#include "led.h"

void IWDG_Init(uint8_t per, uint16_t rlr)
{
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
    IWDG_SetPrescaler(per);
    IWDG_SetReload(rlr);
    IWDG_ReloadCounter();
    DBGMCU_Config(DBGMCU_IWDG_STOP, ENABLE);
    IWDG_Enable();
}

void IWDG_FreeDog(void)
{
    IWDG_ReloadCounter();
    GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1 ? LED(0) : LED(1);
}
