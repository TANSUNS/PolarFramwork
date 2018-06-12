#ifndef __POLAR_ADC_H__
#define __POLAR_ADC_H__

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
/*ע�� ��ͨ��ʹ���жϷ�ʽ��������ADC2*/
/*��ͨ������DMA��ȡ��ΪADC1��ADC3*/
/*��ͨ��DMA��ȡ������ADC3*/
/*********/
/******************************************/
//��������
typedef struct
{
	uint16_t ADC_DMA_MUL_DATA[8];
}ADC_DMA_MUL_GET;

#define    ADC_IRQ                       ADC1_2_IRQn
//���ر�������

extern void NVIC_AD(uint32_t group,uint8_t main,uint8_t sub,uint8_t IRQchannel);//ADC���ж����ú���
extern void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel);//ADC��ͨ����ʼ������
extern void ADC_INIT_Multiple_Channels(uint8_t ADCx,uint8_t CH_NUM,uint8_t GPIOx);//ADC��ͨ����ʼ������
extern void ADC_COL(ADC_TypeDef* ADCx,FunctionalState NewState);//ADC���ƺ���������ADC��ȡ�Ŀ�ʼ�ͽ���
extern uint16_t ADC_Get_Single_Channel(ADC_TypeDef *Channel);//ADC��ú���  �жϷ�ʽ
extern void ADC_Single_DMA_Config(uint channel,uint GPIOx_ADC1,uint AD_NUM);//ADC��ͨ��DMA��ȡ��ʼ������
extern uint16_t DMA_AD_SC(uint AD_NUM);//ADC��ͨ��DMA��ȡ
extern uint16_t DMA_AD_MCS(uint ADCx);//ADC��ͨ��DMA��ȡ
extern uint16_t ADC_Require(uint ADC_Mode,uint ADCx,uint channel,uint AD_NUM);//ADC��ѯ����

#endif
	
