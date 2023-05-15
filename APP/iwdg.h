#ifndef __IWDG_H
#define __IWDG_H

#include "stm32f10x.h"

void IWDG_Init(uint8_t per, uint16_t rlr);
void IWDG_FreeDog(void);

#endif // !__IWDG_H
