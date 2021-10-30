#include "i2c_eeprom.h"
#include <stdlib.h>

#include "../../inc/MarlinConfigPre.h"
#include "../../MarlinCore.h"

/******************** EEPROM ********************/

//初始化IIC接口
void BL24CXX_Init(void)
{
	if(BL24CXX_Check()) // no found I2C_EEPROM
		SERIAL_ECHO_MSG("I2C_EEPROM Check Failed!");
	else
		SERIAL_ECHO_MSG("I2C_EEPROM Check Successed!");      
}

//在BL24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
uint8_t BL24CXX_ReadOneByte(uint16_t ReadAddr)
{				  
	return ReadOneByteData(ReadAddr);
}

//在BL24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void BL24CXX_WriteOneByte(uint16_t WriteAddr,uint8_t DataToWrite)
{				   	  	    																 
	WriteOneByteData(WriteAddr,DataToWrite);
	delay(2);
}

//在BL24CXX里面的指定地址开始写入长度为Len的数据
//该函数用于写入16bit或者32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
//Len        :要写入数据的长度2,4
void BL24CXX_WriteLenByte(uint16_t WriteAddr,uint32_t DataToWrite,uint8_t Len)
{  	
	uint8_t t;
	for(t=0;t<Len;t++)
	{
		BL24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}
	delay(10);
}

//在BL24CXX里面的指定地址开始读出长度为Len的数据
//该函数用于读出16bit或者32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
//Len        :要读出数据的长度2,4
uint32_t BL24CXX_ReadLenByte(uint16_t ReadAddr,uint8_t Len)
{  	
	uint8_t t;
	uint32_t temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=BL24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查BL24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
uint8_t BL24CXX_Check(void)
{
	uint8_t temp;
	temp=BL24CXX_ReadOneByte(255);//避免每次开机都写BL24CXX			   
	if(temp==0X55)return 0;		   
	else//排除第一次初始化的情况
	{
		BL24CXX_WriteOneByte(255,0X55);
    		temp=BL24CXX_ReadOneByte(255);	  
		if(temp==0X55)
		return 0;
	}
	return 1;											  
}

#if 0
//在BL24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 对24c02为0~255
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void BL24CXX_Read(uint16_t ReadAddr,uint8_t *pBuffer,uint16_t NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=BL24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  

//在BL24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 对24c02为0~255
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void BL24CXX_Write(uint16_t WriteAddr,uint8_t *pBuffer,uint16_t NumToWrite)
{
	while(NumToWrite--)
	{
		BL24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
	delay(10);
}
#endif
