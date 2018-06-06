#include <stm32f10x.h>
#include "IncludeList.h"
/** 
* @file         Polar_IT_Funcion.h
* @brief        完成中断函数的转跳定义
* @details  初始化完中断后，在这里进行函数的重定向,该文件应当被系统自己的中断文件所包含，
*           同时包含相关中断函数的文件，应该包含该文件。
* @author       唐俊 
* @date     2018/6/5 
* @version  1.0 
* @par Copyright (c):  
*       Advanced Studios 
* @par History:          
*   version: 唐俊, 6/5, 1.0\n 
*/
#ifndef __POLAR_IT_FUNCTION
#define __POLAR_IT_FUNCTION


 #define     WWDG_IRQHandler  WWDG_IT_Function          // Window Watchdog
 #define     PVD_IRQHandler    PVD_IT_Function        //PVD through EXTI Line detect
 #define     TAMPER_IRQHandler  TAMPER_IT_Function       // Tamper
 #define           RTC_IRQHandler  RTC_IT_Function           // RTC
 #define           FLASH_IRQHandler FLASH_IT_Function         // Flash
 #define          RCC_IRQHandler      RCC_IT_Function        // RCC
 #define          EXTI0_IRQHandler EXTI0_IT_Function          // EXTI Line 0
 #define          EXTI1_IRQHandler  EXTI1_IT_Function          // EXTI Line 1
 #define          EXTI2_IRQHandler  EXTI2_IT_Function        // EXTI Line 2
 #define         EXTI3_IRQHandler   EXTI3_IT_Function        // EXTI Line 3
 #define              EXTI4_IRQHandler  EXTI4_IT_Function          // EXTI Line 4
 #define              DMA1_Channel2_IRQHandler  DMA1_Channel2_IT_Function// DMA1 Channel 2
 #define              DMA1_Channel3_IRQHandler  DMA1_Channel3_IT_Function// DMA1 Channel 3
 #define              DMA1_Channel4_IRQHandler  DMA1_Channel4_IT_Function// DMA1 Channel 4
 #define              DMA1_Channel5_IRQHandler  DMA1_Channel5_IT_Function// DMA1 Channel 5
 #define              DMA1_Channel6_IRQHandler  DMA1_Channel6_IT_Function// DMA1 Channel 6
 #define              DMA1_Channel7_IRQHandler  DMA1_Channel7_IT_Function// DMA1 Channel 7
 #define              ADC1_2_IRQHandler         ADC1_2_IT_Function  // ADC1 & ADC2
 #define              USB_HP_CAN1_TX_IRQHandler  USB_HP_CAN1_TX_IT_Function // USB High Priority or CAN1 TX
 #define              USB_LP_CAN1_RX0_IRQHandler USB_LP_CAN1_RX0_IT_Function// USB Low  Priority or CAN1 RX0
 #define              CAN1_RX1_IRQHandler       CAN1_RX1_IT_Function // CAN1 RX1
 #define              CAN1_SCE_IRQHandler       CAN1_SCE_IT_Function// CAN1 SCE
 #define              EXTI9_5_IRQHandler        EXTI9_5_IT_Function// EXTI Line 9..5
 #define              TIM1_BRK_IRQHandler        TIM1_BRK_IT_Function// TIM1 Break
 #define              TIM1_UP_IRQHandler        TIM1_UP_IT_Function// TIM1 Update
 #define              TIM1_TRG_COM_IRQHandler    TIM1_TRG_COM_IT_Function// TIM1 Trigger and Commutation
 #define              TIM1_CC_IRQHandler        TIM1_CC_IT_Function// TIM1 Capture Compare
 #define              TIM2_IRQHandler          TIM2_IT_Function // TIM2
 #define              TIM3_IRQHandler          TIM3_IT_Function // TIM3
 #define              TIM4_IRQHandler           TIM4_IT_Function// TIM4
 #define              I2C1_EV_IRQHandler       I2C1_EV_IT_Function // I2C1 Event
 #define              I2C1_ER_IRQHandler        I2C1_ER_IT_Function// I2C1 Error
 #define              I2C2_EV_IRQHandler        I2C2_EV_IT_Function// I2C2 Event
 #define              I2C2_ER_IRQHandler        I2C2_ER_IT_Function// I2C2 Error
 #define              SPI1_IRQHandler           SPI1_IT_Function // SPI1
 #define              SPI2_IRQHandler           SPI2_IT_Function// SPI2
 #define              USART1_IRQHandler          USART1_IT_Function// USART1
 #define              USART2_IRQHandler         USART2_IT_Function// USART2
 #define              USART3_IRQHandler         USART3_IT_Function// USART3
 #define              EXTI15_10_IRQHandler      EXTI15_10_IT_Function // EXTI Line 15..10
 #define              RTCAlarm_IRQHandler       RTCAlarm_IT_Function // RTC Alarm through EXTI Line
 #define              USBWakeUp_IRQHandler       USBWakeUp_IT_Function// USB Wakeup from suspend
 #define              TIM8_BRK_IRQHandler       TIM8_BRK_IT_Function// TIM8 Break
 #define              TIM8_UP_IRQHandler        TIM8_UP_IT_Function// TIM8 Update
 #define              TIM8_TRG_COM_IRQHandler   TIM8_TRG_COM_IT_Function// TIM8 Trigger and Commutation
 #define              TIM8_CC_IRQHandler        TIM8_CC_IT_Function // TIM8 Capture Compare
 #define              ADC3_IRQHandler           ADC3_IT_Function// ADC3
 #define              FSMC_IRQHandler           FSMC_IT_Function// FSMC
 #define              SDIO_IRQHandler           SDIO_IT_Function // SDIO
 #define              TIM5_IRQHandler           TIM5_IT_Function// TIM5
 #define              SPI3_IRQHandler           SPI3_IT_Function // SPI3
 #define             UART4_IRQHandler          UART4_IT_Function // UART4
 #define             UART5_IRQHandler          UART5_IT_Function// UART5
 #define             TIM6_IRQHandler          TIM6_IT_Function // TIM6
 #define             TIM7_IRQHandler          TIM7_IT_Function// TIM7
 #define             DMA2_Channel1_IRQHandler  DMA2_Channel1_IT_Function// DMA2 Channel1
 #define             DMA2_Channel2_IRQHandler  DMA2_Channel2_IT_Function // DMA2 Channel2
 #define             DMA2_Channel3_IRQHandler  DMA2_Channel3_IT_Function// DMA2 Channel3
 #define             DMA2_Channel4_5_IRQHandler DMA2_Channel4_5_IT_Function// DMA2 Channel4 & Channel5

extern void WWDG_IT_Function(void);          // Window Watchdog
extern void  PVD_IT_Function(void);       //PVD through EXTI Line detect
extern void TAMPER_IT_Function(void);       // Tamper
extern void RTC_IT_Function(void);         // RTC
extern void FLASH_IT_Function(void);        // Flash
extern void RCC_IT_Function(void);         // RCC
extern void EXTI0_IT_Function(void);           // EXTI Line 0
extern void EXTI1_IT_Function(void);           // EXTI Line 1
extern void EXTI2_IT_Function(void);         // EXTI Line 2
extern void EXTI3_IT_Function(void);         // EXTI Line 3
extern void EXTI4_IT_Function(void);           // EXTI Line 4
extern void DMA1_Channel2_IT_Function(void); // DMA1 Channel 2
extern void DMA1_Channel3_IT_Function(void); // DMA1 Channel 3
extern void DMA1_Channel4_IT_Function(void); // DMA1 Channel 4
extern void DMA1_Channel5_IT_Function(void); // DMA1 Channel 5
extern void DMA1_Channel6_IT_Function(void); // DMA1 Channel 6
extern void DMA1_Channel7_IT_Function(void); // DMA1 Channel 7
extern void ADC1_2_IT_Function(void);   // ADC1 & ADC2
extern void USB_HP_CAN1_TX_IT_Function(void);  // USB High Priority or CAN1 TX
extern void USB_LP_CAN1_RX0_IT_Function(void); // USB Low  Priority or CAN1 RX0
extern void CAN1_RX1_IT_Function(void);  // CAN1 RX1
extern void CAN1_SCE_IT_Function(void); // CAN1 SCE
extern void EXTI9_5_IT_Function(void); // EXTI Line 9..5
extern void TIM1_BRK_IT_Function(void); // TIM1 Break
extern void TIM1_UP_IT_Function(void); // TIM1 Update
extern void TIM1_TRG_COM_IT_Function(void); // TIM1 Trigger and Commutation
extern void TIM1_CC_IT_Function(void); // TIM1 Capture Compare
extern void TIM2_IT_Function(void);  // TIM2
extern void TIM3_IT_Function(void);  // TIM3
extern void TIM4_IT_Function(void); // TIM4
extern void I2C1_EV_IT_Function(void);  // I2C1 Event
extern void I2C1_ER_IT_Function(void); // I2C1 Error
extern void I2C2_EV_IT_Function(void); // I2C2 Event
extern void I2C2_ER_IT_Function(void); // I2C2 Error
extern void SPI1_IT_Function(void);  // SPI1
extern void SPI2_IT_Function(void); // SPI2
extern void USART1_IT_Function(void); // USART1
extern void USART2_IT_Function(void); // USART2
extern void USART3_IT_Function(void); // USART3
extern void EXTI15_10_IT_Function(void);  // EXTI Line 15..10
extern void RTCAlarm_IT_Function(void);  // RTC Alarm through EXTI Line
extern void USBWakeUp_IT_Function(void); // USB Wakeup from suspend
extern void TIM8_BRK_IT_Function(void); // TIM8 Break
extern void TIM8_UP_IT_Function(void); // TIM8 Update
extern void TIM8_TRG_COM_IT_Function(void); // TIM8 Trigger and Commutation
extern void TIM8_CC_IT_Function(void);  // TIM8 Capture Compare
extern void ADC3_IT_Function(void); // ADC3
extern void FSMC_IT_Function(void); // FSMC
extern void SDIO_IT_Function(void);  // SDIO
extern void TIM5_IT_Function(void); // TIM5
extern void SPI3_IT_Function(void);  // SPI3
extern void UART4_IT_Function(void);  // UART4
extern void UART5_IT_Function(void); // UART5
extern void TIM6_IT_Function (void); // TIM6
extern void TIM7_IT_Function(void); // TIM7
extern void DMA2_Channel1_IT_Function(void); // DMA2 Channel1
extern void DMA2_Channel2_IT_Function(void); // DMA2 Channel2
extern void DMA2_Channel3_IT_Function(void); // DMA2 Channel3
extern void DMA2_Channel4_5_IT_Function(void); // DMA2 Channel4 & Channel5


 #endif 