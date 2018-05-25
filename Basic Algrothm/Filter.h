// Designed By TANSUNS//
//General Filter(FLOATING)//
//2018.5.15    Version 1.2


#ifdef __FILTER_H__
#define __FILTER_H__
#include <stdlib.h>

#define DFT_T float   //Setting the default type of this Algorithms

//COM 
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
extern DFT_T LimFilter(LimFilterObj *p,DFT_T CrtVal);]

//Sliding average filter I I类滑动平均滤波 适用于采样速度较慢或要求数据更新率较高的实时系统


typedef struct
{
    int N;//滤波器的特征值N
    DFT_T *Filter_buf;//指向滤波器滤波数据的指针
    DFT_T Output;
}SldAvrgFilterObj;

//APIS
extern uint8_t SldAvrgFilterInit(SldAvrgFilterObj *p,int N);
extern DFT_T SldAvrgFilter(SldAvrgFilterObj *P,DFT_T CrtVal);





#endif