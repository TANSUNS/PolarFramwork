#include "PID.h"
#include "IncludeList.h"

//不使用DSP库的情况下了PID运算，一般ARM在支持DSP的情况下，不建议使用这个部分
float PIDError(PID p,float CurrentValue)
{
    float out;
    out=(p.SetPoint)-CurrentValue;
    return out;
}


float PIDCal(PID p,float ThisError,float *out)
{
    float pError,dError,iError;
    float templ;
    float A,B,C;
    pError =ThisError-(p.LastError);
    iError =ThisError;
    dError =ThisError-2*(p.LastError)+(p.PreError);
       
   //开始增量计算
    A=(p.P)*pError;
    B=(p.I)*iError;
    C=(p.D)*dError;
    templ=A+B+C;

   //开始平移储存
   
   (p.PreError)=(p.LastError);
   (p.LastError)=ThisError;
#ifdef CHECK
   printf("PID Function:%f\r\n",templ);
#endif
   *out=templ;
   return templ;
}


void PIDInit(PID *p,float Pro,float Inte,float Del)
{
    p->P=Pro;
    p->I=Inte;
    p->D=Del;
}

//使用ARM Q15格式的PID 运算，支持M3和M4F内核的芯片

float DSP_PIDCal(DSP_PID *p,float CurrentValue)//PID计算函数
{
    q15_t temp,out;
    float fout;
    arm_float_to_q15(&CurrentValue,&temp,1);
     out=arm_pid_q15(&(p->Ctrl),temp);
    arm_q15_to_float(&out,&fout,1);
    return fout;

}

void DSP_PIDInit(DSP_PID *p,float Pro,float Inte,float Del)
{
    p->Ctrl.Kp=Pro;
    p->Ctrl.Ki=Inte;
    p->Ctrl.Kd=Del;
    arm_pid_init_q15(&((*p).Ctrl),1);

}
