/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTI
  
  AL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "bsp_usart.h"
#include "bsp_SysTick.h"
#include "bsp_adc.h"
#include "bsp_TiMbase.h"
#include "bsp_ds18b20.h"
#include "WifiUsart.h"
#include "bsp_usart_blt.h"
#include <string.h>

extern void TimingDelay_Decrement(void);

extern __IO uint16_t ADC_ConvertedValue;

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	 TimingDelay_Decrement();
}

// 串口中断服务函数
void DEBUG_USART_IRQHandler(void)
{
  uint8_t ucTemp;
	if(USART_GetITStatus(DEBUG_USARTx,USART_IT_RXNE)!=RESET)
	{		
		ucTemp = USART_ReceiveData(DEBUG_USARTx);
    USART_SendData(DEBUG_USARTx,ucTemp);    
	}	 
}

//485中断
// 串口中断服务函数
//bool bRunMotor = false;
void DEBUG_USART3_IRQHandler(void) 
{
  	
	unsigned char data;
  	
	if(USART_GetITStatus(DEBUG_USART3x,USART_IT_RXNE)!=RESET)
	{		
    
			data = USART_ReceiveData(DEBUG_USART3x);
		
    	if(WIFIUART_RxPtr < (WIFIUART_RX_BUFFER_SIZE - 1))
        {
                WIFIUART_RxBuffer[WIFIUART_RxPtr] = data;
                WIFIUART_RxBuffer[WIFIUART_RxPtr + 1]=0x00;
                WIFIUART_RxPtr++;
        }
			else
        {
                WIFIUART_RxBuffer[WIFIUART_RxPtr - 1] = data;
                
        }

        
        #if 1
		if (data == 35)
		{
			WifiUsart_SendString(USART3, (char*)WIFIUART_RxBuffer);
			//WifiUsart_SendString(USART3, (char*)BLTUART_RxBuffer);
		}
		#endif
	}	 
}



// 串口2中断服务函数
void BLT_USART_IRQHandler(void)
{

  unsigned char data;
  if(USART_GetITStatus(BLT_USARTx, USART_IT_RXNE) != RESET)
  {

         data = USART_ReceiveData(BLT_USARTx);
		
    	if(BLTUART_RxPtr < (BLTUART_RX_BUFFER_SIZE - 1))
        {
                BLTUART_RxBuffer[BLTUART_RxPtr] = data;
                BLTUART_RxBuffer[BLTUART_RxPtr + 1]=0x00;
                BLTUART_RxPtr++;
        }
			else
        {
                BLTUART_RxBuffer[BLTUART_RxPtr - 1] = data;
                
        }

        
        #if 1
		if (data == 10)
		{
			//BLTUsart_SendString(USART2, (char*)BLTUART_RxBuffer);
			//WifiUsart_SendString(USART3, (char*)BLTUART_RxBuffer);
			//memset(BLTUART_RxBuffer,0,sizeof(BLTUART_RxBuffer));
		}
		#endif    
  }	
}


//ADC中断数据转换
void ADC_IRQHandler(void)
{	
	if (ADC_GetITStatus(ADCx,ADC_IT_EOC)==SET) 
	{
		//读取ADC数据
		ADC_ConvertedValue = ADC_GetConversionValue(ADCx);
	}
	ADC_ClearITPendingBit(ADCx,ADC_IT_EOC);
}

/**
  * @brief  This function handles TIM2 interrupt request.
  * @param  None
  * @retval None
  */
uint32_t time;
void  BASIC_TIM_IRQHandler (void)
{
	if ( TIM_GetITStatus( BASIC_TIM, TIM_IT_Update) != RESET ) 
	{	
		
		if ( time == 1000 ) /* 1000 * 1 ms = 1s ??? */
        {
            time = 0;
			//printf("\r\n temperature %.1f\r\n",DS18B20_Get_Temp());
		}
		else
		{
			time++;
		}
		TIM_ClearITPendingBit(BASIC_TIM , TIM_FLAG_Update);  		 
	}		 	
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
