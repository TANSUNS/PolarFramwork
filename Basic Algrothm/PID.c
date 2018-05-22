#include "PID.h"

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
   
//    printf("A:%f\n",pError);
//    printf("B:%f\n",iError);
//    printf("C:%f\n",dError);
    
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