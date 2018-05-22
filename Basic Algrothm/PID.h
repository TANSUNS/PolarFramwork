//Designed By Advanced Stuidos 2018 
// PID Algorithm  Tang Jun


#ifndef __PID_H__
#define __PID_H__


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





#endif