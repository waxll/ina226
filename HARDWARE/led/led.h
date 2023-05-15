#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

void LED_Init(void);
void PWM_Init(void);
#define LED(x) x == 1 ? GPIO_SetBits(GPIOC, GPIO_Pin_13) : GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define PWM1(x) x == 1 ? GPIO_SetBits(GPIOC, GPIO_Pin_13) : GPIO_ResetBits(GPIOC, GPIO_Pin_13)
#define PWM2(x) x == 1 ? GPIO_SetBits(GPIOC, GPIO_Pin_14) : GPIO_ResetBits(GPIOC, GPIO_Pin_14)
#endif //!__LED_H

