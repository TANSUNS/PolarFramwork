// Designed By TANSUNS//
//General Filter(FLOATING)//
//2018.5.15    Version 1.2


#ifndef __FILTER_H__
#define __FILTER_H__
#include "stdint.h"
#define DFT_T float   //Setting the default type of this Algorithms
extern DFT_T ABS(DFT_T NUM);

//Range Security 范围保护
typedef struct
{
    DFT_T UppLmt;//upperLimit
    DFT_T LwrLmt;//lowerLimit
    DFT_T LstVl;//LastValue
    DFT_T Output;

}RgSecrObj;

//APIS

extern uint8_t RangeSecureInit(RgSecrObj *p, DFT_T Up, DFT_T Low);
extern DFT_T RangeSecure_I(RgSecrObj *p,DFT_T CrtVal);
extern DFT_T RangeSecure_II(RgSecrObj *p,DFT_T CrtVal);


//Limiting filter  限幅滤波器 能有效克服因偶然因素引起的脉冲干扰但对快速变化的量无法保证，建议低速选择
typedef struct
{
    DFT_T LstVl; // LastValue
    DFT_T Error;  //Error
    DFT_T Output;
    DFT_T FstFlg; //是否是第一次的标志位
}LimFilterObj;

//APIS
extern uint8_t LimFilterInit(LimFilterObj *p,DFT_T Error);
extern DFT_T LimFilter(LimFilterObj *p,DFT_T CrtVal);

//Sliding average filter I 
//I类滑动平均滤波 适用于采样速度较慢或要求数据更新率较高的实时系统
 //对周期性干扰有良好的抑制作用，平滑度高；
 //   适用于高频振荡的系统。
 //   灵敏度低，对偶然出现的脉冲性干扰的抑制作用较差；
 //   不易消除由于脉冲干扰所引起的采样值偏差；
  //  不适用于脉冲干扰比较严重的场合；

//II类加权平均滤波
//给予新采样值的权系数越大，则灵敏度越高，但信号平滑度越低。
//   适用于有较大纯滞后时间常数的对象，和采样周期较短的系统。
//   对于纯滞后时间常数较小、采样周期较长、变化缓慢的信号；
//   不能迅速反应系统当前所受干扰的严重程度，滤波效果差。


typedef struct
{
    int N;//滤波器的特征值N
    DFT_T *Filter_buf;//指向滤波器滤波数据的指针
    DFT_T Output;
    int *Coe; //加权系数表
    DFT_T SumCoe;//加权系数和

}SldAvrgFilterObj;

//APIS
extern uint8_t SldAvrgFilter_I_Init(SldAvrgFilterObj *p,int N);
extern uint8_t SldAvrgFilter_II_Init(SldAvrgFilterObj *p,int N,int *C);
extern DFT_T SldAvrgFilter_I(SldAvrgFilterObj *p,DFT_T CrtVal);
extern DFT_T SldAvrgFilter_II(SldAvrgFilterObj *p,DFT_T CrtVal);

//median-value filter 防脉冲干扰平均滤波法
//融合了“中位值滤波法”+“算术平均滤波法”两种滤波法的优点。
//    对于偶然出现的脉冲性干扰，可消除由其所引起的采样值偏差。
//    对周期干扰有良好的抑制作用。
//    平滑度高，适于高频振荡的系统。
//    计算速度较慢，和算术平均滤波法一样。

typedef struct
{
    int N;
    DFT_T *Filter_buf;
    DFT_T Output;

}MVFilterObj;


extern uint8_t MVFilterInit(MVFilterObj *p,int N);
extern DFT_T MVfilter(MVFilterObj *p,DFT_T *CrtVal);

#endif