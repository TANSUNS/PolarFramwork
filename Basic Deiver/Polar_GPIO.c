#include "stm32f10x.h"
#include "Polar_GPIO.h"
#include "PeriphDef.h"
#define uint unsigned int
	
/*具体的细节定义见stm32f10x_define.h*/

#define digitalToggle(p,i) {p->ODR ^=i;} //输出反转状态

//data resister order to review the set before

GPIO_CFG GPIO_CON;
/*
	GPIO初始化函数 USER SHEET
	int GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t Speed,uint8_t mode,uint8_t CLK)
                            端口         引脚          速度         模式       时钟线
//端口号  GPIOx  GPIOA GPIOB ~~~
//引脚号   pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//模式    1  模拟输入  2  浮空输入  3  下拉输入    4  上拉输出   5  开漏输出   6  推挽输出   7  复用开漏输出  8  复用推挽输出
//速度    LOW_Speed                    2MHz
          MID_Speed                   10MHz
          HIGH_Speed                  50MHz
*/
int GPIO_INIT(GPIO_TypeDef* GPIOx,uint16_t pin,uint8_t Speed,uint8_t mode)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	
	switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
		  GPIO_CON.GPIO_PIN = GPIO_Pin_1;
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
		  GPIO_CON.GPIO_PIN = GPIO_Pin_2;
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
		  GPIO_CON.GPIO_PIN = GPIO_Pin_3;
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_4;
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_5;
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_6;
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_7;
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_8;
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_9;
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_10;
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_11;
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			GPIO_CON.GPIO_PIN = GPIO_Pin_12;
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_13;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_14;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_15;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			GPIO_CON.GPIO_PIN = GPIO_Pin_0;
			break;
	};
	
	switch(Speed)
	{
			case 10:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_10MHz;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_2MHz;
			break;
			case 50:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_50MHz;
			break;
	};	
	
	switch(mode)
	{
			case 1:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;// 模拟输入
			GPIO_CON.GPIO_Mode = GPIO_Mode_AIN;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;// 浮空输入
			GPIO_CON.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			break;
			case 3:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;// 下拉输入
			GPIO_CON.GPIO_Mode = GPIO_Mode_Out_OD;
			break;
			case 4:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPU;	// 上拉输入
			GPIO_CON.GPIO_Mode = GPIO_Mode_IPU;
			break;
			case 5:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;	// 开漏输出
			GPIO_CON.GPIO_Mode = GPIO_Mode_Out_OD;
			break;
			case 6:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;// 推挽输出
			GPIO_CON.GPIO_Mode = GPIO_Mode_Out_PP;
			break;
			case 7:
			GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_OD;// 复用开漏输出
			GPIO_CON.GPIO_Mode = GPIO_Mode_AF_OD;
			break;
			case 8:
			GPIO_InitStructure.GPIO_Mode  =  GPIO_Mode_AF_PP;// 复用推挽输出
			GPIO_CON.GPIO_Mode = GPIO_Mode_AF_PP;
			break;
		};
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	return 0;
	 
 }
 /*
PORT快速输出初始化函数 USER SHEET
 int Fast_OutputSet(GPIO_TypeDef* GPIOx,uint pin)
                         端口          引脚
//端口号 GPIOx  GPIOA GPIOB ~~~
//引脚号  pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//快速设置为50MHz推挽
*/
int Fast_OutputSet(GPIO_TypeDef* GPIOx,uint8_t pin)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //推挽模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			break;
	};
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	
	return 0;
}
 /*
PORT快速输入初始化函数 USER SHEET
Fast_InputSet(GPIO_TypeDef* GPIOx,uint pin,uint Speed)
                           端口      引脚      速度
//端口号  GPIOx  GPIOA GPIOB ~~~
//引脚号  pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//速度    LOW_Speed                    2MHz
          MID_Speed                   10MHz
          HIGH_Speed                  50MHz
*/
int Fast_InputSet(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t Speed)
{
	GPIO_InitTypeDef GPIO_InitStructure;   //Define a struct about gpio init
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入
		 switch(Speed)
	{
			case 10:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_10MHz;
			break;
			case 2:
			GPIO_InitStructure.GPIO_Speed= GPIO_Speed_2MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_2MHz;
			break;
			case 50:
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
			GPIO_CON.GPIO_Speed = GPIO_Speed_50MHz;
			break;
	};
		switch(pin)
	{
		case 1:   
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 ; 
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ; 
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ; 
			break;
		case 4:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 ; 
			break;
		case 5:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 ; 
			break;
		case 6:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 ; 
			break;
	  case 7:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 ; 
			break;
		case 8:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ; 
			break;
		case 9:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ; 
			break;
		case 10:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ; 
			break;
		case 11:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 ; 
			break;
		case 12:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 ; 
			break;
		case 13:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
			break;
		case 14:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 ;
			break;
		case 15:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 ;
			break;
	  case 0:
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 ;
			break;
	};
	
	GPIO_Init(GPIOx, &GPIO_InitStructure);
	return 0;
}
 /*
PORT快速输入初始化函数 USER SHEET
Change_Port_Mode(GPIO_TypeDef* GPIOx,uint pin,uint mode,uint Speed)
                             端口      引脚       模式        速度
//端口号  GPIOx  GPIOA GPIOB ~~~
//引脚号  pin0  GPIO_Pin_0   pin1  GPIO_Pin_1  pin2  GPIO_Pin_2  ~~~~~~    pin15  GPIO_Pin_15
//速度    LOW_Speed                    2MHz
          MID_Speed                   10MHz
          HIGH_Speed                  50MHz
//模式  1  模拟输入  2  浮空输入  3  下拉输入    4  上拉输出   5  开漏输出   6  推挽输出   7  复用开漏输出  8  复用推挽输出
*/
int Change_Port_Mode(GPIO_TypeDef* GPIOx,uint8_t pin,uint8_t mode,uint8_t Speed)
{
  GPIO_INIT(GPIOx,pin,Speed,mode);
	return 0;
}
 /*
端口静默函数 断开端口时钟 USER SHEET
Cut_PIN_CLK(uint port)
               端口            
//端口号  GPIOA_SET GPIOA   GPIOB_SET GPIOB  GPIOC_SET  GPIOC  GPIOD_SET  GPIOD  GPIOE_SET  GPIOE   GPIOF_SET  GPIOF  GPIOG_SET  GPIOG
*/
int Cut_PIN_CLK(uint8_t port)
{
	switch(port)
	{
		case 1:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,ENABLE);
			break;
		case 2:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,ENABLE);
			break;
		case 3:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,ENABLE);
			break;
		case 4:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD,ENABLE);
			break;
		case 5:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE,ENABLE);
			break;
		case 6:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF,ENABLE);
			break;
		case 7:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG,ENABLE);
			break;
	};
	return 0;
}
 /*
解除端口静默函数 重连端口时钟 USER SHEET
Reconnect_PIN_CLK(uint port)
                   端口            
//端口号  GPIOA_SET GPIOA   GPIOB_SET GPIOB  GPIOC_SET  GPIOC  GPIOD_SET  GPIOD  GPIOE_SET  GPIOE   GPIOF_SET  GPIOF  GPIOG_SET  GPIOG
//使用先决条件 调用 Cut_PIN_CLK(uint port) 之后
*/
int Reconnect_PIN_CLK(uint8_t port)
{
		switch(port)
	{
		case 1:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOA,DISABLE);
			break;
		case 2:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOB,DISABLE);
			break;
		case 3:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOC,DISABLE);
			break;
		case 4:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOD,DISABLE);
			break;
		case 5:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOE,DISABLE);
			break;
		case 6:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOF,DISABLE);
			break;
		case 7:
			RCC_APB2PeriphResetCmd(RCC_APB2Periph_GPIOG,DISABLE);
			break;
	};
	return 0;
}
 /*
输出高低电平数据 USER SHEET
GPIO_OUT(uint port,uint pin,uint data)
              端口     引脚    高低电平   
//端口号  port  GPIOA\GPIOB\GPIOC\GPIOD~~
//引脚号  pin  GPIO_Pin_0 GPIO_Pin_1 GPIO_Pin_2 GPIO_Pin_3~~~
//高低电平 (data) Bit_SET 1;Bit_RESET 0;
//使用先决条件 调用初始化端口之后
*/
int GPIO_OUT(GPIO_TypeDef* port,uint16_t pin,BitAction data)
{
GPIO_WriteBit(port,pin, data);
	return 0;
}
 /*
读取输入高低电平数据 USER SHEET
GPIO_READ(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
                 端口              引脚      
//端口号  GPIOx  GPIOA\GPIOB\GPIOC\GPIOD~~
//引脚号  GPIO_Pin  GPIO_Pin_0 GPIO_Pin_1 GPIO_Pin_2 GPIO_Pin_3~~~
//使用先决条件 调用初始化端口之后
*/
uint8_t GPIO_READ(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{
	uint8_t Read_data;
	Read_data = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	return Read_data;
}
 /*
端口组输出数据(可以为16进制) USER SHEET
GPIO_Write_Port(GPIO_TypeDef* GPIOx,u16 Val)
                      端口          输出值
//端口号  GPIOx  GPIOA\GPIOB\GPIOC\GPIOD~~
//输出值  Val  0x02~~
//使用先决条件 调用初始化端口之后
*/
void GPIO_Write_Port(GPIO_TypeDef* GPIOx,u16 Val)
{
	GPIO_Write(GPIOx,Val);
}
 /*
读取端口数据(16位) USER SHEET
GPIO_Read_Port(GPIO_TypeDef* GPIOx)
                      端口         
//端口号  GPIOx  GPIOA\GPIOB\GPIOC\GPIOD~~
//使用先决条件 调用初始化端口之后
*/
u16 GPIO_Read_Port(GPIO_TypeDef* GPIOx)
{
	u16 Read_Val;
	Read_Val = GPIO_ReadInputData(GPIOx);
	return Read_Val;
}
 /*
时钟挂载函数 USER SHEET
CLK_SET(uint GPIOX);
                      端口         
//端口号  GPIOX  GPIOA_SET\GPIOB_SET\GPIOC_SET\GPIOD_SET~~
*/
void CLK_SET(uint8_t GPIOX)
{
	switch(GPIOX)
	{
		case 1:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		break;
		case 2:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		break;
		case 3:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
		break;
		case 4:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
		break;
		case 5:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
		break;
	  case 6:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);
		break;
		case 7:
	      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);
		break;
	}
}
/*
输出反转函数
OUT_TOGGLE(GPIO_TypeDef* GPIOx,uint16_t pin)
                  端口            引脚
GPIOx GPIOA GPIOB......
pin   Pin0 Pin1 Pin2 ......
*/
void OUT_TOGGLE(GPIO_TypeDef* GPIOx,uint16_t pin)
{
	switch(pin)
	{
		case 0:
			digitalToggle(GPIOx,GPIO_Pin_0);
			break;
		case 1:
			digitalToggle(GPIOx,GPIO_Pin_1);
			break;
		case 2:
			digitalToggle(GPIOx,GPIO_Pin_2);
			break;
	  case 3:
			digitalToggle(GPIOx,GPIO_Pin_3);
			break;
	  case 4:
			digitalToggle(GPIOx,GPIO_Pin_4);
			break;
		case 5:
			digitalToggle(GPIOx,GPIO_Pin_5);
			break;
		case 6:
			digitalToggle(GPIOx,GPIO_Pin_6);
			break;
		case 7:
			digitalToggle(GPIOx,GPIO_Pin_7);
			break;
		case 8:
			digitalToggle(GPIOx,GPIO_Pin_8);
			break;
		case 9:
			digitalToggle(GPIOx,GPIO_Pin_9);
			break;
	  case 10:
			digitalToggle(GPIOx,GPIO_Pin_10);
			break;
	  case 11:
			digitalToggle(GPIOx,GPIO_Pin_11);
			break;
		case 12:
			digitalToggle(GPIOx,GPIO_Pin_12);
			break;
		case 13:
			digitalToggle(GPIOx,GPIO_Pin_13);
			break;
		case 14:
			digitalToggle(GPIOx,GPIO_Pin_14);
			break;
		case 15:
			digitalToggle(GPIOx,GPIO_Pin_15);
			break;
	}
}