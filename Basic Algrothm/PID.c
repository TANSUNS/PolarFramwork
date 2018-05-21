#include "PID.h"
////////////////////////////////////////////////////////////////////////////////////////////
//NORMAL PID APIS//
////////////////////////////////////////////////////////////////////////////////////////////
float PIDError(PID p,float CurrentValue)
{
    float out;
    out=(p.SetPoint)-CurrentValue;
    /*printf("PP:%f\n",p.P);
//    printf("II:%f\n",p.I);
//    printf("DD:%f\n",p.D);*/

    return out;
    }



float PIDCal(PID p,float ThisError,float *out)
{
    float pError,dError,iError;
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
   p.Position=p.Position+A+B+C;
   *out=p.Position;
//   printf("PP:%f\n",p.P);
//    printf("II:%f\n",p.I);
//   printf("DD:%f\n",p.D);
//   printf("TEMPL:%f\n",out);
//    printf("D:%f\n",A);
//    printf("E:%f\n",B);
//    printf("F:%f\n",C);
   //开始平移储存
   
   (p.PreError)=(p.LastError);
   (p.LastError)=ThisError;
   return 0;
}


void PIDInit(PID *p,float Pro,float Inte,float Del)
{
    p->P=Pro;
    p->I=Inte;
    p->D=Del;
    p->Position=0;
//    printf("PP:%f\n",p->P);
//    printf("II:%f\n",p->I);
//    printf("DD:%f\n",p->D);
}

////////////////////////////////
//ProPID APIS       /////////////                  
////////////////////////////////
float Abs(float num)
{
    if(num>=0)
      return num;
      else
      return (0-num);
}

void ProPIDSave(ProPID p)
{
   (p.PreError)=(p.LastError);
   (p.LastError)=(p.Errors);

}

void ProPIDInit(ProPID *p,float Pro,float Inte,float Del,float m1,float m2,float Max,float Am,float Am2,float ER)//初始化ProPID参数
{
    p->P=Pro;
    p->I=Inte;
    p->D=Del;
    p->M1=m1;
    p->M2=m2;
    p->k1=Am;
    p->k2=Am2;
    p->e=ER;
    p->LastOutput=0;

}

float ProPIDCal(ProPID p,float MessureValue)
{
    float pError,iError,dError,templ;
    p.Errors=(p.SetPoint)-MessureValue;
    p.dEk=(p.Errors)-(p.LastError);
    p.dEk_1=(p.LastError)-(p.PreError);
    pError =(p.Errors)-(p.LastError);
    iError =p.Errors;
    dError =(p.Errors)-2*(p.LastError)+(p.PreError);

//    printf("A:%f\n",pError);
//    printf("B:%f\n",iError);
//    printf("C:%f\n",dError);
    
   //开始增量计算

   templ=(p.P)*pError+(p.I)*iError+(p.D)*dError;//ss

   if(Abs(p.Errors)>(p.M1))    //规则1
   {
       ProPIDSave(p);
       return p.MAXOUTPUT;
   }

   if((p.Errors)*(p.dEk)>0||(p.Errors==0))  //规则2 e(k)dert e(k)>0 或者e(k)=0
   {
       if(Abs((p.Errors))>= (p.M2) )
       {
           templ=templ*(p.k1);
           p.LastOutput=templ;
           ProPIDSave(p);
           return templ;
       }
       else
       {
           p.LastOutput=templ;
           ProPIDSave(p);
           return templ;
       }
   }
   else
   {
       if((p.dEk)*(p.dEk_1)>0||(p.Errors)==0) //规则3 e(k)*dert e(k)<0,dert e(k)*dert e(k-1)>0 或者e(k)=0
       {
           templ=(p.LastOutput);
           ProPIDSave(p);
           return templ;

       }
       else                                  //规则4  e(k)*dert e(k)<0,dert e(k)*dert e(k-1)<0 
       {
           templ=(p.k1)*(p.P)*(p.Errors);
           p.LastOutput=templ;
           ProPIDSave(p);
           return templ;
           
       }

   }
   if(Abs((p.Errors))<=(p.e))   //规则5 e(k)<=e(精度)
   {
       templ=(p.k2)*(p.P)*(p.Errors);
       p.LastOutput=templ;
       ProPIDSave(p);
       return templ;
   }


}

