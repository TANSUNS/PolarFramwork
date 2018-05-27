#include <Filter.h>
#include <stdlib.h>
#include <stm32f10x.h>


#define DFT_T float
//函数名字 ABS(DFT_T NUM)
//函数说明 取绝对值得函数
//参数 NUM  ：需要取绝对值的值
//返回值：NUM得绝对值
DFT_T ABS(DFT_T NUM)
{
 if(NUM>=0)
 {
     return NUM;
 }
 else
 {
     return (0-NUM);
 }
}

//函数名字 RangeSecureInit(RgSecrObj *p, DFT_T Up, DFT_T Low)
//函数说明 用于RS范围限定函数的句柄初始化
//参数 RgSecrObj *p ：需要限定范围参数的结构体 其名字最好与保护参数的名字类似 ：NAME_RS；
//参数 Up ：限定范围的上限
//参数 Low ：限定范围的下限
//返回值：1:设置成功

uint8_t RangeSecureInit(RgSecrObj *p, DFT_T Up, DFT_T Low)
{
    p->UppLmt=Up;
    p->LwrLmt=Low;
    p->LstVl=0;
    p->Output=0;
    return 1;
    }

//函数名字 RangeSecure_I(RgSecrObj *p, DFT_T CrtVal)
//函数说明 ：第一类数字范围保护，大于范围取边界值
//参数 RgSecrObj *p ：需要限定范围参数的结构体 其名字最好与保护参数的名字类似 ：NAME_RS；
//参数 CrtVal ：需要限制参数的当前值
//返回值： 经过参数保护以后的值
//快捷调用方式 RSI(CrtVal) 未定义

DFT_T RangeSecure_I(RgSecrObj *p, DFT_T CrtVal)
{
    if(CrtVal>=p->UppLmt)
    {
        p->LstVl=p->Output;
        p->Output=p->UppLmt;
        return p->Output;
    }
    if(CrtVal<=p->LwrLmt)
    {
         p->LstVl=p->Output;
        p->Output=p->LwrLmt;
        return p->Output;
    }
     p->LstVl=p->Output;
    p->Output=CrtVal;
    return p->Output;
}
//函数名字 RangeSecure_II(RgSecrObj *p, DFT_T CrtVal)
//函数说明 ：第二类数字范围保护，大于范围取上一次输出值
//参数 RgSecrObj *p ：需要限定范围参数的结构体 其名字最好与保护参数的名字类似 ：NAME_RS；
//参数 CrtVal ：需要限制参数的当前值
//返回值： 经过参数保护以后的值
//快捷调用方式 RSII(CrtVal) 未定义

DFT_T RangeSecure_II(RgSecrObj *p, DFT_T CrtVal)
{
    if(CrtVal>=p->UppLmt||CrtVal<=p->LwrLmt)
    {
         p->LstVl=p->Output;
        p->Output=p->LstVl;
        return p->Output;
    }
     p->LstVl=p->Output;
    p->Output=CrtVal;
    return p->Output;
}

//函数名字  LimFilterInit(LimFilterObj *p,DFT_T Error)
//函数说明 用于限幅滤波函数的句柄初始化
//参数 LimFilterObj *p：需要限定范围参数的结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 Error ：装置允许的误差限定范围
//返回值：1:设置成功

uint8_t LimFilterInit(LimFilterObj *p,DFT_T Error)
{
    p->Error=Error;
    p->Output=0;
    p->LstVl=0;
    p->FstFlg=1;
    return 1;

}

//函数名字  LimFilter(LimFilterObj *p,DFT_T CrtVal)
//函数说明 用于限幅滤波,当数据的波动超过了误差允许值，以上一次输出为准
//参数 LimFilterObj *p：需要限定范围参数的结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 CrtVal ：滤波的值的当前值
//返回值：滤波后的值

DFT_T LimFilter(LimFilterObj *p,DFT_T CrtVal)
{    
    if(ABS((CrtVal-p->LstVl))>=p->Error)
    {
        if(p->FstFlg==1)
        {
            p->LstVl=p->Output;
            p->Output=CrtVal;
            return CrtVal;
        }
        else
        {
            p->LstVl=p->Output;
            p->Output=p->LstVl;
            return p->Output;
        }
    }
    else
    {
        p->LstVl=p->Output;
        p->Output=CrtVal;
        return CrtVal;
    }
}

//函数名字   SldAvrgFilter_I_Init(SldAvrgFilterObj *p,int N)
//函数说明 用于I类滑动滤波函数的句柄初始化
//参数 SldAvrgFilterObj *p：滑动滤波函数控制结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 N ：滑动器的滑动范围 
//N建议取值:流量，N=12；压力，N=4；液面，N=4-12；温度，N=1-4
//返回值：1:设置成功

uint8_t SldAvrgFilter_I_Init(SldAvrgFilterObj *p,int N)
{
    p->Filter_buf=malloc(sizeof(DFT_T)*(N+1));
    p->N=N;
    return 1;
}

//函数名字  SldAvrgFilter_I(SldAvrgFilterObj *P,DFT_T CrtVal)
//函数说明 用于滑动滤波I类，未加权
//参数 SldAvrgFilterObj *p：滑动滤波函数控制结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 CrtVal ：滤波的值的当前值
//返回值：滤波后的值
DFT_T SldAvrgFilter_I(SldAvrgFilterObj *p,DFT_T CrtVal)
{
    DFT_T Sum;
    p->Filter_buf[p->N]=CrtVal;
    for(int i=0;i<p->N;i++)
    {
        p->Filter_buf[i]=p->Filter_buf[i+1];
        Sum+=p->Filter_buf[i];
    }
    p->Output=Sum/p->N;
    return p->Output;
}
//SldAvrgFilter_II_Init(SldAvrgFilterObj *p,int N,DFT_T *C) SldAvrgFilter_II_Init(SldAvrgFilterObj *p,int N)
//函数说明 用于II类滑动滤波函数的句柄初始化
//参数 SldAvrgFilterObj *p：滑动滤波函数控制结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 N ：滑动器的滑动范围 
//N建议取值:流量，N=12；压力，N=4；液面，N=4-12；温度，N=1-4   ALL：3-14
//参数 *C:加权表的设置
//返回值：1:设置成功

uint8_t SldAvrgFilter_II_Init(SldAvrgFilterObj *p,int N,int *C)
{
  p->Filter_buf=malloc(sizeof(DFT_T)*(N+1));
    p->N=N;
    p->Coe=C;
    for(int i=0;i<N;i++)
    {
        p->SumCoe+=C[i];
    }
    return 1;
}

//函数名字  SldAvrgFilter_II(SldAvrgFilterObj *P,DFT_T CrtVal)
//函数说明 用于滑动滤波I类，加权
//参数 SldAvrgFilterObj *p：滑动滤波函数控制结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 CrtVal ：滤波的值的当前值
//返回值：滤波后的值

DFT_T SldAvrgFilter_II(SldAvrgFilterObj *p,DFT_T CrtVal)
{
    int i;
    int Sum;
    p->Filter_buf[p->N]=CrtVal;
    for(i=0;i<p->N;i++)
    {
        p->Filter_buf[i]=p->Filter_buf[i+1];
        Sum+=p->Filter_buf[i]*(p->Coe[i]);
    }
    p->Output=Sum/p->SumCoe;
    return p->Output;
}

//函数名字   MVFilterInit(MVFilterObj *p,int N)
//函数说明 用于防脉冲冲击滤波函数的句柄初始化
//参数 MVFilterObj *p：MV控制参数的结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数N ：数据采集的特征值  建议值 》10
//返回值：1:设置成功

uint8_t MVFilterInit(MVFilterObj *p,int N)
{
    p->N=N;
    return 1;
}

//函数名字  MVfilter(MVFilterObj *p,DFT_T *CrtVal)
//函数说明 用于中值平均滤波类，可以有效抑制冲击带来的偏差
//参数MVFilterObj *p：滑动滤波函数控制结构体 其名字最好与限幅参数的名字类似 ：NAME_RS；
//参数 CrtVal ：滤波的值的当前值,是一个数据，本函数采用组运算
//返回值：滤波后的值

DFT_T MVfilter(MVFilterObj *p,DFT_T *CrtVal)
{
    int i;
    int j;
    DFT_T filter_temp;
    DFT_T Sum;

   for(j = 0; j < p->N - 1; j++)  //冒泡排序
    {
    for(i = 0; i < p->N - 1 - j; i++) 
    {
      if(p->Filter_buf[i] >p-> Filter_buf[i + 1]) 
      {
        filter_temp = p->Filter_buf[i];
        p->Filter_buf[i] = p->Filter_buf[i + 1];
        p->Filter_buf[i + 1] = filter_temp;
      }
    }
  }

   for(i = 1; i < p->N - 1; i++)
    Sum += p->Filter_buf[i];

p->Output=Sum / (p->N - 2);
return  p->Output;


}


