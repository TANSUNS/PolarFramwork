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
	

//参数定义

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //基本定时器时钟控制函数

//特殊数据类型

extern TIM_ICUserValueTypeDef TIM_ICUserValueStructure;




//返回变量声明
/***********通用函数**********************/

/************基本定时器 TIM6&TIM7**********/
/*使用初始化要初始化NVIC和TIM一起*/
extern void Basic_TIM_Config(uint8_t TIMx,uint16_t Period, uint16_t Psc);      //基本定时器初始化
extern void Basic_TIM_NVIC_Config(uint TIM_NUM); //基本定时器中断配置函数
extern int Basic_TIM_IRQ_Function();//基本定时器中断服务函数
extern void Basic_TIM_Col(uint8_t Status);         //基本定时器控制函数

/************通用定时器 TIM2~TIM5**********/
/*通用定时器在比赛中一般用来做PWM信号发生器或频率采集使用*/
extern void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t,Psc,uint8_t Mode); //通用定时器初始化
/*FTM_OUT模块*/
extern void FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty);	  	//FTM初始化函数
extern void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState);  			  		//FTM控制函数
extern void Set_Duty(uint FTMx,uint16_t channel,double duty);     				  	//占空比更改函数
/*FTM_GET模块*/
extern void FTM_GET_Config(uint FTM_GETx,uint Channel,uint16_t START_Edge);   //FTM捕获功能函数
extern void FTM_IN_NVIC_SET(uint8_t NVIC_Source,uint32_t NVIC_GROUP,uint8_t Main_Priority,uint8_t Catch_Priority); //FTM中断设置函数
extern float FTM_GET(uint16_t END_Edge);                                      //FTM捕获函数(一般情况下在stm32f10x_it.h调用)
extern uint32_t FTM_Time_Transfer();                                                //计算参数传递函数
/************高级定时器 TIM1&TIM8**********/




//函数声明

#endif
