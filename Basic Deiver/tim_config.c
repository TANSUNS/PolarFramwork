#include "tim_config.h"
#include "stm32f10x_define.h"
#include "uart.h"

#define uint unsigned int
#define uchar unsigned char

//1MHz = 1000000Hz

extern volatile uint32_t time;

#define BASIC_TIM_CLK_Cmd    RCC_APB1PeriphClockCmd  //基本定时器时钟控制函数
#define GENERAL_TIM_CLK_Cmd  RCC_APB1PeriphClockCmd  //通用定时器时钟控制函数

float Duty_Set;

uint32_t TIM_PscCLK = 72000000 / 72;
/*********************************************************************************/
														/****************************/
																	//特殊数据类型
														/****************************/
/*********************************************************************************/


/**********基本定时器用************/
typedef struct  
{
  TIM_TypeDef* TIM_Data;
	uint8_t NVIC_CH;
}TIM_INFMATION;

TIM_INFMATION TIM_CODE;

/**********************/

/**********通用定时器用（FTM）***************/
typedef struct
{
	uint16_t PSC_DATA0;
	uint16_t PSC_DATA1;
	uint16_t PSC_DATA2;
	uint16_t PSC_DATA3;
}PSC;

PSC PSCA;//计算不同定时器重载计数器的值便于之后设置改变及占空比的计算函数
/*************************************/

/******************通用定时器（FTM_IN）中断标志结构******************/
typedef struct 
{
	uint FTM_IN_NVIC_CH;
}FTM_NVIC;
FTM_NVIC FTM_NVIC_SET;
/************************存储FTM捕获的结构***************************/
typedef struct
{
	double FTM_IN_DATA;
}FTM_IN_Data;
FTM_IN_Data FTM_Got;
extern FTM_IN_Data FTM_Got;


TIM_ICUserValueTypeDef TIM_ICUserValueStructure = {0,0,0,0};

/******************************************************************/





/*具体的细节定义见stm32f10x_define.h*/


/*
定时器状态控制函数可以开启和关闭
 void Basic_TIM_Col(uint8_t Status)
                           状态
Status   Set_ENABLE   Set_DISABLE
TIM_TypeDef* TIMx
*/


void Basic_TIM_Col(uint8_t Status)
{
	switch(Status)
	{
		case 0:
		TIM_ITConfig(TIM_CODE.TIM_Data,TIM_IT_Update,DISABLE);
		TIM_Cmd(TIM_CODE.TIM_Data, DISABLE);	
		break;
		case 1:
		TIM_ITConfig(TIM_CODE.TIM_Data,TIM_IT_Update,ENABLE);
		TIM_Cmd(TIM_CODE.TIM_Data, ENABLE);	
		break;
	}
}


/******基本定时器部分******/
/*
基本定时器TIM6&TIM7初始化函数
Basic_TIM_Config(uint8_t TIMx,uint8_t Period, uint8_t Psc)
                      TIM        定时器周期       分频因子
  TIMx   BASIC_TIM_6  BASIC_TIM_7
  Period  计算得到 如果Psc=71 时钟 1MHz  Period = 1000 时为计数周期1ms
  Psc   一般为71； 系统时钟-1
注意：次函数没有开启定时器，仅仅是初始化，需要再次Enable
*/


void Basic_TIM_Config(uint8_t TIMx,uint16_t Period, uint16_t Psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	switch(TIMx)
	{
		case 6:
			BASIC_TIM_CLK_Cmd(RCC_APB1Periph_TIM6,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
		  TIM_TimeBaseStructure.TIM_Prescaler = Psc;
		  TIM_TimeBaseInit(TIM6,&TIM_TimeBaseStructure);
			TIM_ClearFlag(TIM6,TIM_FLAG_Update);
		  Basic_TIM_Col(Set_DISABLE);
			TIM_CODE.TIM_Data = TIM6;
		  TIM_CODE.NVIC_CH = TIM6_IRQn;
			break;
		case 7:
			BASIC_TIM_CLK_Cmd(BASIC_TIM_7_CLK,ENABLE);
		  TIM_TimeBaseStructure.TIM_Period = Period;
		  TIM_TimeBaseStructure.TIM_Prescaler = Psc;
		  TIM_TimeBaseInit(TIM7,&TIM_TimeBaseStructure);
			TIM_ClearFlag(TIM7,TIM_FLAG_Update);
      Basic_TIM_Col(Set_DISABLE);
		  TIM_CODE.TIM_Data = TIM7;
		  TIM_CODE.NVIC_CH = TIM7_IRQn;
			break;
	}
}
/*
基本定时器中断服务函数  由用户自己定义
*/
int Basic_TIM_IRQ_Function()
{
	return 0;
}
/*
基本定时器中断控制函数
void Set_TIM_NVIC_Config(uint TIM_NUM)
                            BASIC_TIM_2/6 /7
*/
void Set_TIM_NVIC_Config(uint TIM_NUM)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
	if(TIM_NUM == 2)
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;	
	if(TIM_NUM == 3)
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;	
	if(TIM_NUM == 4)
    NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;	
	if(TIM_NUM == 5)
    NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;	
	if(TIM_NUM == 6)
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ;	
	if(TIM_NUM == 7)
		NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;	
		// 设置主优先级为 0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置抢占优先级为3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/**********通用定时器函数***********/
/*
	通用定时器初始化函数 USERSHEET
void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t,Psc,uint8_t Mode)
                              定时器          周期        分频因子     模式
TIMx              TIM2 TIM3 TIM4 TIM5
Period            计数周期
Psc               分频因子，一般为71
Mode              TIM_Mode_Up TIM_Mode_Down 
*/
void General_TIM_Config(uint8_t TIMx,uint16_t Period,uint16_t Psc,uint8_t Mode)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
		switch(Mode)
	{
		case 1:
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			break;
		case 2:
			TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;
			break;
	}
	switch(TIMx)
	{
		case 2:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM2,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM2, TIM_FLAG_Update);
			TIM_CODE.TIM_Data = TIM2;
			TIM_CODE.NVIC_CH = TIM2_IRQn;
			TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
			break;	
		case 3:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM3,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM3, TIM_FLAG_Update);
			TIM_CODE.TIM_Data = TIM3;
			TIM_CODE.NVIC_CH = TIM3_IRQn;
			TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
			break;
		case 4:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM4,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);	
			TIM_CODE.TIM_Data = TIM4;
			TIM_CODE.NVIC_CH = TIM4_IRQn;
			TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
			break;
		case 5:
			GENERAL_TIM_CLK_Cmd(RCC_APB1Periph_TIM5,ENABLE);
			TIM_TimeBaseStructure.TIM_Period = Period;
			TIM_TimeBaseStructure.TIM_Prescaler = Psc;
			TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
			TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
			TIM_ClearFlag(TIM4, TIM_FLAG_Update);
			TIM_CODE.TIM_Data = TIM5;
			TIM_CODE.NVIC_CH = TIM5_IRQn;
			TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);
			break;
	}
	Basic_TIM_Col(Set_DISABLE);
}

/*
通用定时器中断控制函数
void GENERAL_TIM_Mode_Config(void)
*/

/*******************************************/
/************通用定时器FTM模块使************/
/*FTM相关通道的改写在stm32f10x_define.h*/
/*******************************************/
/* ----------------   PWM信号 周期和占空比的计算--------------- */
// ARR ：自动重装载寄存器的值
// CLK_cnt：计数器的时钟，等于 Fck_int / (psc+1) = 72M/(psc+1)
// PWM 信号的周期 T = ARR * (1/CLK_cnt) = ARR*(PSC+1) / 72M
// 占空比P=CCR/(ARR+1)
/*
#define            GENERAL_TIM_Period            99
#define            GENERAL_TIM_Prescaler         71
*/
/*******************************************/
/*
FTM模块初始化函数
FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty)
FTMx           FTM0~FTM3
Channel        FTM0_CH1.........
frequance      单位Hz
Duty           0.1 0.2 0.36  .....
*/
void FTM_INIT(uint FTMx,uint Channel,uint Frequance,double Duty)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t GENERAL_TIM_Period;
	float CCR_Val;
	uint16_t PSC_CAL;
	uint16_t Period_CAL;
	
	Duty_Set = Duty;
	PSC_CAL = GENERAL_TIM_Prescaler+1;
	GENERAL_TIM_Period = 72000000/(Frequance*PSC_CAL);  //ARR
	Period_CAL = GENERAL_TIM_Period+1;
	/***************需要用户自己调整**********************/
	CCR_Val = (Duty)*Period_CAL;																//CRR
	/*****************************************************/
	switch(FTMx)
	{
		case 0:  //FTM0
			PSCA.PSC_DATA0 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	

					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);				
								
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM2, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
					
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);		
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
				
					// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM2, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
				
// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM2, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);			
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);		
				
// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM2, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM2, ENABLE);
					break;
			}
			break;
		case 1:   //FTM1
			PSCA.PSC_DATA1 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM5, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);
				
					break;
				case 2:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM5, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);					
					break;
				case 3:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM5, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);
					break;
				case 4:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM5, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM5, ENABLE);				
					break;
			}			
			break;
		case 2:  //FTM2
			PSCA.PSC_DATA2 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM3, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);					
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM3, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);						
					break;
				case 3:
					
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM3, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);						
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM3, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM3, ENABLE);						
					break;
			}			
			break;
		case 3:   //FTM3
			PSCA.PSC_DATA3 = Period_CAL;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC1Init(TIM4, &TIM_OCInitStructure);
					TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);	
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC2Init(TIM4, &TIM_OCInitStructure);
					TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);						
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC3Init(TIM4, &TIM_OCInitStructure);
					TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);						
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);		
			
	// 自动重装载寄存器的值，累计TIM_Period+1个频率后产生一个更新或者中断
					TIM_TimeBaseStructure.TIM_Period=GENERAL_TIM_Period;	
	// 驱动CNT计数器的时钟 = Fck_int/(psc+1)
					TIM_TimeBaseStructure.TIM_Prescaler= GENERAL_TIM_Prescaler;	
	// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
	// 计数器计数模式，设置为向上计数
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
	// 重复计数器的值，没用到不用管
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
	// 初始化定时器
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	// 配置为PWM模式1
					TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
					TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置	
					TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
				
					TIM_OCInitStructure.TIM_Pulse = CCR_Val;
					TIM_OC4Init(TIM4, &TIM_OCInitStructure);
					TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
					
					TIM_Cmd(TIM4, ENABLE);	
					break;
			}			
			break;
	}
	
}
/*
FTM控制函数
注：一般不用，要控制计数器启动和停止的时候再用
void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState)
FTMx  FTM0~3
NewState ENABLE DISABLE
*/
void FTM_COL(TIM_TypeDef* FTMx,FunctionalState NewState)
{
		TIM_Cmd(FTMx, NewState);
}

/*
设置占空比函数
void Set_Duty(uint FTMx,uint16_t channel,double duty)
FTMx  FTM0~3
channel  FTM0_CH1.......
duty	 0.1  0.2  0.63  0.15.......								
*/
void Set_Duty(uint FTMx,uint16_t channel,double duty)
{
	uint16_t Duty;
	switch(FTMx)
	{
		case 0:
			//FTM0
		Duty = duty*PSCA.PSC_DATA0;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM2,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM2,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM2,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM2,Duty);
			break;
	}
	break;
	case 1:
		//FTM1
	Duty = duty*PSCA.PSC_DATA1;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM5,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM5,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM5,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM5,Duty);
			break;
	}
	break;
	case 2:
				//FTM2
	Duty = duty*PSCA.PSC_DATA2;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM3,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM3,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM3,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM3,Duty);
			break;
	}
	break;
	case 3:
				//FTM3
	Duty = duty*PSCA.PSC_DATA3;
	switch(channel)
	{
		case 1:
			TIM_SetCompare1(TIM4,Duty);
			break;
		case 2:
			TIM_SetCompare2(TIM4,Duty);
			break;
		case 3:
			TIM_SetCompare3(TIM4,Duty);
			break;
		case 4:
			TIM_SetCompare4(TIM4,Duty);
			break;
	}
	break;
}
}
/*
FTM_IN中断设置函数
void FTM_IN_NVIC_SET(uint8_t NVIC_Source,uint32_t NVIC_GROUP,uint8_t Main_Priority,uint8_t Catch_Priority)
															中断源             中断组               主优先级               抢占优先级     
NVIC_Source     NVIC_FTM_IN0......NVIC_FTM_IN3  
NVIC_GROUP			NVIC_PriorityGroup_0
Main_Priority   0,1,2,3......
Catch_Priority  0,1,2,3......

*/
void FTM_IN_NVIC_SET(uint8_t NVIC_Source,uint32_t NVIC_GROUP,uint8_t Main_Priority,uint8_t Catch_Priority)
{
		NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_GROUP);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = NVIC_Source ;	
		// 设置主优先级为 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = Main_Priority;	 
	  // 设置抢占优先级为
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = Catch_Priority;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);	
}

/*
基本定时器输入捕获功能(单路，多路见高级定时器)
void FTM_GET_Config(uint FTM_GETx,uint Channel,uint16_t START_Edge)
FTM_GETx   FTM_IN0.......
Channel    FTM_IN0_CH1......
START_Edge   UP_Edge  FALL_Edge
*/
void FTM_GET_Config(uint FTM_GETx,uint Channel,uint16_t START_Edge)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	switch(FTM_GETx)
	{
		case 0:  //FTM0
			FTM_NVIC_SET.FTM_IN_NVIC_CH = FTM_IN0;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_15;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	
		
					FTM_IN_NVIC_SET(NVIC_FTM_IN0,NVIC_PriorityGroup_0,0,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	

				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM2, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM2, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM2, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM2, ENABLE);				
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);		
				
					FTM_IN_NVIC_SET(NVIC_FTM_IN0,NVIC_PriorityGroup_0,0,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM2, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM2, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM2, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM2, ENABLE);								
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_10;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);
				
					FTM_IN_NVIC_SET(NVIC_FTM_IN0,NVIC_PriorityGroup_0,0,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM2, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM2, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM2, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM2, ENABLE);					
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	

					FTM_IN_NVIC_SET(NVIC_FTM_IN0,NVIC_PriorityGroup_0,0,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);					
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM2, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM2, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM2, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM2, ENABLE);					
					break;
			}		
			break;
		case 1:  //FTM1
			FTM_NVIC_SET.FTM_IN_NVIC_CH = FTM_IN2;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
				
				
					   
					FTM_IN_NVIC_SET(NVIC_FTM_IN1,NVIC_PriorityGroup_0,1,3);
				
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);	

					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM5, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM5, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM5, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM5, ENABLE);					
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);

					FTM_IN_NVIC_SET(NVIC_FTM_IN1,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);					
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM5, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM5, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM5, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM5, ENABLE);					
				
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_2;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);

					FTM_IN_NVIC_SET(NVIC_FTM_IN1,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);					
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM5, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM5, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM5, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM5, ENABLE);					
				
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);	

					FTM_IN_NVIC_SET(NVIC_FTM_IN1,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);					
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM5, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM5, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM5, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM5, ENABLE);					

				
					break;
			}			
			break;
		case 2:  //FTM2
			FTM_NVIC_SET.FTM_IN_NVIC_CH = FTM_IN2;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);		

					FTM_IN_NVIC_SET(NVIC_FTM_IN2,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM3, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM3, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM3, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM3, ENABLE);					
				
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOA, &GPIO_InitStructure);

					FTM_IN_NVIC_SET(NVIC_FTM_IN2,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM3, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM3, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM3, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM3, ENABLE);					
					break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	

					FTM_IN_NVIC_SET(NVIC_FTM_IN2,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM3, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM3, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM3, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM3, ENABLE);					
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);		

					FTM_IN_NVIC_SET(NVIC_FTM_IN2,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM3, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM3, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM3, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM3, ENABLE);					
					break;
			}			
			break;
		case 3:  //FTM3
			FTM_NVIC_SET.FTM_IN_NVIC_CH = FTM_IN3;
			switch(Channel)
			{
				case 1:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	

					FTM_IN_NVIC_SET(NVIC_FTM_IN3,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM4, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM4, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM4, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM4, ENABLE);					
					break;
				case 2:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	

					FTM_IN_NVIC_SET(NVIC_FTM_IN3,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);					
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM4, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM4, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM4, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM4, ENABLE);					
			break;
				case 3:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	

					FTM_IN_NVIC_SET(NVIC_FTM_IN3,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_3;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM4, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM4, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM4, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM4, ENABLE);					
				
					break;
				case 4:
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
					GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
					GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
					FTM_IN_NVIC_SET(NVIC_FTM_IN3,NVIC_PriorityGroup_0,1,3);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);	
				
					TIM_TimeBaseStructure.TIM_Period=FTM_IN_PERIOD;	
					TIM_TimeBaseStructure.TIM_Prescaler= FTM_IN_PSC;	
						// 时钟分频因子 ，配置死区时间时需要用到
					TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;		
					TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;		
					TIM_TimeBaseStructure.TIM_RepetitionCounter=0;	
					TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
					TIM_ICInitStructure.TIM_Channel = TIM_Channel_4;
						// 输入捕获信号的极性配置
					TIM_ICInitStructure.TIM_ICPolarity = START_Edge;
						// 输入通道和捕获通道的映射关系，有直连和非直连两种
					TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
						// 输入的需要被捕获的信号的分频系数
					TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
						// 输入的需要被捕获的信号的滤波系数
					TIM_ICInitStructure.TIM_ICFilter = 0;
						// 定时器输入捕获初始化
					TIM_ICInit(TIM4, &TIM_ICInitStructure);
						// 清除更新和捕获中断标志位
					TIM_ClearFlag(TIM4, TIM_FLAG_Update|GENERAL_TIM_IT_CCx);	
						// 开启更新和捕获中断  
					TIM_ITConfig (TIM4, TIM_IT_Update | GENERAL_TIM_IT_CCx, ENABLE );
						// 使能计数器
					TIM_Cmd(TIM4, ENABLE);					
				
					break;
			}			
			break;
	}
}





/*
FTM_IN捕获功能获取函数
float FTM_GET(uint FTM_Source,uint16_t END_Edge);
FTM_Source  FTM_IN0 ......
END_Edge    UP_Edge  FALL_Edge  
*/
float FTM_GET(uint FTM_Source,uint16_t END_Edge)
{	
	
	// 当要被捕获的信号的周期大于定时器的最长定时时，定时器就会溢出，产生更新中断
	// 这个时候我们需要把这个最长的定时周期加到捕获信号的时间里面去
	switch(FTM_Source)
	{
		case 0:
		if ( TIM_GetITStatus ( TIM2, TIM_IT_Update) != RESET )               
		{	
			TIM_ICUserValueStructure.Capture_Period ++;		
			TIM_ClearITPendingBit ( TIM2, TIM_FLAG_Update ); 		
		}
		if ( TIM_GetITStatus (TIM2, GENERAL_TIM_IT_CCx ) != RESET)
	{
		// 第一次捕获
		if ( TIM_ICUserValueStructure.Capture_StartFlag == 0 )
		{
			// 计数器清0
			TIM_SetCounter ( TIM2, 0 );
			// 自动重装载寄存器更新标志清0
			TIM_ICUserValueStructure.Capture_Period = 0;
      // 存捕获比较寄存器的值的变量的值清0			
			TIM_ICUserValueStructure.Capture_CcrValue = 0;

			// 当第一次捕获到上升沿之后，就把捕获边沿配置为下降沿
			TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);
      // 开始捕获标准置1			
			TIM_ICUserValueStructure.Capture_StartFlag = 1;			
		}
		// 下降沿捕获中断
		else // 第二次捕获
		{
			// 获取捕获比较寄存器的值，这个值就是捕获到的高电平的时间的值
			TIM_ICUserValueStructure.Capture_CcrValue = 
			TIM_GetCapture1 (TIM2);

			// 当第二次捕获到下降沿之后，就把捕获边沿配置为上升沿，好开启新的一轮捕获
			TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Rising);
      // 开始捕获标志清0		
			TIM_ICUserValueStructure.Capture_StartFlag = 0;
      // 捕获完成标志置1			
			TIM_ICUserValueStructure.Capture_FinishFlag = 1;		
		}

		TIM_ClearITPendingBit (TIM2,GENERAL_TIM_IT_CCx);	  
	}
			break;
		case 1:
		if ( TIM_GetITStatus ( TIM5, TIM_IT_Update) != RESET )               
		{	
			TIM_ICUserValueStructure.Capture_Period ++;		
			TIM_ClearITPendingBit ( TIM5, TIM_FLAG_Update ); 		
		}
		if ( TIM_GetITStatus (TIM5, GENERAL_TIM_IT_CCx ) != RESET)
	{
		// 第一次捕获
		if ( TIM_ICUserValueStructure.Capture_StartFlag == 0 )
		{
			// 计数器清0
			TIM_SetCounter ( TIM5, 0 );
			// 自动重装载寄存器更新标志清0
			TIM_ICUserValueStructure.Capture_Period = 0;
      // 存捕获比较寄存器的值的变量的值清0			
			TIM_ICUserValueStructure.Capture_CcrValue = 0;

			// 当第一次捕获到上升沿之后，就把捕获边沿配置为下降沿
			TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Falling);
      // 开始捕获标准置1			
			TIM_ICUserValueStructure.Capture_StartFlag = 1;			
		}
		// 下降沿捕获中断
		else // 第二次捕获
		{
			// 获取捕获比较寄存器的值，这个值就是捕获到的高电平的时间的值
			TIM_ICUserValueStructure.Capture_CcrValue = 
			TIM_GetCapture1 (TIM5);
			// 当第二次捕获到下降沿之后，就把捕获边沿配置为上升沿，好开启新的一轮捕获
			TIM_OC1PolarityConfig(TIM5, TIM_ICPolarity_Rising);
      // 开始捕获标志清0		
			TIM_ICUserValueStructure.Capture_StartFlag = 0;
      // 捕获完成标志置1			
			TIM_ICUserValueStructure.Capture_FinishFlag = 1;		
		}

		TIM_ClearITPendingBit (TIM5,GENERAL_TIM_IT_CCx);	  
	}
			break;
		case 2:
			if ( TIM_GetITStatus ( TIM3, TIM_IT_Update) != RESET )               
		{	
			TIM_ICUserValueStructure.Capture_Period ++;		
			TIM_ClearITPendingBit ( TIM3, TIM_FLAG_Update ); 		
		}
		if ( TIM_GetITStatus (TIM3, GENERAL_TIM_IT_CCx ) != RESET)
	{
		// 第一次捕获
		if ( TIM_ICUserValueStructure.Capture_StartFlag == 0 )
		{
			// 计数器清0
			TIM_SetCounter ( TIM3, 0 );
			// 自动重装载寄存器更新标志清0
			TIM_ICUserValueStructure.Capture_Period = 0;
      // 存捕获比较寄存器的值的变量的值清0			
			TIM_ICUserValueStructure.Capture_CcrValue = 0;

			// 当第一次捕获到上升沿之后，就把捕获边沿配置为下降沿
			TIM_OC1PolarityConfig(TIM2, TIM_ICPolarity_Falling);
      // 开始捕获标准置1			
			TIM_ICUserValueStructure.Capture_StartFlag = 1;			
		}
		// 下降沿捕获中断
		else // 第二次捕获
		{
			// 获取捕获比较寄存器的值，这个值就是捕获到的高电平的时间的值
			TIM_ICUserValueStructure.Capture_CcrValue = 
			TIM_GetCapture1 (TIM3);

			// 当第二次捕获到下降沿之后，就把捕获边沿配置为上升沿，好开启新的一轮捕获
			TIM_OC1PolarityConfig(TIM3, TIM_ICPolarity_Rising);
      // 开始捕获标志清0		
			TIM_ICUserValueStructure.Capture_StartFlag = 0;
      // 捕获完成标志置1			
			TIM_ICUserValueStructure.Capture_FinishFlag = 1;		
		}

		TIM_ClearITPendingBit (TIM3,GENERAL_TIM_IT_CCx);	  
	}
			break;
		case 3:
			if ( TIM_GetITStatus ( TIM4, TIM_IT_Update) != RESET )               
		{	
			TIM_ICUserValueStructure.Capture_Period ++;		
			TIM_ClearITPendingBit ( TIM4, TIM_FLAG_Update ); 		
		}
		if ( TIM_GetITStatus (TIM4, GENERAL_TIM_IT_CCx ) != RESET)
	{
		// 第一次捕获
		if ( TIM_ICUserValueStructure.Capture_StartFlag == 0 )
		{
			// 计数器清0
			TIM_SetCounter ( TIM4, 0 );
			// 自动重装载寄存器更新标志清0
			TIM_ICUserValueStructure.Capture_Period = 0;
      // 存捕获比较寄存器的值的变量的值清0			
			TIM_ICUserValueStructure.Capture_CcrValue = 0;

			// 当第一次捕获到上升沿之后，就把捕获边沿配置为下降沿
			TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Falling);
      // 开始捕获标准置1			
			TIM_ICUserValueStructure.Capture_StartFlag = 1;			
		}
		// 下降沿捕获中断
		else // 第二次捕获
		{
			// 获取捕获比较寄存器的值，这个值就是捕获到的高电平的时间的值
			TIM_ICUserValueStructure.Capture_CcrValue = 
			TIM_GetCapture1 (TIM4);

			// 当第二次捕获到下降沿之后，就把捕获边沿配置为上升沿，好开启新的一轮捕获
			TIM_OC1PolarityConfig(TIM4, TIM_ICPolarity_Rising);
      // 开始捕获标志清0		
			TIM_ICUserValueStructure.Capture_StartFlag = 0;
      // 捕获完成标志置1			
			TIM_ICUserValueStructure.Capture_FinishFlag = 1;		
		}

		TIM_ClearITPendingBit (TIM4,GENERAL_TIM_IT_CCx);	  
	}
			break;
	}
	
	
	
return 0;
}

/*
	FTM捕获数据获得函数
*/
uint32_t FTM_Time_Transfer()
{
	uint32_t t;
	uint32_t Time;
		if(TIM_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// 计算高电平时间的计数器的值
			Time = TIM_ICUserValueStructure.Capture_Period * (FTM_IN_PERIOD+1) + 
			       (TIM_ICUserValueStructure.Capture_CcrValue+1);	
			//printf("time=%dus\n",Time);
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;			
		}	
			t=Time;
	return t;
}
