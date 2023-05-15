#include "uart.h"

void USART1_Init(uint32_t BaudRate)
{
    RCC_APB2PeriphClockCmd(RCC_APB2ENR_USART1EN, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = BaudRate;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &USART_InitStructure);
    USART_Cmd(USART1, ENABLE);
    // USART_ClearFlag(USART1, USART_FLAG_TC);
    // USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

void USART1_IRQHandler(void)
{
    //    uint8_t Res;
    if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        USART_ReceiveData(USART1);
        //      Res = USART_ReceiveData(USART1);
    }
}

#if 1
#include "stdio.h"
#include "SEGGER_RTT.h"
#ifdef __CC_ARM
#pragma import(__use_no_semihosting)
#elif defined(__GUN) || defined(__clang__)
__asm(".global __use_no_semihosting\n\t");
#endif
struct __FILE
{
    int handle;
};

FILE __stdout;

void _sys_exit(int x)
{
    x = x;
}
int fputc(int ch, FILE *f)
{
#ifdef RTT_OUT
    SEGGER_RTT_PutChar(0, ch);
#elif UART_OUT
    while ((USART1->SR & 0x40) == 0)
        ;
    USART1->DR = (u8)ch;
#elif SWO_OUT
    ITM_SendChar(ch);
#endif
    return ch;
}
#ifdef SWO_OUT
void TIM_Init(void)
{
    DBGMCU->CR = 0x27;     // 使能TRACE的引脚
    ITM->LAR = 0xC5ACCE55; // 允许写其他ITM寄存器
    ITM->TCR = 0x00010005; // 使能TPIU的同步包并使能整个ITM功能
    ITM->TER = 0x01;       // 以使能触发端口0
    ITM->TPR = 0x01;       // 关闭对触发端口7:0的屏蔽
}
#endif
#endif
