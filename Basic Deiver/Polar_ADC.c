#include "stm32f10x.h"
#include "Polar_ADC.h"
#include "stm32f10x_define.h"
#include "IncludeList.h"
#include <stdio.h>
#include "Polar_DMA.h"

#define uint unsigned int
#define uchar unsigned char



__IO uint16_t ADC1_ConvertedValue[6]={0,0,0,0};
__IO uint16_t ADC3_ConvertedValue[6]={0,0,0,0};

__IO uint16_t ADC1_DMA_GET0;
__IO uint16_t ADC1_DMA_GET1;
__IO uint16_t ADC1_DMA_GET2;
__IO uint16_t ADC1_DMA_GET3;
__IO uint16_t ADC1_DMA_GET4;
__IO uint16_t ADC1_DMA_GET5;

__IO uint16_t ADC_Single_IT_Get;



//extern __IO uint16_t ADC_Single_IT_Get;
//extern __IO uint16_t ADC3_DMA_GET;
//extern __IO uint16_t ADC1_ConvertedValue[6];
//extern __IO uint16_t ADC3_ConvertedValue[6];

typedef struct
{
	uint32_t ADC_CLK;
}ADC_CLK;

ADC_CLK ADC1_CLK;
ADC_CLK ADC2_CLK;
ADC_CLK ADC3_CLK;

/*ADC��ͨ��ͨ������ȡ�ṹ*/

typedef struct
{
	uint8_t CH[16];
	uint16_t PIN[16];
	uint32_t CLK[16];
}ADC_CHS;
ADC_CHS AD_ch;

ADC_DMA_MUL_GET DMA_MUL_ADC_DATA;

extern ADC_DMA_MUL_GET DMA_MUL_ADC_DATA;

/*
ADC��ͨ����ʼ������(�жϷ�ʽ)
void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel)
ADCx ADC_1 ADC_2 ADC_3
Channel ADC_Channel0.......ADC_Channel15

ATTENTION:��ͨ��һ��ʹ��ADC2��1��3����DMA��ѯ

*/
void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	uint8_t Channel_Set;
	switch(Channel)
	{
		case 0:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			Channel_Set = ADC_Channel_0 ;
			break;
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			Channel_Set = ADC_Channel_1 ;		
			break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			Channel_Set = ADC_Channel_2 ;	
			break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);			
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			Channel_Set = ADC_Channel_3 ;		
			break;
		case 4:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_4 ;				
			break;
		case 5:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_5 ;				
			break;
		case 6:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_6 ;				
			break;
		case 7:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_7 ;				
			break;
		case 8:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_8 ;				
			break;
		case 9:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
			GPIO_Init(GPIOB, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_9 ;				
			break;
		case 10:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_10 ;				
			break;
		case 11:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_11 ;				
			break;
		case 12:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_12 ;				
			break;
		case 13:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_13 ;				
			break;
		case 14:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_14 ;				
			break;
		case 15:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			GPIO_Init(GPIOC, &GPIO_InitStructure);
			Channel_Set = ADC_Channel_15 ;				
			break;	
	}
	switch(ADCx)
	{
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);	
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
			ADC_InitStructure.ADC_ScanConvMode = DISABLE ; //��ֹɨ��
			ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿ����
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
			ADC_InitStructure.ADC_NbrOfChannel = 1;	//һ��ת��ͨ��
			ADC_Init(ADC1, &ADC_InitStructure);//��ʼ��
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); //��Ƶ9MHz
			ADC_RegularChannelConfig(ADC1, Channel_Set, 1, ADC_SampleTime_55Cycles5);//���ò���ʱ��
			ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	// ADC ת�����������ж�
			ADC_Cmd(ADC1, ENABLE);	// ������ADC�������ʹ�ÿ��ƺ���
			ADC_ResetCalibration(ADC1);	// ��ʼ��ADC У׼�Ĵ���  
			while(ADC_GetResetCalibrationStatus(ADC1));	// �ȴ�У׼�Ĵ�����ʼ�����
			ADC_StartCalibration(ADC1);	// ADC��ʼУ׼
			while(ADC_GetCalibrationStatus(ADC1));	// �ȴ�У׼���	
			break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);	
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
			ADC_InitStructure.ADC_ScanConvMode = DISABLE ; //��ֹɨ��
			ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿ����
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
			ADC_InitStructure.ADC_NbrOfChannel = 1;	//һ��ת��ͨ��
			ADC_Init(ADC2, &ADC_InitStructure);//��ʼ��
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); //��Ƶ9MHz
			ADC_RegularChannelConfig(ADC2, Channel_Set, 1, ADC_SampleTime_55Cycles5);//���ò���ʱ��
			ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);	// ADC ת�����������ж�
			ADC_Cmd(ADC2, ENABLE);	// ����ADC�������ʹ�ÿ��ƺ���
			ADC_ResetCalibration(ADC2);	// ��ʼ��ADC У׼�Ĵ���  
			while(ADC_GetResetCalibrationStatus(ADC2));	// �ȴ�У׼�Ĵ�����ʼ�����
			ADC_StartCalibration(ADC2);	// ADC��ʼУ׼
			while(ADC_GetCalibrationStatus(ADC2));	// �ȴ�У׼���		
			break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
			ADC_InitStructure.ADC_ScanConvMode = DISABLE ; //��ֹɨ��
			ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//����ת��
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿ����
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
			ADC_InitStructure.ADC_NbrOfChannel = 1;	//һ��ת��ͨ��
			ADC_Init(ADC3, &ADC_InitStructure);//��ʼ��
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); //��Ƶ9MHz
			ADC_RegularChannelConfig(ADC3, Channel_Set, 1, ADC_SampleTime_55Cycles5);//���ò���ʱ��
			ADC_ITConfig(ADC3, ADC_IT_EOC, ENABLE);	// ADC ת�����������ж�
			ADC_Cmd(ADC3, ENABLE);	// ������ADC�������ʹ�ÿ��ƺ���
			ADC_ResetCalibration(ADC3);	// ��ʼ��ADC У׼�Ĵ���  
			while(ADC_GetResetCalibrationStatus(ADC3));	// �ȴ�У׼�Ĵ�����ʼ�����
			ADC_StartCalibration(ADC3);	// ADC��ʼУ׼
			while(ADC_GetCalibrationStatus(ADC3));	// �ȴ�У׼���		
			break;
	}
	
}
/*
ADC��ͨ�����ƺ���
void ADC_COL(ADC_TypeDef* ADCx,FunctionalState NewState);
ADCx ADC1 ADC2 ADC3
NewState ENABLE DISABLE
*/
void ADC_COL(ADC_TypeDef* ADCx,FunctionalState NewState)
{
	ADC_Cmd(ADCx, NewState);	
}
/*
ADC��ͨ����ʼ��ͨ����ʩ����
void ADC_MCS_GET()
�˺�����Ҫ�û����и���
*/
void ADC_MCS_GET()
{
	AD_ch.CH[0] = ADC_Channel_0;
	AD_ch.PIN[0] = GPIO_Pin_0;
	
	AD_ch.CH[1] = ADC_Channel_1;
	AD_ch.PIN[1] = GPIO_Pin_1;
	
	AD_ch.CH[2] = ADC_Channel_2;
	AD_ch.PIN[2] = GPIO_Pin_2;
	
	AD_ch.CH[3] = ADC_Channel_3;
	AD_ch.PIN[3] = GPIO_Pin_3;
	
	AD_ch.CH[4] = ADC_Channel_4;
	AD_ch.PIN[4] = GPIO_Pin_4;
	
	AD_ch.CH[5] = ADC_Channel_5;
	AD_ch.PIN[5] = GPIO_Pin_5;
	
	AD_ch.CH[6] = ADC_Channel_6;
	AD_ch.PIN[6] = GPIO_Pin_6;
	
	AD_ch.CH[7] = ADC_Channel_7;
	AD_ch.PIN[7] = GPIO_Pin_7;
	
	AD_ch.CH[8] = ADC_Channel_8;
	AD_ch.PIN[0] = GPIO_Pin_0;
	
	AD_ch.CH[9] = ADC_Channel_9;
	AD_ch.PIN[9] = GPIO_Pin_1;
	
	AD_ch.CH[10] = ADC_Channel_10;
	AD_ch.PIN[10] = GPIO_Pin_0;
	
	AD_ch.CH[11] = ADC_Channel_11;
	AD_ch.PIN[11] = GPIO_Pin_1;
	
	AD_ch.CH[12] = ADC_Channel_12;
	AD_ch.PIN[12] = GPIO_Pin_2;
	
	AD_ch.CH[13] = ADC_Channel_13;
	AD_ch.PIN[13] = GPIO_Pin_3;
	
	AD_ch.CH[14] = ADC_Channel_14;
	AD_ch.PIN[14] = GPIO_Pin_4;
	
	AD_ch.CH[15] = ADC_Channel_15;
	AD_ch.PIN[15] = GPIO_Pin_5;
	
}
/*
��ͨ��ADת����ʼ������
void ADC_INIT_Multiple_Channels(uint8_t ADCx,uint8_t CH_NUM)
void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel)
ADCx ADC_1  ADC_3
Channel ADC_Channel0.......ADC_Channel11
 GPIOA_SET
ע�⣺һ��ֻ��һ��˿�
ֻ���ADC1��ͨ��0-ͨ��5ȫ����ADC3��ͨ��0-ͨ��3ȫ��
*/
void ADC_INIT_Multiple_Channels(uint8_t ADCx,uint8_t CH_NUM,uint8_t GPIOx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	/************************GPIO�ܽų�ʼ��*******************************/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	switch(CH_NUM)
	{
		case 2:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1];
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1]|AD_ch.PIN[2];
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1]|AD_ch.PIN[2]|AD_ch.PIN[3];
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1]|AD_ch.PIN[2]|AD_ch.PIN[3]|AD_ch.PIN[4];
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1]|AD_ch.PIN[2]|AD_ch.PIN[3]|AD_ch.PIN[4]|AD_ch.PIN[5];
			break;
		case 7:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1]|AD_ch.PIN[2]|AD_ch.PIN[3]|AD_ch.PIN[4]|AD_ch.PIN[5]|AD_ch.PIN[6];
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = AD_ch.PIN[0]|AD_ch.PIN[1]|AD_ch.PIN[2]|AD_ch.PIN[3]|AD_ch.PIN[4]|AD_ch.PIN[5]|AD_ch.PIN[6]|AD_ch.PIN[7];
			break;
	}
		switch(GPIOx)
	{
		case 1:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
			GPIO_Init(GPIOB, &GPIO_InitStructure);	
			break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
			GPIO_Init(GPIOC, &GPIO_InitStructure);	
			break;
	}
	/**************************GPIO_DMA_MODE_SET*****************************/
	
	switch(ADCx)
	{
		case 1:
			RCC_AHBPeriphClockCmd(ADC1_DMA_CLK, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
		  DMA_INIT(ADC_1,HighLevel,CH_NUM,ADC1_Data_Address,HalfWords,Hold,(uint32_t)ADC1_ConvertedValue,HalfWords,Inc,PERIPHTOMEM,Circle);
			break;
		case 3:
			RCC_AHBPeriphClockCmd(ADC3_DMA_CLK, ENABLE);
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
			DMA_INIT(ADC_1,HighLevel,CH_NUM,ADC3_Data_Address,HalfWords,Hold,(uint32_t)ADC3_ConvertedValue,HalfWords,Inc,PERIPHTOMEM,Circle);

			break;
	}
	/*****************************GPIO_ADC_MODE_SET*********************************/

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; // ɨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;// ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// �����ⲿ����ת������������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	// ת������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = CH_NUM;		// ת��ͨ������
		
switch(ADCx)
{
	case 1:
			ADC_Init(ADC1, &ADC_InitStructure);	// ��ʼ��ADC
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	// 8��Ƶ9MHz
			switch(CH_NUM)
			{
				case 2:
					ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					break;
				case 3:
					ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);	
					break;
				case 4:
					ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);				
					break;
				case 5:
					ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);		
					break;
				case 6:
					ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5);				
					break;
			}
				ADC_DMACmd(ADC1, ENABLE);	// ʹ��ADC DMA ����
				ADC_Cmd(ADC1, ENABLE);	// ����ADC ������ʼת��
				ADC_ResetCalibration(ADC1);	// ��ʼ��ADC У׼�Ĵ���  
				while(ADC_GetResetCalibrationStatus(ADC1));	// �ȴ�У׼�Ĵ�����ʼ�����
				ADC_StartCalibration(ADC1);	// ADC��ʼУ׼
				while(ADC_GetCalibrationStatus(ADC1));	// �ȴ�У׼���
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// ����û�в����ⲿ����������ʹ���������ADCת�� 
		break;
	case 3:
			ADC_Init(ADC3, &ADC_InitStructure);	// ��ʼ��ADC
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	// 8��Ƶ9MHz
			switch(CH_NUM)
			{
				case 2:
					ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					break;
				case 3:
					ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);	
					break;
				case 4:
					ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);				
					break;
				case 5:
					ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);		
					break;
				case 6:
					ADC_RegularChannelConfig(ADC3, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_4, 5, ADC_SampleTime_55Cycles5);
					ADC_RegularChannelConfig(ADC3, ADC_Channel_5, 6, ADC_SampleTime_55Cycles5);				
					break;
			}
				ADC_DMACmd(ADC3, ENABLE);	// ʹ��ADC DMA ����
				ADC_Cmd(ADC3, ENABLE);	// ����ADC ������ʼת��
				ADC_ResetCalibration(ADC3);	// ��ʼ��ADC У׼�Ĵ���  
				while(ADC_GetResetCalibrationStatus(ADC3));	// �ȴ�У׼�Ĵ�����ʼ�����
				ADC_StartCalibration(ADC3);	// ADC��ʼУ׼
				while(ADC_GetCalibrationStatus(ADC3));	// �ȴ�У׼���
				ADC_SoftwareStartConvCmd(ADC3, ENABLE);	// ����û�в����ⲿ����������ʹ���������ADCת�� 	
		break;
}
}

/*
��ͨ��ADת��ֵ��ȡ����(�жϷ�ʽ)
double ADC_Get_Single_Channel()
����ֵ ADC2��������ADת��ֵ
���жϺ��������
*/
uint16_t ADC_Get_Single_Channel(ADC_TypeDef *Channel)
{

	uint16_t Output;
	ADC_SoftwareStartConvCmd(Channel, ENABLE);	
	while(ADC_GetFlagStatus  ( Channel,ADC_FLAG_EOC)!=SET){};
	ADC_SoftwareStartConvCmd(Channel, DISABLE);
	ADC_ClearFlag(Channel,ADC_FLAG_EOC);
  Output=ADC_GetConversionValue(Channel);  		
	

	return Output;
}

/*
ADC1��ͨ��DMA��ȡ��ʼ������
void ADC_Single_DMA_Config(uint channel,uint GPIOx_ADC1,uint32_t Address)
channel ADC_Channel0 ADC_Channel1......
GPIOx_ADC3  GPIOA_SET GPIOC_SET   
*/
void ADC_Single_DMA_Config(uint channel,uint GPIOx_ADC1,uint AD_NUM)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
			switch(GPIOx_ADC1)
	{
		case 1:
			RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOA, ENABLE );
			break;
		case 3:
			RCC_APB2PeriphClockCmd ( RCC_APB2Periph_GPIOC, ENABLE );
			break;
	}
	switch(channel)
	{
		case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			break;
		case 1:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
			break;
	}
	
		switch(GPIOx_ADC1)
	{
		case 1:
			GPIO_Init(GPIOA, &GPIO_InitStructure);	
			break;
		case 3:
			GPIO_Init(GPIOC, &GPIO_InitStructure);	
			break;
	}
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	RCC_APB2PeriphClockCmd ( RCC_APB2Periph_ADC1, ENABLE );
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ( uint32_t ) ( & ( ADC1->DR ) );
	switch(AD_NUM)
	{
		case 0:
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1_DMA_GET0 ;
		break;
		case 1:
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1_DMA_GET1 ;
		break;
		case 2:
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1_DMA_GET2 ;
		break;
		case 3:
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1_DMA_GET3 ;
		break;
		case 4:
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1_DMA_GET4 ;
		break;
		case 5:
			DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADC1_DMA_GET5 ;
		break;
	}
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;	
	DMA_InitStructure.DMA_BufferSize = 1;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable; 
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;	
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	DMA_Cmd(DMA1_Channel1 , ENABLE);
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;// ֻʹ��һ��ADC�����ڵ�ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	// ����ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// �����ⲿ����ת������������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	// ת������Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;		// ת��ͨ��1��
	ADC_Init(ADC1, &ADC_InitStructure);	// ��ʼ��ADC
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	// ����ADCʱ��ΪPCLK2��8��Ƶ����9MHz
	
	switch(channel)
	{
		case 0:
			ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 1:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 2:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 3:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 10:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 11:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 12:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
		case 13:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_55Cycles5);	// ���� ADC ͨ��ת��˳��Ϊ1����һ��ת��������ʱ��Ϊ55.5��ʱ������
			break;
	}
	ADC_DMACmd(ADC1, ENABLE);	// ʹ��ADC DMA ����
	ADC_Cmd(ADC1, ENABLE);	// ����ADC ������ʼת��
	ADC_ResetCalibration(ADC1);	// ��ʼ��ADC У׼�Ĵ���  
	while(ADC_GetResetCalibrationStatus(ADC1));	// �ȴ�У׼�Ĵ�����ʼ�����
	ADC_StartCalibration(ADC1);	// ADC��ʼУ׼
	while(ADC_GetCalibrationStatus(ADC1));	// �ȴ�У׼���
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// ����û�в����ⲿ����������ʹ���������ADCת�� 
}
/*
��ͨ��ADת��DMA��ȡ
uint16_t DMA_AD_SC();
����ֵ DMA��õ�ADC3��ADת��ֵ
*/
uint16_t DMA_AD_SC(uint AD_NUM)
{
	uint16_t ADC_Value;
			switch(AD_NUM)
			{
				case 0:
					ADC_Value = ADC1_DMA_GET0;
					break;
				case 1:
					ADC_Value = ADC1_DMA_GET1;
					break;
				case 2:
					ADC_Value = ADC1_DMA_GET2;
					break;
				case 3:
					ADC_Value = ADC1_DMA_GET3;
					break;
				case 4:
					ADC_Value = ADC1_DMA_GET4;
					break;
				case 5:
					ADC_Value = ADC1_DMA_GET5;
					break;
			}
	return ADC_Value;
}
/*
��ͨ��ADת��DMA��ȡ
uint16_t DMA_AD_MCS()
���ݴ洢��
DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[0]
����������
*/
uint16_t DMA_AD_MCS(uint ADCx)
{
	switch(ADCx)
	{
		case 1:
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[0] = ADC1_ConvertedValue[0];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[1] = ADC1_ConvertedValue[1];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[2] = ADC1_ConvertedValue[2];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[3] = ADC1_ConvertedValue[3];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[4] = ADC1_ConvertedValue[4];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[5] = ADC1_ConvertedValue[5];
			break;
		case 2:
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[0] = ADC3_ConvertedValue[0];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[1] = ADC3_ConvertedValue[1];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[2] = ADC3_ConvertedValue[2];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[3] = ADC3_ConvertedValue[3];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[4] = ADC3_ConvertedValue[4];
			DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[5] = ADC3_ConvertedValue[5];
			break;
	}
	return 0;
}
/*
ADC��ѯ����
ADC_Require(uint ADC_Mode,uint ADCx,uint channel)
ADC_Mode  		 SIT  //��ͨ���ж�ģʽ
							 SDMA //��ͨ��DMA����
							 MDMA //��ͨ��DMA����
ADCx 			 		 ADC_1                        
							 ADC_2                       
							 ADC_3        
channel        ADC_Channel0  
							 ADC_Channel1.......

ʹ�÷�ʽ 
1����ʹ�õ�ͨ���ж�ģʽ�͵�ͨ��DMAģʽ�º���������������������
2����ʹ�ö�ͨ��DMA��ģʽ����������һ��Ҫ���ձ���������

*/
uint16_t ADC_Require(uint ADC_Mode,uint ADCx,uint channel,uint AD_NUM)
{
	uint16_t ADC_Convert_value;
	switch(ADC_Mode)
	{
		case 1:   //��ͨ���ж�ģʽ
			ADC_Convert_value = ADC_Single_IT_Get;
			break;
		case 2:   //��ͨ��DMA
			switch(AD_NUM)
			{
				case 0:
					ADC_Convert_value = ADC1_DMA_GET0;
					break;
				case 1:
					ADC_Convert_value = ADC1_DMA_GET1;
					break;
				case 2:
					ADC_Convert_value = ADC1_DMA_GET2;
					break;
				case 3:
					ADC_Convert_value = ADC1_DMA_GET3;
					break;
				case 4:
					ADC_Convert_value = ADC1_DMA_GET4;
					break;
				case 5:
					ADC_Convert_value = ADC1_DMA_GET5;
					break;
			}
			break;
		case 3:   //��ͨ��DMA
			switch(ADCx)
			{
				case 1:
					ADC_Convert_value=ADC1_ConvertedValue[channel];
					break;
				case 3:
					ADC_Convert_value=ADC3_ConvertedValue[channel];
					break;
			}
			break;
	}
	return ADC_Convert_value;
}
