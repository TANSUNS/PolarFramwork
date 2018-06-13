#ifndef __POLAR_1602_H__
#define __POLAR_1602_H__
#include "Polar.h"

#define LCD1602_Port GPIOB

/** 定义1602对象定义 */ 
typedef struct
{

    GPIO_TypeDef *Port; //1602端口
    uint16_t RS;  //RS端口
    uint16_t RW;  //读写端口
    uint16_t E;   //使能端口

    uint16_t D0;
    uint16_t D1;
    uint16_t D2;
    uint16_t D3;
    uint16_t D4;
    uint16_t D5;
    uint16_t D6;
    uint16_t D7;
    
}LCD_1602Obj;

/** 定义1602 命令组  */ 
#define ONELINE_5_8_ 0x30  ///<单行5X8显示
#define ONELINE_5_10_ 0x34 ///< 单行5X10显示
#define DOUBLELINE_5_8_ 0x38 ///< 双行5X8显示
#define DOUBLELINE_5_10_ 0x3C ///< 双行5X10

#define OPENLCD 0x0C ///< 开启LCD
#define CLOSELCD 0x08 /// < 关闭LCD
#define OPENCURSOR 0x0A /// < 打开光标
#define CLOSECURSOR 0x08 /// <关闭光标
#define CURSORFLASH 0x09 ///< 光标闪烁
#define CURSORNOTFLASH 0x08 ///<光标不闪烁

#define MOVE_RIGHT 0x07 ///< 光标右移动滚动
#define MOVE_RIGHT 0x06 ///< 光标右移动不滚动


#define CLEARDISPLAY 0x01 ///<清频率

#define  FIRST 0x80
#define  SECOND 0x80+0x40



/** 定义1602 Fast函数组  */ 

/** 定义1602API  */ 
extern uint8_t LCD1602_Init(LCD_1602Obj *LCD); //初始化1602管脚

extern  void WriteCom(LCD_1602Obj *LCD,uint8_t *ComGrp); //按组写入命令
static uint8_t LCDRead(LCD_1602Obj *LCD,uint8_t Mode);//读取1602的数据

extern void LCD1602_Display(LCD_1602Obj *LCD,uint8_t *Data);//在1602上显示数据
extern void ClearAll(LCD_1602Obj *LCD);//清屏



#endif 