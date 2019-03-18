#ifndef __SETIO_H
#define	__SETIO_H

#include "stm32f10x.h"

void SETIO_GPIO_Config(void);

// swich
#define SWITCH_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define SWITCH_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define SWITCH_GPIO_PIN		    GPIO_Pin_0			        /* 连接到SCL时钟线的GPIO */

// led
#define LED_GPIO_PORT    	GPIOB			              /* GPIO端口 */
#define LED_GPIO_CLK 	    RCC_APB2Periph_GPIOB		/* GPIO端口时钟 */
#define LED_GPIO_PIN		GPIO_Pin_1			        /* 连接到SCL时钟线的GPIO */

#endif

