#include <stm32f10x.h>
#include "IncludeList.h"
//需要添加滤波器系数的头文件

#ifndef __FIR_FILTER_H__
#define __FIR_FILTER_H__

extern uint8_t FastLowPassFR(float32_t *Src,float32_t *Des,float32_t *firCoeffs32); 
#endif