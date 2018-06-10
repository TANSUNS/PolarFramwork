#ifndef __ADC_H__
#define __ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#define uint unsigned int
#define uchar unsigned char
/******************************************/
/*********/
/*注意 单通道使用中断方式调用限于ADC2*/
/*多通道仅限DMA读取且为ADC1和ADC3*/
/*单通道DMA读取仅限于ADC3*/
/*********/
/******************************************/
//参数定义
typedef struct
{
	uint16_t ADC_DMA_MUL_DATA[8];
}ADC_DMA_MUL_GET;

#define    ADC_IRQ                       ADC1_2_IRQn
//返回变量声明

extern void NVIC_AD(uint32_t group,uint8_t main,uint8_t sub,uint8_t IRQchannel);//ADC的中断设置函数
extern void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel);//ADC单通道初始化函数
extern void ADC_INIT_Multiple_Channels(uint8_t ADCx,uint8_t CH_NUM,uint8_t GPIOx);//ADC多通道初始化函数
extern void ADC_COL(ADC_TypeDef* ADCx,FunctionalState NewState);//ADC控制函数，控制ADC读取的开始和结束
extern uint16_t ADC_Get_Single_Channel(ADC_TypeDef *Channel);//ADC获得函数  中断方式
extern void ADC_Single_DMA_Config(uint channel,uint GPIOx_ADC1,uint AD_NUM);//ADC单通道DMA获取初始化函数
extern uint16_t DMA_AD_SC(uint AD_NUM);//ADC单通道DMA读取
extern uint16_t DMA_AD_MCS(uint ADCx);//ADC多通道DMA读取
extern uint16_t ADC_Require(uint ADC_Mode,uint ADCx,uint channel,uint AD_NUM);//ADC查询函数

#endif
	
