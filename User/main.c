/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   串口中断接收测试
  ******************************************************************************
  * @attention
  *
  * 实验平台:秉火 F103-指南者 STM32 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
 
 
#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "setio.h"
#include "bsp_adc.h"
#include "bsp_ds18b20.h"
#include "bsp_TiMbase.h"
#include <string.h>
#include <math.h>
#include "WifiUsart.h"
#include "bsp_usart_blt.h"

extern __IO uint16_t ADC_ConvertedValue;

extern uint32_t time;
// 局部变量，保存ADC的值
float ADC_ConvertedValueLocal;  
double temp[500] = {0};

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */


int adctimes = 0;	
double deltADC = 0;
double sum = 0;

int main(void)
{	
  	
	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
    USART_Config();

    WifiUSART_Config();

    BLT_USART_Config();
	
	SysTick_Init();
	
	SETIO_GPIO_Config();
	
	
	
	while( DS18B20_Init())	
	{
		//printf("\r\n no ds18b20 exit \r\n");
	}	
	printf("\r\n ds18b20 exit \r\n");
	
	// ADC初始化
	ADCx_Init();
  //BASIC_TIM_Init();
	
	/* 发送一个字符串 */
	printf("微温脉动仪\n\n\n\n");
	
    while(1)
	{			 
		  		 		
		  CloseADC();
		  printf("temperature = %f ℃\r\n",DS18B20_Get_Temp());

		  WifiUsart_SendString(USART3, "it is ok!\n");
		  BLTUsart_SendString(USART2, "BLT it is ok!\n");
					
		  OpenADC();
		  for (adctimes = 0;adctimes <500; adctimes++)
		  {
			  ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3;
		      temp[adctimes] = ADC_ConvertedValueLocal*ADC_ConvertedValueLocal*ADC_ConvertedValueLocal*ADC_ConvertedValueLocal;
				Delay_ms(10);
		  }
		 
		 for (adctimes = 0;adctimes < 500; adctimes++)
		 {
		    sum = sum + temp[adctimes];
		 }
		 
		  deltADC = sqrt(sum/500);
		 
		  printf("deltADC = %f V\r\n",deltADC);
		  printf("ADC_ConvertedValueLocal = %f V\r\n",ADC_ConvertedValueLocal);
		 
		  memset(temp,0,sizeof(temp));
				 
	}	
}
/*********************************************END OF FILE**********************/
