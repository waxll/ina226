#include "myiic.h"
#include "delay.h"
#include "stdio.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//IIC驱动 代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//初始化IIC1
void IIC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
}
//产生IIC起始信号
void IIC1_Start(void)
{
	SDA1_OUT();     //sda线输出
	IIC1_SDA=1;
	IIC1_SCL=1;
	delay_us(4);
 	IIC1_SDA=0;//START:when CLK is high,DATA change form high to low
	delay_us(4);
	IIC1_SCL=0;//钳住I2C总线，准备发送或接收数据
}
//产生IIC停止信号
void IIC1_Stop(void)
{
	SDA1_OUT();//sda线输出
	IIC1_SCL=0;
	IIC1_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC1_SCL=1;
	IIC1_SDA=1;//发送I2C总线结束信号
	delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC1_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA1_IN();      //SDA设置为输入
	IIC1_SDA=1;delay_us(1);
	IIC1_SCL=1;delay_us(1);
	while(READ1_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC1_Stop();
			return 1;
		}
	}
	IIC1_SCL=0;//时钟输出0
	return 0;
}
//产生ACK应答
void IIC1_Ack(void)
{
	IIC1_SCL=0;
	SDA1_OUT();
	IIC1_SDA=0;
	delay_us(2);
	IIC1_SCL=1;
	delay_us(2);
	IIC1_SCL=0;
}
//不产生ACK应答
void IIC1_NAck(void)
{
	IIC1_SCL=0;
	SDA1_OUT();
	IIC1_SDA=1;
	delay_us(2);
	IIC1_SCL=1;
	delay_us(2);
	IIC1_SCL=0;
}
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答
void IIC1_Send_Byte(u8 txd)
{
    u8 t;
	SDA1_OUT();
    IIC1_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC1_SDA=1;
		else
			IIC1_SDA=0;
		txd<<=1;
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC1_SCL=1;
		delay_us(2);
		IIC1_SCL=0;
		delay_us(2);
    }
}
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
u8 IIC1_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA1_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC1_SCL=0;
        delay_us(2);
		IIC1_SCL=1;
        receive<<=1;
        if(READ1_SDA)receive++;
		delay_us(1);
    }
    if (!ack)
        IIC1_NAck();//发送nACK
    else
        IIC1_Ack(); //发送ACK
    return receive;
}

void IIC_delay(void)
{
	u8 t=3;
	while(t--);
}


//初始化IIC2
void IIC2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );	//使能GPIOB时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
}

//产生IIC起始信号
void IIC2_Start(void)
{
	IIC2_SDA=1;
	IIC2_SCL=1;
	IIC_delay();
 	IIC2_SDA=0;//START:when CLK is high,DATA change form high to low
	IIC_delay();
	IIC2_SCL=0;//钳住I2C总线，准备发送或接收数据 ]
    IIC_delay();
}

//产生IIC停止信号
void IIC2_Stop(void)
{
	IIC2_SCL=0;
	IIC2_SDA=0;//STOP:when CLK is high DATA change form low to high
 	IIC_delay();
	IIC2_SDA=1;//发送I2C总线结束信号
}

//等待应答信号
void IIC2_Wait_Ack(void) //测数据信号的电平
{
	IIC2_SDA=1;
	IIC_delay();
	IIC2_SCL=1;
	IIC_delay();
	IIC2_SCL=0;
	IIC_delay();
}

//IIC发送一个字节数据
void IIC2_Send_Byte(u8 txd)
{
    u8 t;
    for(t=0;t<8;t++)
    {
		if(txd&0x80)
			IIC2_SDA=1;
		else
			IIC2_SDA=0;
        IIC_delay();
        IIC2_SCL=1;
        IIC_delay();
        IIC2_SCL=0;
		txd<<=1;
    }
}
