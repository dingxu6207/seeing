#ifndef    __WRFLASH_H
#define    __WRFLASH_H


#include "stm32f10x.h"

#define WriteFlashAddress    ((u32)0x0800FC00)//存储到最后一页，地址范围：0x0800 FC00~0x0800 FFFF

void Read_Flash(u32 *buff, u8 len);
u8 Write_Flash(u32 *buff, u8 len);

#endif
