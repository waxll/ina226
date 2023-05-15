#ifndef __INA226_H
#define __INA226_H
#include "sys.h"

#define READ_ADDR                  0x81	 //A0=GND，A1=GND // R=1, W=0
#define WRITE_ADDR                 0x80

#define Config_Reg                 0x00
#define Shunt_V_Reg                0x01
#define Bus_V_Reg                  0x02
#define Power_Reg                  0x03
#define Current_Reg                0x04
#define Calib_Reg                  0x05
#define Mask_En_Reg                0x06
#define Alert_Reg                  0x07
#define Man_ID_Reg                 0xFE  //0x5449
#define ID_Reg                     0xFF  //0x2260

u16 INA226_Read2Byte(u8 reg_addr);
u8 INA226_Write2Byte(u8 reg_addr,u16 reg_data);
void INA226_Init(void);

#endif
