#include "oled.h"
#include "myiic.h"
#include "delay.h"
#include "codetab.h"

uint8_t OLED_GRAM[128][64];

//更新显存到OLED
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
		OLED_WrCmd(0xb0); //设置行起始地址
		OLED_WrCmd(0x00);   //设置低列起始地址
		OLED_WrCmd(0x10);   //设置高列起始地址
		IIC2_Start();
		IIC2_Send_Byte(0x78);
		IIC2_Send_Byte(0x40);
		for(n=0;n<128;n++)
		{
			IIC2_Send_Byte(OLED_GRAM[n][i]);
		}
		IIC2_Stop();
  }
}
void OLED_PartClear(u8 x0,u8 y0,u8 x1,u8 y1)
{
	u8 i,n;
    for( i=x0;i<x1;i++)
    {
        for( n=y0;n<y1;n++)
        {
            OLED_GRAM[i][n]=0;
        }
    }
    OLED_Refresh();
}

void OLED_WrDat(uint8_t dat)
{
    IIC2_Start();
    IIC2_Send_Byte(0x78);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x40);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(dat);
    IIC2_Wait_Ack();
    IIC2_Stop();
}

void OLED_WrCmd(uint8_t cmd)
{
    IIC2_Start();
    IIC2_Send_Byte(0x78);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(0x00);
    IIC2_Wait_Ack();
    IIC2_Send_Byte(cmd);
    IIC2_Wait_Ack();
    IIC2_Stop();
}

void OLED_Set_Pos(uint8_t x, uint8_t y)
{
    OLED_WrCmd(0xb0 + y);
    OLED_WrCmd(((x & 0xf0) >> 4) | 0x10);
    OLED_WrCmd((x & 0x0f) | 0x01);
}

void OLED_Fill(uint8_t bmp_dat)
{
    uint8_t x, y;
    for (y = 0; y < 8; y++)
    {
        OLED_WrCmd(0xb0 + y);
        OLED_WrCmd(0x00);
        OLED_WrCmd(0x10);
        for (x = 0; x < X_WIDTH; x++)
            OLED_WrDat(bmp_dat);
    }
}

void OLED_CLS(void)
{
    uint8_t x, y;
    for (y = 0; y < 8; y++)
    {
        OLED_WrCmd(0xb0 + y);
        OLED_WrCmd(0x00);
        OLED_WrCmd(0x10);
        for (x = 0; x < X_WIDTH; x++)
            OLED_WrDat(0);
    }
}

void OLED_ReShow(uint8_t l, uint8_t h, uint8_t x)
{
    for(uint8_t i = l; i<h; i++)
    {
        OLED_WrCmd(0xb0 + i);
        OLED_WrCmd(0x01);
        OLED_WrCmd(0x10);
        for (uint8_t w = x; w < X_WIDTH; w++)
            OLED_WrDat(0);
    }
}


void OLED_OFF(void)
{
    OLED_WrCmd(0X8D); // 设置电荷泵
    OLED_WrCmd(0X10); // 关闭电荷泵
    OLED_WrCmd(0XAE); // OLED休眠
}

void OLED_ON(void)
{
    OLED_WrCmd(0X8D); // 设置电荷泵
    OLED_WrCmd(0X14); // 开启电荷泵
    OLED_WrCmd(0XAF); // OLED唤醒
}

void OLED_Init(void)
{
    delay_ms(50);
    OLED_WrCmd(0xae);       //--turn off oled panel
    OLED_WrCmd(0x00);       //---set low column address
    OLED_WrCmd(0x10);       //---set high column address
    OLED_WrCmd(0x40);       //--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
    OLED_WrCmd(0x81);       //--set contrast control register
    OLED_WrCmd(Brightness); // Set SEG Output Current Brightness 亮度调节 0x00~0xff
    OLED_WrCmd(0xa0);       //--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
    OLED_WrCmd(0xc0);       // Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
    OLED_WrCmd(0xa6);       //--set normal display
    OLED_WrCmd(0xa8);       //--set multiplex ratio(1 to 64)
    OLED_WrCmd(0x3f);       //--1/64 duty
    OLED_WrCmd(0xd3);       //-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
    OLED_WrCmd(0x00);       //-not offset
    OLED_WrCmd(0xd5);       //--set display clock divide ratio/oscillator frequency
    OLED_WrCmd(0x80);       //--set divide ratio, Set Clock as 100 Frames/Sec
    OLED_WrCmd(0xd9);       //--set pre-charge period
    OLED_WrCmd(0xf1);       // Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
    OLED_WrCmd(0xda);       //--set com pins hardware configuration
    OLED_WrCmd(0x12);
    OLED_WrCmd(0xdb); //--set vcomh
    OLED_WrCmd(0x40); // Set VCOM Deselect Level
    OLED_WrCmd(0x20); //-Set Page Addressing Mode (0x00/0x01/0x02)
    OLED_WrCmd(0x02); //
    OLED_WrCmd(0x8d); //--set Charge Pump enable/disable
    OLED_WrCmd(0x14); //--set(0x10) disable
    OLED_WrCmd(0xa4); // Disable Entire Display On (0xa4/0xa5)
    OLED_WrCmd(0xa6); // Disable Inverse Display On (0xa6/a7)
    OLED_WrCmd(0xaf); //--turn on oled panel
    OLED_CLS();       // 初始清屏
    OLED_Set_Pos(0, 0);
}

// m^n函数
uint32_t oled_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;
    while (n--)
        result *= m;
    return result;
}
// 显示2个数字
// x,y :起点坐标
// len :数字的位数
// size:字体大小
// mode:模式	0,填充模式;1,叠加模式
// num:数值(0~4294967295);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size)
{
    uint8_t t, temp;
    uint8_t enshow = 0;
    for (t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t - 1)) % 10;
        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                OLED_ShowChar(x + (size / 2) * t, y, ' ');
                continue;
            }
            else
                enshow = 1;
        }
        OLED_ShowChar(x + (size / 2) * t, y, temp + '0');
    }
}
// 在指定位置显示一个字符,包括部分字符
// x:0~127
// y:0~63
// mode:0,反白显示;1,正常显示
// size:选择字体 16/12
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr)
{
    uint8_t c = 0, i = 0;
    c = chr - ' '; // 得到偏移后的值
    if (x > Max_Column - 1)
    {
        x = 0;
        y = y + 2;
    }
    if (SIZE == 0)
    {
        OLED_Set_Pos(x, y);
        for (i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i]);
        OLED_Set_Pos(x, y + 1);
        for (i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i + 8]);
    }
    else
    {
        OLED_Set_Pos(x, y + 1);
        for (i = 0; i < 6; i++)
            OLED_WrDat(F6x8[c][i]);
    }
}
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void OLED_P6x8Str(uint8_t x, uint8_t y, uint8_t ch[])
{
    uint8_t c = 0, i = 0, j = 0;
    while (ch[j] != '\0')
    {
        c = ch[j] - 32;
        if (x > 126)
        {
            x = 0;
            y++;
        }
        OLED_Set_Pos(x, y);
        for (i = 0; i < 6; i++)
            OLED_WrDat(F6x8[c][i]);
        x += 6;
        j++;
    }
}

/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
void OLED_P8x16Str(uint8_t x, uint8_t y, uint8_t ch[])
{
    uint8_t c = 0, i = 0, j = 0;
    while (ch[j] != '\0')
    {
        c = ch[j] - 32;
        if (x > 120)
        {
            x = 0;
            y++;
        }
        OLED_Set_Pos(x, y);
        for (i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i]);
        OLED_Set_Pos(x, y + 1);
        for (i = 0; i < 8; i++)
            OLED_WrDat(F8X16[c * 16 + i + 8]);
        x += 8;
        j++;
    }
}

//--------------------------------------------------------------
// Prototype      : OLED_P16x16Ch(uint8_t x, uint8_t y, uint8_t N)
// Calls          :
// Parameters     : x,y -- 起始点坐标(x:0~127, y:0~7); N:汉字在codetab.h中的索引
// Description    : 显示codetab.h中的汉字,16*16点阵
//--------------------------------------------------------------

/*****************功能描述：显示16*16点阵  显示的坐标（x,y），y为页范围0～7****************************/
void OLED_P16x16Ch(uint8_t x, uint8_t y, uint32_t N)
{
    uint8_t wm = 0;
    uint32_t adder = 32 * N;
    OLED_Set_Pos(x, y);
    for (wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x16[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x16[adder]);
        adder += 1;
    }
}
void OLED_P16x32Ch(uint8_t x, uint8_t y, uint32_t N)
{
    uint8_t wm = 0;
    uint32_t adder = 64 * N;
    OLED_Set_Pos(x, y);
    for (wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 2);
    for (wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3);
    for (wm = 0; wm < 16; wm++)
    {
        OLED_WrDat(F16x32[adder]);
        adder += 1;
    }
}
void OLED_P32x32Ch(uint8_t x, uint8_t y, uint32_t N)
{
    uint8_t wm = 0;
    uint32_t adder = 128 * N;
    OLED_Set_Pos(x, y);
    for (wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 2);
    for (wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3);
    for (wm = 0; wm < 32; wm++)
    {
        OLED_WrDat(F32x32[adder]);
        adder += 1;
    }
}
void OLED_P128x48Ch(uint8_t x, uint8_t y, uint32_t N)
{
    uint8_t wm = 0;
    uint32_t adder = 768 * N;
    OLED_Set_Pos(x, y);
    for (wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 1);
    for (wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 2);
    for (wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 3);
    for (wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 4);
    for (wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
    OLED_Set_Pos(x, y + 5);
    for (wm = 0; wm < 128; wm++)
    {
        OLED_WrDat(F128x48[adder]);
        adder += 1;
    }
}
