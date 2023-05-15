#include "ina226.h"
#include "myiic.h"
#include "delay.h"

u16 INA226_Read2Byte(u8 reg_addr)
{
  u16 reg_data=0;
  u16 temp=0;
  IIC1_Start();
  IIC1_Send_Byte(WRITE_ADDR);
  if(IIC1_Wait_Ack())return 0;
  IIC1_Send_Byte(reg_addr);
  if(IIC1_Wait_Ack())return 0;
  IIC1_Start();
  IIC1_Send_Byte(READ_ADDR);
  if(IIC1_Wait_Ack())return 0;
  reg_data= IIC1_Read_Byte(1);
  reg_data=(reg_data<<8)&0xFF00;
  temp=IIC1_Read_Byte(0);
  IIC1_Stop();
  reg_data|=temp;
  return reg_data;
}

u8 INA226_Write2Byte(u8 reg_addr,u16 reg_data)
{
  u8 data_high=(u8)((reg_data&0xFF00)>>8);
  u8 data_low=(u8)reg_data&0x00FF;
  IIC1_Start();
  IIC1_Send_Byte(WRITE_ADDR);
  if(IIC1_Wait_Ack())return 0;
  IIC1_Send_Byte(reg_addr );
  if(IIC1_Wait_Ack())return 0;
  IIC1_Send_Byte(data_high);
  if(IIC1_Wait_Ack())return 0;
  IIC1_Send_Byte(data_low);
  if(IIC1_Wait_Ack())return 0;
  IIC1_Stop();
  delay_ms(2);
  return 1;
}

void INA226_Init(void)
{
  INA226_Write2Byte(Config_Reg, 0x4527);//0100_010_100_100_111 //16次平均,1.1ms,1.1ms,连续测量分流电压和总线电压
  INA226_Write2Byte(Calib_Reg, 0x0A00);
}
