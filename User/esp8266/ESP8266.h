#ifndef		__ESP8266_H
#define		__ESP8266_H

#include "stm32f10x.h"
#include "stdio.h"
#include <string.h>  

void ESP8266_Set(unsigned char *puf); // 数组指针*puf指向字符串数组 
void SetIP(unsigned char *pReIP);
void SetWifiConnect(void);
void CmdString(unsigned char *ptr);
void SetWifiName(unsigned char *pReName);
void SetNameCode(void);
void SetWifiCode(unsigned char *pReCode);
void ESP8266IO(void);
void ESP8266_Rst( void );


#define Wirst_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define Wirst_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define Wirst_GPIO_PIN		GPIO_Pin_9			        /* 连接到SCL时钟线的GPIO */

#define Wien_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define Wien_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define Wien_GPIO_PIN		GPIO_Pin_8			        /* 连接到SCL时钟线的GPIO */


#define     macESP8266_RST_HIGH_LEVEL()        GPIO_SetBits ( Wien_GPIO_PORT, Wien_GPIO_PIN )
#define     macESP8266_RST_LOW_LEVEL()         GPIO_ResetBits ( Wien_GPIO_PORT, Wien_GPIO_PIN )

typedef union//union只能对第一个变量初始化
{
    struct
    {
			   
			//NAME
			unsigned char NameStr[16];

			//Code
			unsigned char CodeString[16];

			//ip
			unsigned char  Cmdstr[52];
			
    } CfgData;
		u32 SaveArray[30];
}UnionData; 

#endif

