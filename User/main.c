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

extern __IO uint16_t ADC_ConvertedValue;

extern uint32_t time;
// 局部变量，保存ADC的值
float ADC_ConvertedValueLocal;   

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */

int main(void)
{	
  	
	/*初始化USART 配置模式为 115200 8-N-1，中断接收*/
  USART_Config();
	
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
					
			OpenADC();
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3;
			printf("AD value = %f V\r\n",ADC_ConvertedValueLocal);
		
		 Delay_ms(1000);
		 
	}	
}
/*********************************************END OF FILE**********************/
