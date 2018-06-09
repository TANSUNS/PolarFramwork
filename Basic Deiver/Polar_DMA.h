#ifndef __POLAR_DMA_H__
#define __POLAR_DMA_H__
#include "stdint.h"
#include "stm32f10x.h"

/**函数返回状态定义*/
#define OK (uint8_t) 1
#define NOTOK (uint8_t)0

/** 定义外设的DMA使用的通道 */  
/** 定义DMA1 CHANNEL1使用的通道 */  
#define ADC_1 DMA1_Channel1
#define TIM2_CH3 DMA1_Channel1
#define TIM4_CH1 DMA1_Channel1

/** 定义DMA1 CHANNEL2使用的通道 */  
#define SPI1_RX DMA1_Channel2
#define USART3_TX DMA1_Channel2
#define TIM1_CH1 DMA1_Channel2
#define TIM2_UP DMA1_Channel2
#define TIM3_CH3 DMA1_Channel2

/** 定义DMA1 CHANNEL3使用的通道 */ 
#define SPI1_TX DMA1_Channel3
#define USART3_RX DMA1_Channel3
#define TIM1_CH2 DMA1_Channel3
#define TIM3_CH4 DMA1_Channel3
#define TIM3_UP DMA1_Channel3

/** 定义DMA1 CHANNEL4使用的通道 */ 
#define SPI_AND_I2S2_RX DMA1_Channel4
#define USART1_TX DMA1_Channel4
#define I2C2_TX DMA1_Channel4
#define TIM1_TX4 DMA1_Channel4
#define TIM1_TRIG DMA1_Channel4
#define TIM1_COM DMA1_Channel4
#define TIM4_CH2 DMA1_Channel4

/** 定义DMA1 CHANNE5使用的通道 */ 
#define SPI_AND_I2S2_TX DMA1_Channel5
#define USART1_RX DMA1_Channel5
#define I2C2_RX DMA1_Channel5
#define TIM1_UP DMA1_Channel5
#define TIM2_CH1 DMA1_Channel5
#define TIM4_CH3 DMA1_Channel5

/** 定义DMA1 CHANNE6使用的通道 */ 
#define USART2_RX DMA1_Channel6
#define I2C1_TX DMA1_Channel6
#define TIM1_CH3 DMA1_Channel6
#define TIM3_CH1 DMA1_Channel6
#define TIM3_TRIG DMA1_Channel6

/** 定义DMA1 CHANNE7使用的通道 */ 
#define USART2_TX DMA1_Channel7
#define I2C1_RX DMA1_Channel7
#define TIM2_CH2 DMA1_Channel7
#define TIM2_CH4 DMA1_Channel7
#define TIM4_UP DMA1_Channel7

/** 定义DMA2 CHANNE1使用的通道 */ 
#define SPI_AND_I2S3_RX DMA2_Channel1
#define TIM5_CH4 DMA2_Channel1
#define TIM5_TRIG DMA2_Channel1
#define TIM8_CH3 DMA2_Channel1
#define TIM8_UP DMA2_Channel1

/** 定义DMA2 CHANNE2使用的通道 */ 
#define SPI_AND_I2S3_tX DMA2_Channel2
#define TIM5_CH3 DMA2_Channel2
#define TIM5_UP DMA2_Channel2
#define TIM8_CH4 DMA2_Channel2
#define TIM8_TRIG DMA2_Channel2
#define TIM8_COM DMA2_Channel2

/** 定义DMA2 CHANNE3使用的通道 */ 
#define USART4_RX DMA2_Channel3
#define TIM6_UP_AND_DAC_CH1 DMA2_Channel3
#define TIM8_CH1 DMA2_Channel3

/** 定义DMA2 CHANNE4使用的通道 */ 
#define SDIO_ DMA2_Channel4
#define TIM5_CH2 DMA2_Channel4
#define TIM7_UP_AND_DAC_CH2 DMA2_Channel4

/** 定义DMA2 CHANNE5使用的通道 */ 
#define ADC_3 DMA2_Channel5
#define USART4_TX DMA2_Channel5
#define TIM5_CH1 DMA2_Channel5
#define TIM8_CH2 DMA2_Channel5

/** 定义常用外设地址 */ 
#define ADC1_Data_Address (uint32_t)&ADC1->DR///< ADC1数据地址
#define ADC2_Data_Address (uint32_t)&ADC2->DR///< ADC2数据地址
#define ADC3_Data_Address (uint32_t)&ADC3->DR///< ADC3数据地址
#define USART1_Data_Address (uint32_t)&USART1->DR///< USART1数据地址
#define USART2_Data_Address (uint32_t)&USART2->DR///< USART2数据地址
#define DAC1_8bit_Data_Address (uint32_t)&DAC1->DHR8R1///< DAC1 8位数据地址
#define DAC1_12bit_Data_Address (uint32_t)&DAC2->DHR12R1///<DAC1 12位数据地址
#define DAC2_8bit_Data_Address (uint32_t)&DAC1->DHR8R2///< DAC2 8位数据地址
#define DAC2_12bit_Data_Address (uint32_t)&DAC2->DHR12R2///<DAC2 12位数据地址


/** 定义缺省快捷函数 */ 

#define MEMDEFAULTCHANNAL DMA1_Channel1  ///< 定义数据传输的默认通道 

#define Fast_Mem_ByteDataTransfer(a,b)  Mem_ByteDataTransfer(a,b,MEMDEFAULTCHANNAL) 
#define Fast_Mem_HalfWordDataTransfer(a,b) Mem_HalfWordDataTransfer(a,b,MEMDEFAULTCHANNAL)
#define  Fast_Mem_WordDataTransfer(a,b)     Mem_WordDataTransfer(a,b,MEMDEFAULTCHANNAL)
//#define  Circle_DMA_INIT(a,b,c,d,e,f,g,h)  DMA_INIT(uint32_t Channel,uint32_t DataNum,uint32_t DesAdr,uint32_t DesByte,uint32_t SrcAdr,uint32_t SrcByte,Who_To_Who Way,uint8_t CircleFlag);

/** 定义数据单位 */ 
#define Bytes (uint32_t)8 ///< 8位数据
#define HalfWords (uint32_t)16///< 16位数据 
#define Words (uint32_t)32 ///< 32位数据 

/** 定义循环标志 */ 
#define Circle (uint8_t)1
#define Onece  (uint8_t)0

/** 定义地址指针是否增加类型 */ 
#define Inc (uint8_t)1
#define Hold (uint8_t)0

/** 定义中断类型 */ 
#define AfterFinish (uint32_t)0
#define WhenWrong (uint32_t)1

/** 定义中断类型 */
#define MostLevel (uint8_t)0 
#define HighLevel (uint8_t)1
#define MediumLevel (uint8_t)2
#define LowLevel (uint8_t)3

/** 
 * 传输方向的参数
 * MEMTOMEM  储存器到储存器
 * PERIPHTOMEM 外设到储存器
 * MEMTOPERIPH 储存器到外设
 */  
typedef enum {MEMTOMEM,PERIPHTOMEM,MEMTOPERIPH}Who_To_Who;

extern uint8_t DMA_INIT(DMA_Channel_TypeDef *Channel,uint8_t Level,uint32_t DataNum,uint32_t PeriAdr,uint32_t PeriByte,uint8_t PeriInc,uint32_t MemAdr,uint32_t MemByte,uint8_t MemInc,Who_To_Who Way,uint8_t CircleFlag);

static void PeriphDMAInit(void);         //外设响应允许通道
extern void CloseDMA(DMA_Channel_TypeDef *Channel);  //关闭DMA通道
extern void OpenDMA(DMA_Channel_TypeDef *Channel);  //打开DMA通道/软件触发
extern void Start_DMA_Convers(DMA_Channel_TypeDef *Channel,uint16_t DataSize);  //一次传递后重启下一次

extern uint8_t DMAIsFinish(DMA_Channel_TypeDef *Channel);//判断传输是否完成
extern uint8_t Mem_ByteDataTransfer(uint8_t *Src,uint8_t *Des,DMA_Channel_TypeDef *Channel); //8位数据传输
extern uint8_t Mem_HalfWordDataTransfer(uint16_t *Src,uint16_t *Des,DMA_Channel_TypeDef *Channel); //16位数据传输
extern uint8_t Mem_WordDataTransfer(uint32_t *Src,uint32_t *Des,DMA_Channel_TypeDef *Channel);//32位数据传输

extern uint8_t DMA_IT_Config(DMA_Channel_TypeDef *Channel,uint32_t WichType); //允许DMA中断，只能被IT组件调用
extern uint8_t Clear_DMA_IT_Flag(DMA_Channel_TypeDef *Channel);  //清除中断FLAG函数，
#endif