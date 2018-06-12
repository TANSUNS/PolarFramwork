/** 
* @file         Polar_SPI.h
* @brief       SPI总线组件
* @details    该部分包含SPI总线的使用
* @author       唐俊 
* @date     2018/6/5 
* @version  1.0 
* @par Copyright (c):  
*       Advanced Studios 
* @par History:          
*   version: 唐俊, 6/5, 1.0\n 
*/


#ifndef __POLAR_SPI_H__
#define __POLAR_SPI_H__
#include "stdint.h"
#include "IncludeList.h"
/** 定义SPI函数状态 */
#define OK (uint8_t)1
#define NOTOK (uint8_t)0


/** 定义SPI的工作模式 */ 
#define  SPIMode0 (uint8_t)0 ///< SPI工作在模式0
#define  SPIMode1 (uint8_t)1 ///< SPI工作在模式1
#define  SPIMode2 (uint8_t)2 ///< SPI工作在模式2
#define  SPIMode3 (uint8_t)3 ///< SPI工作在模式3

/** 定义SPI的工作方向*/ 
#define Master (uint8_t)1 ///< 作为SPI主机
#define Slave  (uint8_t)2 ///<作为SPI从机

/** 定义SPI的工作数据*/ 

#define Bytes (uint8_t)8///< 8位数据
#define HalfWords (uint8_t)16///< 16位数据

/** 定义SPI的选定方式*/ 
#define AotoNss (uint8_t)0  ///< SPI自动分配NSS
#define ManualNss (uint8_t)0  ///< SPI手动分配NSS

/** 定义SPI的先行方式*/ 
#define MSB (uint8_t)0  ///< 最高位先行
#define LSB (uint8_t)1  ///< 最低位先行

/** 定义SPI的通道*/ 
 #define SPI1_Port GPIOA
 #define SPI2_Port GPIOB
#define SPI_Channel0 GPIO_Pin_0
#define SPI_Channel1 GPIO_Pin_1
#define SPI_Channel2 GPIO_Pin_2
#define SPI_Channel3 GPIO_Pin_3
#define SPI_Channel4 GPIO_Pin_4
#define SPI_Channel5 GPIO_Pin_5
#define SPI_Channel6 GPIO_Pin_6
#define SPI_Channel7 GPIO_Pin_7
#define SPI_Channel8 GPIO_Pin_8
#define SPI_Channel9 GPIO_Pin_9
#define SPI_Channel10 GPIO_Pin_10
#define SPI_Channel11 GPIO_Pin_11
#define SPI_Channel12 GPIO_Pin_12
#define SPI_Channel13 GPIO_Pin_13
#define SPI_Channel14 GPIO_Pin_14
#define SPI_Channel15 GPIO_Pin_15

/** 定义SPI标志位*/ 
#define ReadyToSend  SPI_FLAG_TXE
#define ReadyToGet SPI_FLAG_RXNE


/** 定义SPI快速设置函数和相关参数,FAST系列函数*/ 

#define DefaultSpeedPrescare (uint8_t)2 ///< SPI工作在2分频模式
#define DefaultFirstBit MSB

#define Fast_SPI_INIT_Byte(SPIX,SPIMODEX,MODE,CHANNEL)  SPI_INIT(SPIX,CHANNEL,MODE,Bytes,SPIMODEX,AotoNss,DefaultSpeedPrescare,DefaultFirstBit)///< SPI8位模式
#define Fast_SPI_INIT_HalfWord(SPIX,SPIMODEX,MODE,CHANNEL)  SPI_INIT(SPIX,CHANNEL,MODE,HalfWords,SPIMODEX,AotoNss,DefaultSpeedPrescare,DefaultFirstBit)///< SPI8位模式

/** 定义SPI API*/ 
extern uint8_t SPI_INIT(SPI_TypeDef* SPIx,uint16_t Channel,uint8_t Mode,uint8_t DataByte,uint8_t SPIModex,uint8_t Nss,uint8_t Speed,uint8_t FirstBit);///< SPI设置函数
extern uint8_t SPI_NSS_Register(GPIO_TypeDef *GPIOx,uint16_t Channel); ///< 注册通道
static void Select_Channel(SPI_TypeDef* SPIx,uint16_t Channel); ///< 选通通道
static void Release_Channel(SPI_TypeDef* SPIx,uint16_t Channel); ///< 关闭通道
extern uint8_t SPISendByteData(SPI_TypeDef* SPIx,uint8_t *Data,uint16_t Channel);///< 传送8位数据
extern uint8_t SPISendHalfWordData(SPI_TypeDef* SPIx,uint16_t *Data,uint16_t Channel);///< 传送16位数据
extern uint8_t SPIGetByteData(SPI_TypeDef* SPIx,uint8_t *Buffer,uint16_t Channel);///<获得8位数据
extern uint8_t SPISend_Get(SPI_TypeDef* SPIx,uint16_t Channel,uint16_t *Data,uint16_t *Buffer);///<同时获得获得和传输16位数据
extern uint8_t SPIGetHalfDate(SPI_TypeDef* SPIx,uint16_t *Buffer,uint16_t Channel);///< 获得16位数据
extern void CloseSPI(SPI_TypeDef* SPIx);///<关闭SPI总线
extern void OpenSPI(SPI_TypeDef* SPIx);///<开启SPI总线 

///** 保留SPI API，用于PolarAoto组件，移交外设控制权限*/ 
static *PeriphObj CreatAotoList(void);//向Polar管理策略组申请SPI外设控制对象
static uint8_t  ApplyPolarAoto(SPI_TypeDef* SPIx);//申请Polar自动对齐唤醒,控制权限移交PolarAoto控制器
static uint8_t  CancelPolarAoto(SPI_TypeDef* SPIx);//取消Polar自动对齐唤醒，控制权限移交用户
static uint8_t SPISilence((SPI_TypeDef* SPIx);//外设静默，取消使能并向PolarKernel注销


/** 定义中断注册函数*/ 
extern uint8_t SPI_IT_Config(void);
extern uint8_t GetSPIFlag(uint8_t Flag);
extern void ClearSPIFlag(uint8_t Flag);

#endif