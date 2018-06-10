#include "stm32f10x.h"
#include "adc.h"
#include "stm32f10x_define.h"
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

/*ADC多通道通道数获取结构*/

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
ADC单通道初始化函数(中断方式)
void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel)
ADCx ADC_1 ADC_2 ADC_3
Channel ADC_Channel0.......ADC_Channel15

ATTENTION:单通道一般使用ADC2，1和3用在DMA查询

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
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
			ADC_InitStructure.ADC_ScanConvMode = DISABLE ; //禁止扫描
			ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//连续转换
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不使用外部触发
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
			ADC_InitStructure.ADC_NbrOfChannel = 1;	//一个转换通道
			ADC_Init(ADC1, &ADC_InitStructure);//初始化
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); //分频9MHz
			ADC_RegularChannelConfig(ADC1, Channel_Set, 1, ADC_SampleTime_55Cycles5);//配置采样时间
			ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);	// ADC 转换结束产生中断
			ADC_Cmd(ADC1, ENABLE);	// 不开启ADC按需求打开使用控制函数
			ADC_ResetCalibration(ADC1);	// 初始化ADC 校准寄存器  
			while(ADC_GetResetCalibrationStatus(ADC1));	// 等待校准寄存器初始化完成
			ADC_StartCalibration(ADC1);	// ADC开始校准
			while(ADC_GetCalibrationStatus(ADC1));	// 等待校准完成	
			break;
		case 2:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2,ENABLE);	
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
			ADC_InitStructure.ADC_ScanConvMode = DISABLE ; //禁止扫描
			ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//连续转换
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不使用外部触发
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
			ADC_InitStructure.ADC_NbrOfChannel = 1;	//一个转换通道
			ADC_Init(ADC2, &ADC_InitStructure);//初始化
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); //分频9MHz
			ADC_RegularChannelConfig(ADC2, Channel_Set, 1, ADC_SampleTime_55Cycles5);//配置采样时间
			ADC_ITConfig(ADC2, ADC_IT_EOC, ENABLE);	// ADC 转换结束产生中断
			ADC_Cmd(ADC2, ENABLE);	// 开启ADC按需求打开使用控制函数
			ADC_ResetCalibration(ADC2);	// 初始化ADC 校准寄存器  
			while(ADC_GetResetCalibrationStatus(ADC2));	// 等待校准寄存器初始化完成
			ADC_StartCalibration(ADC2);	// ADC开始校准
			while(ADC_GetCalibrationStatus(ADC2));	// 等待校准完成		
			break;
		case 3:
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE);
			ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
			ADC_InitStructure.ADC_ScanConvMode = DISABLE ; //禁止扫描
			ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//连续转换
			ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不使用外部触发
			ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//右对齐
			ADC_InitStructure.ADC_NbrOfChannel = 1;	//一个转换通道
			ADC_Init(ADC3, &ADC_InitStructure);//初始化
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); //分频9MHz
			ADC_RegularChannelConfig(ADC3, Channel_Set, 1, ADC_SampleTime_55Cycles5);//配置采样时间
			ADC_ITConfig(ADC3, ADC_IT_EOC, ENABLE);	// ADC 转换结束产生中断
			ADC_Cmd(ADC3, ENABLE);	// 不开启ADC按需求打开使用控制函数
			ADC_ResetCalibration(ADC3);	// 初始化ADC 校准寄存器  
			while(ADC_GetResetCalibrationStatus(ADC3));	// 等待校准寄存器初始化完成
			ADC_StartCalibration(ADC3);	// ADC开始校准
			while(ADC_GetCalibrationStatus(ADC3));	// 等待校准完成		
			break;
	}
	
}
/*
ADC单通道控制函数
void ADC_COL(ADC_TypeDef* ADCx,FunctionalState NewState);
ADCx ADC1 ADC2 ADC3
NewState ENABLE DISABLE
*/
void ADC_COL(ADC_TypeDef* ADCx,FunctionalState NewState)
{
	ADC_Cmd(ADCx, NewState);	
}
/*
ADC多通道初始化通道设施函数
void ADC_MCS_GET()
此函数需要用户自行更改
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
多通道AD转换初始化函数
void ADC_INIT_Multiple_Channels(uint8_t ADCx,uint8_t CH_NUM)
void ADC_INIT_Single_Channel(uint8_t ADCx,uint8_t Channel)
ADCx ADC_1  ADC_3
Channel ADC_Channel0.......ADC_Channel11
 GPIOA_SET
注意：一次只开一组端口
只针对ADC1的通道0-通道5全开和ADC3的通道0-通道3全开
*/
void ADC_INIT_Multiple_Channels(uint8_t ADCx,uint8_t CH_NUM,uint8_t GPIOx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	/************************GPIO管脚初始化*******************************/
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

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	// 只使用一个ADC，属于单模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ; // 扫描模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;// 连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 不用外部触发转换，软件开启即可
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	// 转换结果右对齐
	ADC_InitStructure.ADC_NbrOfChannel = CH_NUM;		// 转换通道个数
		
switch(ADCx)
{
	case 1:
			ADC_Init(ADC1, &ADC_InitStructure);	// 初始化ADC
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	// 8分频9MHz
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
				ADC_DMACmd(ADC1, ENABLE);	// 使能ADC DMA 请求
				ADC_Cmd(ADC1, ENABLE);	// 开启ADC ，并开始转换
				ADC_ResetCalibration(ADC1);	// 初始化ADC 校准寄存器  
				while(ADC_GetResetCalibrationStatus(ADC1));	// 等待校准寄存器初始化完成
				ADC_StartCalibration(ADC1);	// ADC开始校准
				while(ADC_GetCalibrationStatus(ADC1));	// 等待校准完成
				ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// 由于没有采用外部触发，所以使用软件触发ADC转换 
		break;
	case 3:
			ADC_Init(ADC3, &ADC_InitStructure);	// 初始化ADC
			RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	// 8分频9MHz
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
				ADC_DMACmd(ADC3, ENABLE);	// 使能ADC DMA 请求
				ADC_Cmd(ADC3, ENABLE);	// 开启ADC ，并开始转换
				ADC_ResetCalibration(ADC3);	// 初始化ADC 校准寄存器  
				while(ADC_GetResetCalibrationStatus(ADC3));	// 等待校准寄存器初始化完成
				ADC_StartCalibration(ADC3);	// ADC开始校准
				while(ADC_GetCalibrationStatus(ADC3));	// 等待校准完成
				ADC_SoftwareStartConvCmd(ADC3, ENABLE);	// 由于没有采用外部触发，所以使用软件触发ADC转换 	
		break;
}
}

/*
单通道AD转换值获取程序(中断方式)
double ADC_Get_Single_Channel()
返回值 ADC2测量到的AD转换值
在中断函数里调用
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
ADC1单通道DMA读取初始化函数
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
	
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;// 只使用一个ADC，属于单模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ; 	// 禁止扫描模式，多通道才要，单通道不需要
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	// 连续转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	// 不用外部触发转换，软件开启即可
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	// 转换结果右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;		// 转换通道1个
	ADC_Init(ADC1, &ADC_InitStructure);	// 初始化ADC
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 	// 配置ADC时钟为PCLK2的8分频，即9MHz
	
	switch(channel)
	{
		case 0:
			ADC_RegularChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 1:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 2:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 3:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 10:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_10, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 11:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 12:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
		case 13:
			ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_55Cycles5);	// 配置 ADC 通道转换顺序为1，第一个转换，采样时间为55.5个时钟周期
			break;
	}
	ADC_DMACmd(ADC1, ENABLE);	// 使能ADC DMA 请求
	ADC_Cmd(ADC1, ENABLE);	// 开启ADC ，并开始转换
	ADC_ResetCalibration(ADC1);	// 初始化ADC 校准寄存器  
	while(ADC_GetResetCalibrationStatus(ADC1));	// 等待校准寄存器初始化完成
	ADC_StartCalibration(ADC1);	// ADC开始校准
	while(ADC_GetCalibrationStatus(ADC1));	// 等待校准完成
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);	// 由于没有采用外部触发，所以使用软件触发ADC转换 
}
/*
单通道AD转换DMA获取
uint16_t DMA_AD_SC();
返回值 DMA获得的ADC3的AD转换值
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
多通道AD转换DMA获取
uint16_t DMA_AD_MCS()
数据存储在
DMA_MUL_ADC_DATA.ADC_DMA_MUL_DATA[0]
的数组里面
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
ADC查询函数
ADC_Require(uint ADC_Mode,uint ADCx,uint channel)
ADC_Mode  		 SIT  //单通道中断模式
							 SDMA //单通道DMA传输
							 MDMA //多通道DMA传输
ADCx 			 		 ADC_1                        
							 ADC_2                       
							 ADC_3        
channel        ADC_Channel0  
							 ADC_Channel1.......

使用方式 
1、在使用单通道中断模式和单通道DMA模式下后两个参数可以随意设置
2、在使用多通道DMA的模式下三个参数一定要按照表格进行设置

*/
uint16_t ADC_Require(uint ADC_Mode,uint ADCx,uint channel,uint AD_NUM)
{
	uint16_t ADC_Convert_value;
	switch(ADC_Mode)
	{
		case 1:   //单通道中断模式
			ADC_Convert_value = ADC_Single_IT_Get;
			break;
		case 2:   //单通道DMA
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
		case 3:   //多通道DMA
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
