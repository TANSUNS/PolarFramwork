#ifdef __TIM_CONFIG_H
#define __TIM_CONFIG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_define.h"
#define uint unsigned int
#define uchar unsigned char
	

//��������

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //������ʱ��ʱ�ӿ��ƺ���

//������������

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;




//���ر�������
/***********ͨ�ú���**********************/

/************������ʱ�� TIM6&TIM7**********/
/*ʹ�ó�ʼ��Ҫ��ʼ��NVIC��TIMһ��*/
extern void Basic_TIM_Config(uint8_t TIMx,uint16_t Period, uint16_t Psc);      //������ʱ����ʼ��
extern void Basic_TIM_NVIC_Config(uint TIM_NUM); //������ʱ���ж����ú���
extern int Basic_TIM_IRQ_Function();//������ʱ���жϷ�����
extern void Basic_TIM_Col(uint8_t Status);         //������ʱ�����ƺ���

/************ͨ�ö�ʱ�� TIM2~TIM5**********/
/*ͨ�ö�ʱ���ڱ�����һ��������PWM�źŷ�������Ƶ�ʲɼ�ʹ��*/
extern void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t,Psc,uint8_t Mode); //ͨ�ö�ʱ����ʼ��
/*FTM_OUTģ��*/
extern void FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty);	  	//FTM��ʼ������
extern void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState);  			  		//FTM���ƺ���
extern void Set_Duty(uint FTMx,uint16_t channel,double duty);     				  	//ռ�ձȸ��ĺ���
/*FTM_GETģ��*/
extern void FTM_GET_Config(uint FTM_GETx,uint Channel,uint16_t START_Edge);   //FTM�����ܺ���
extern void FTM_IN_NVIC_SET(uint8_t NVIC_Source,uint32_t NVIC_GROUP,uint8_t Main_Priority,uint8_t Catch_Priority); //FTM�ж����ú���
extern float FTM_GET(uint16_t END_Edge);                                      //FTM������(һ���������stm32f10x_it.h����)
extern uint32_t FTM_Time_Transfer();                                                //����������ݺ���
/************�߼���ʱ�� TIM1&TIM8**********/




//��������

#endif
