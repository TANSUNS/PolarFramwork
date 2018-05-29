//Designed By Advanced Stuidos 2018 
// PID Algorithm  Tang Jun
#include "IncludeList.h"

#ifndef __PID_H__
#define __PID_H__
//POAR自带的PID APIS
typedef struct//PID结构体
{
    float SetPoint;//设定目标
    float P;//比例常数
    float I;//积分常数
    float D;//微分常数
    float LastError;//Error[-1]
    float PreError;//Error[-2]
    float LastValue;//Error的总和
}PID;


extern float PIDError(PID p,float CurrentValue );//计算PID误差
extern float PIDCal(PID p,float ThisError,float *out);//PID计算函数
extern void PIDInit(PID *p,float Pro,float Inte,float Del);//PID初始化函数
extern void PIDSet(PID *p);//设置PID的参数

//使用ARM DSP库的PID函数库
typedef struct
{
  arm_pid_instance_q15  Ctrl;
}DSP_PID;

extern float DSP_PIDCal(DSP_PID *p,float CurrentValue);//PID计算函数
extern void DSP_PIDInit(DSP_PID *p,float Pro,float Inte,float Del);//PID初始化函数




#endif