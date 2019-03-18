/*
  ******************************************************************************
  * @file    bsp_led.c
  * @author  dingxu
  * @version V1.0
  * @date    2018-xx-xx
  * @brief   Flashº¯Êý½Ó¿Ú
  ******************************************************************************
  */

#include "WRFlash.h"


void Read_Flash(u32 *buff, u8 len)
{
	u32 Address = WriteFlashAddress;
	u8 k;
	for(k=0;k<len;k++)
	{
		buff[k] =  (*(vu32*) Address);
		Address += 4;     
	}
}

u8 Write_Flash(u32 *buff, u8 len)
{    
	volatile FLASH_Status FLASHStatus;
	u32 Address = WriteFlashAddress;
	FLASHStatus = FLASH_COMPLETE;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
	FLASHStatus = FLASH_ErasePage(WriteFlashAddress);
	if(FLASHStatus == FLASH_COMPLETE)
	{
		u8 k;
		for(k=0;(k<len) && (FLASHStatus == FLASH_COMPLETE);k++)
		{
				FLASHStatus = FLASH_ProgramWord(Address, buff[k]);
				Address = Address + 4;
		}        
		FLASH_Lock();
	}
	else
	{
		return 0;
	}
	if(FLASHStatus == FLASH_COMPLETE)
	{
		return 1;
	}
	return 0;
}



