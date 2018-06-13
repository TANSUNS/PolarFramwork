#ifndef __PERRIPHDEF_H__
#define __PERRIPHDEF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
	 

#define GPIOA_SET                    1
#define GPIOB_SET                    2
#define GPIOC_SET                    3
#define GPIOD_SET                    4
#define GPIOE_SET                    5
#define GPIOF_SET                    6
#define GPIOG_SET                    7

	 
#define pin0                         0
#define pin1                         1
#define pin2                         2
#define pin3                         3
#define pin4                         4
#define pin5                         5
#define pin6                         6
#define pin7                         7
#define pin8                         8
#define pin9                         9
#define pin10                       10
#define pin11                       11
#define pin12                       12
#define pin13                       13
#define pin14                       14
#define pin15                       15
#define pin16                       16

#define Pin0                         GPIO_Pin_0
#define Pin1                         GPIO_Pin_1
#define Pin2                         GPIO_Pin_2
#define Pin3                         GPIO_Pin_3
#define Pin4                         GPIO_Pin_4
#define Pin5                         GPIO_Pin_5
#define Pin6                         GPIO_Pin_6
#define Pin7                         GPIO_Pin_7
#define Pin8                         GPIO_Pin_8
#define Pin9                         GPIO_Pin_9
#define Pin10                        GPIO_Pin_10
#define Pin11                        GPIO_Pin_11
#define Pin12                        GPIO_Pin_12
#define Pin13                        GPIO_Pin_13
#define Pin14                        GPIO_Pin_14
#define Pin15                        GPIO_Pin_15



#define LOW_Speed                    2
#define MID_Speed                   10
#define HIGH_Speed                  50


#define High                         1
#define Low                          0


#define UART0_SET                    0
#define UART1_SET                    1
#define UART2_SET                    2
#define UART3_SET                    3
#define UART4_SET                    4
#define UART5_SET                    5


/*Systick Define*/
#define Set_ENABLE                   1
#define Set_DISABLE                  0


/*Basic TIM*/
#define BASIC_TIM_6                  6
#define BASIC_TIM_7                  7
#define BASIC_TIM_6_CLK              RCC_APB1Periph_TIM6
#define BASIC_TIM_7_CLK              RCC_APB1Periph_TIM7
#define BASIC_TIM_6_IRQ              TIM6_IRQn
#define BASIC_TIM_7_IRQ              TIM7_IRQn
#define BASIC_TIM_6_IRQHandler       TIM6_IRQHandler
#define BASIC_TIM_7_IRQHandler       TIM7_IRQHandler


/*General TIM*/
#define GENERAL_TIM_2                2
#define GENERAL_TIM_3                3
#define GENERAL_TIM_4                4
#define GENERAL_TIM_5                5

#define TIM_Mode_Up                  1
#define TIM_Mode_Down                2

/*****FTM*******/

#define FTM0                         0

#define FTM0_CH1                     1
#define FTM0_CH2                     2
#define FTM0_CH3                     3
#define FTM0_CH4                     4

#define FTM1                         1

#define FTM1_CH1                     1
#define FTM1_CH2                     2
#define FTM1_CH3                     3
#define FTM1_CH4                     4

#define FTM2                         2

#define FTM2_CH1                     1
#define FTM2_CH2                     2
#define FTM2_CH3                     3
#define FTM2_CH4                     4

#define FTM3                         3

#define FTM3_CH1                     1
#define FTM3_CH2                     2
#define FTM3_CH3                     3
#define FTM3_CH4                     4


#define            GENERAL_TIM_Prescaler         71

/**********************************/
typedef struct  
{
	char GPIO_PORT;       //多신Port데뗌땍屢
	uint16_t GPIO_PIN;    //多신Pin
	GPIOSpeed_TypeDef GPIO_Speed;  //多신醵똑
	GPIOMode_TypeDef GPIO_Mode;  //多신친駕
	
}GPIO_CFG;


#endif
#endif