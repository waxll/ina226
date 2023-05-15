#ifndef __MYIIC_H
#define __MYIIC_H

#include "sys.h"
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

//IO方向设置

#define SDA1_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA1_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

#define SDA2_IN()  {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)8<<28;}
#define SDA2_OUT() {GPIOA->CRL&=0X0FFFFFFF;GPIOA->CRL|=(u32)3<<28;}

//IO操作函数
#define IIC1_SCL    PBout(6) //SCL
#define IIC1_SDA    PBout(7) //SDA
#define READ1_SDA   PBin(7)  //输入SDA

#define IIC2_SCL    PAout(6) //SCL
#define IIC2_SDA    PAout(7) //SDA
#define READ2_SDA   PAin(7)  //输入SDA

//IIC所有操作函数
void IIC1_Init(void);                //初始化IIC的IO口
void IIC1_Start(void);				//发送IIC开始信号
void IIC1_Stop(void);	  			//发送IIC停止信号
void IIC1_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC1_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC1_Wait_Ack(void); 				//IIC等待ACK信号
void IIC1_Ack(void);					//IIC发送ACK信号
void IIC1_NAck(void);				//IIC不发送ACK信号

void IIC2_Init(void);                //初始化IIC的IO口
void IIC2_Start(void);				//发送IIC开始信号
void IIC2_Stop(void);	  			//发送IIC停止信号
void IIC2_Send_Byte(u8 txd);			//IIC发送一个字节
void IIC2_Wait_Ack(void); 				//IIC等待ACK信号

#endif
















