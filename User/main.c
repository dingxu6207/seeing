/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����жϽ��ղ���
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:���� F103-ָ���� STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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
#include <stdio.h>

extern __IO uint16_t ADC_ConvertedValue;

extern uint32_t time;
// �ֲ�����������ADC��ֵ
float ADC_ConvertedValueLocal;  
double temp[500] = {0};

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */


int adctimes = 0;	
double deltADC = 0;
double sum = 0;
char *Pressure = NULL;
char Pre[20] = {0};
char Hig[20] = {0};
char cTempterStr[20] = {0};
char cdeltADCStr[20] = {0};
char cADC_ConvertedValueLocalstr[50] = {0};
int main(void)
{	
  	
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1���жϽ���*/
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
	
	// ADC��ʼ��
	ADCx_Init();
  //BASIC_TIM_Init();
	
	/* ����һ���ַ��� */
	printf("΢��������\n\n\n\n");
	
    while(1)
	{			 
		  		 		
		  CloseADC();
		  printf("temperature = %f ��\r\n",DS18B20_Get_Temp());
      sprintf(cTempterStr, "temperature = %f ��\n", DS18B20_Get_Temp());
		 	WifiUsart_SendString(USART3, (char*)cTempterStr);
		
		#if 1
		 Pressure = strstr((char*)BLTUART_RxBuffer, "Pre"); 
     strncpy(Pre, Pressure, 19);
		 strncpy(Hig, Pressure+20, 17);
		 WifiUsart_SendString(USART3, (char*)Pre); 
		 WifiUsart_SendByte(USART3, '\n');
     WifiUsart_SendString(USART3, (char*)Hig);
     WifiUsart_SendByte(USART3, '\n');		
     printf("%s\n", Pre);
		 printf("%s\n", Hig);
		
		//memset(BLTUART_RxBuffer,0,sizeof(BLTUART_RxBuffer));
		#endif
		
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
		 
		  sprintf(cdeltADCStr, "deltADC = %f \n", deltADC);
		 	WifiUsart_SendString(USART3, (char*)cdeltADCStr);
		 
		  sprintf(cADC_ConvertedValueLocalstr, "ADC_ConvertedValueLocal = %f \n", ADC_ConvertedValueLocal);
		 	WifiUsart_SendString(USART3, (char*)cADC_ConvertedValueLocalstr);
		  
		  //WifiUsart_SendString(USART3, "\r\n");
		  printf("\r\n");
		 
		  memset(temp,0,sizeof(temp));
				 
	}	
}
/*********************************************END OF FILE**********************/
