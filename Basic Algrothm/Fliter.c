#include <Filter.c>

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
    if(ABS((CrtVal-p->LstVl)>=p->Error)
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
