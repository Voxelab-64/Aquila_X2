#ifndef __I2C_EEPROM_H
#define __I2C_EEPROM_H

#include "../../inc/MarlinConfig.h"
#include "../../MarlinCore.h"


/******************** EEPROM ********************/
#define BL24C01		127
#define BL24C02		255
#define BL24C04		511
#define BL24C08		1023
#define BL24C16		2047
#define BL24C32		4095
#define BL24C64	  8191
#define BL24C128	16383
#define BL24C256	32767  
#define EE_TYPE   BL24C16
					  
uint8_t BL24CXX_ReadOneByte(uint16_t ReadAddr);							          //指定地址读取一个字节
void BL24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite);		//指定地址写入一个字节
void BL24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len);//指定地址开始写入指定长度的数据
uint32_t BL24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len);					//指定地址开始读取指定长度数据
void BL24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite);	//从指定地址开始写入指定长度的数据
void BL24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead);   	//从指定地址开始读出指定长度的数据

uint8_t BL24CXX_Check(void);  //检查器件
void BL24CXX_Init(void); //初始化IIC


#endif

