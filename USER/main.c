#include "main.h"

#define PRINT(window, fmt, args...) printf("{"#window"}"fmt"\n", ##args)
uint16_t temp1, temp2, temp3, temp4;
float u, i, p;
float power1, power2;
char U[32], I[32], P[32];
int main()
{
    LED_Init();          // LED 初始化
    USART1_Init(115200); // 串口初始化

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); // 中断分组

    RCC_ClocksTypeDef clocks;
    RCC_GetClocksFreq(&clocks);
    printf("SYSCLK: %dMhz, HCLK: %dMhz, PCLK1: %dMhz, PCLK2: %dMhz\r\n",
           clocks.SYSCLK_Frequency / 1000000, clocks.HCLK_Frequency / 1000000,
           clocks.PCLK1_Frequency / 1000000, clocks.PCLK2_Frequency / 1000000);

    delay_init(); // 延时函数初始化

    IIC1_Init();

    IIC2_Init();

    INA226_Init();

    OLED_Init();

    OLED_P8x16Str(0, 0, (uint8_t *)"U:");
    OLED_P8x16Str(0, 3, (uint8_t *)"I:");
    OLED_P8x16Str(0, 6, (uint8_t *)"P:");
    // PWM_Init();
    IWDG_Init(4, 625);
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

    while (1)
    {
               temp2 = INA226_Read2Byte(Shunt_V_Reg);
                temp1 = INA226_Read2Byte(Current_Reg);
               temp3 = INA226_Read2Byte(Power_Reg);
                temp4 = INA226_Read2Byte(Bus_V_Reg);
        if (temp1 > 0x7fff)
        {
            temp1 = (temp1 ^ 0xffff) + 1;
            temp2 = (temp2 ^ 0xffff) + 1;
            i = temp1 * 0.02 * -1;
        }
        else
        {
            i = temp1 * 0.02;
        }
        u = temp4 * 1.25;

        p = temp3 * 0.02 * 25;
        snprintf(U, sizeof(U), "%.2fmV", u);
        snprintf(I, sizeof(I), "%.2fmA", i);
        snprintf(P, sizeof(P), "%.2fmW", p);

        //        OLED_ReShow(0, 2, 24);
        //        OLED_P8x16Str(0, 0, (uint8_t *)"U:");
        //        OLED_PartClear(64, 0, 100, 2);
        OLED_P8x16Str(24, 0, (uint8_t *)U);

        OLED_ReShow(3, 5, 24);
        OLED_P8x16Str(0, 3, (uint8_t *)"I:");
        OLED_P8x16Str(24, 3, (uint8_t *)I);

        OLED_ReShow(6, 8, 24);
        OLED_P8x16Str(0, 6, (uint8_t *)"P:");
        OLED_P8x16Str(24, 6, (uint8_t *)P);

        // LOG(RTT)
//        printf("data=%-5d, Bus_V  =%.2f mV\r\n", temp4, temp4 * 1.25);
//        printf("data=%-5d, Shunt_V=%.2f mV\r\n", temp2, temp2 * 2.5 * 0.001);
//        printf("data=%-5d, Curent =%.2f mA\r\n", temp1, temp1 * 0.02);
//        printf("data=%-5d, Power  =%.2f mW\r\n", temp3, temp3 * 0.02 * 25);

//        power1 += temp3 * 0.02 * 25 / 1000 / 3600;
//        power2 += temp2 * 2.5 * 0.001 / 100 / 3600;
//        printf("%fmWh\r\n", power1);
//        printf("%fmAh\r\n", power2);
        PRINT(plotter, "%.2f, %.2f, %.2f",temp4 * 1.25, temp1 * 0.02, temp3 * 0.02 * 25);
        delay_ms(500);
        // GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1 ? LED(0) : LED(1);
//        temp1 = temp2 = temp3 = temp4++;
        // GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1 ? PWM1(0) : PWM1(1);
        // GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_14) == 1 ? PWM2(0) : PWM2(1);
        // delay_us(100);
        IWDG_FreeDog();
    }
}