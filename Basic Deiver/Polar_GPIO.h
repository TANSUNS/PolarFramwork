#ifdef __POLAR_GPIO_H__
#define __POLAR_GPIO_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#define uint unsigned int
#define uchar unsigned char
	

//参数定义

//返回变量声明


//函数声明
extern int GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t Speed,uint8_t mode);  //GPIO模式初始化函数
extern int PORT_INIT(GPIO_TypeDef* GPIOx,uint8_t speed,uint8_t mode);  //一组端口初始化函数
extern int Fast_OutputSet(GPIO_TypeDef* GPIOx,uint8_t pin);//快速输出初始化，默认配置为浮空输入
extern int Fast_InputSet(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t Speed);//快速输入初始化，默认配置为浮空输入，速度自定
extern int Change_Port_Mode(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t mode,uint8_t Speed);//端口参数改变 改变端口，引脚，模式，速度
extern int Cut_PIN_CLK(uint8_t port);//端口静默，断开端口时钟
extern int Reconnect_PIN_CLK(uint8_t port);//解除端口静默
extern int GPIO_OUT(GPIO_TypeDef* port,uint16_t pin,BitAction data);//输出高低电平数据
extern uint8_t GPIO_READ(GPIO_TypeDef* GPIOx,u16 GPIO_Pin);//读取输入的高低电平
extern void GPIO_Write_Port(GPIO_TypeDef* GPIOx,u16 Val);//向端口组输出数据，可以为16进制
extern u16 GPIO_Read_Port(GPIO_TypeDef* GPIOx);//读取端口组十六位数据并返回
extern void CLK_SET(uint8_t GPIOX);//时钟挂载
extern void OUT_TOGGLE(GPIO_TypeDef* GPIOx,uint16_t pin);//输出反转
#endif