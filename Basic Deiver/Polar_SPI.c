#include "Polar_SPI.h"

uint8_t SPI_INIT(SPI_TypeDef* SPIx,uint16_t Channel,uint8_t Mode,uint8_t DataByte,uint8_t SPIModex,uint8_t Nss,uint8_t Speed,uint8_t FirstBit);///< SPI设置函数
{
    SPI_InitTypeDef S;
    GPIO_InitTypeDef D;

    //设置选定为时钟
    if(SPIx==SPI1)
    {
     RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
     D.GPIO_Pin=GPIO_Pin_5;
     D.GPIO_Mode=GPIO_Mode_AF_PP;
     GPIO_Init(GPIOA,&D);
     D.GPIO_Pin=GPIO_Pin_6;
     GPIO_Init(GPIOA,&D);
     D.GPIO_Pin=GPIO_Pin_7;
     GPIO_Init(GPIOA,&D);
     SPI_NSS_Register(SPI1_Port,Channel);

    }
     else if(SPIx==SPI2)
     {
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
      RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
     D.GPIO_Pin=GPIO_Pin_13;
     D.GPIO_Mode=GPIO_Mode_AF_PP;
     GPIO_Init(GPIOA,&D);
     D.GPIO_Pin=GPIO_Pin_14;
     GPIO_Init(GPIOA,&D);
     D.GPIO_Pin=GPIO_Pin_15;
     GPIO_Init(GPIOA,&D);
     SPI_NSS_Register(SPI2_Port,Channel);

     }

    SPI_I2S_DeInit(SPIx);
    
    //默认全双工模式
    S.SPI_Direction=SPI_Direction_2Lines_FullDuplex;

    //设置为主机或者丛机 
    switch(Mode)
    {
        case Master:   
         S.SPI_Mode=SPI_Mode_Master;
         break;
        case Slave:
         S.SPI_Mode=SPI_Mode_Slave;
         break;
         default :
            return NOTOK;
    }  
   //设置一帧数据的大小
   switch(DataBytes)
   {
       case Bytes:
       S.SPI_DataSize=SPI_DataSize_8b;
       break;
       case HaldWords:
        S.SPI_DataSize=SPI_DataSize_16b;
        break;

        default :
            return NOTOK;
   }
   //设置极性和工作方式 CPOL为高位CPHA为低位
   switch(SPIModex)
   {
       case SPIMode0:
       S.SPI_CPOL=SPI_CPOL_Low;
       S.SPI_CPHA=SPI_CPHA_1Edge;
       break;

       case SPIMode1:
       S.SPI_CPOL=SPI_CPOL_Low;
       S.SPI_CPHA=SPI_CPHA_2Edge;
       break;

       case SPIMode2:
       S.SPI_CPOL=SPI_CPOL_High;
       S.SPI_CPHA=SPI_CPHA_1Edge;
       break;

       case SPIMode3:
       S.SPI_CPOL=SPI_CPOL_High;
       S.SPI_CPHA=SPI_CPHA_2Edge;
       break;

       default :
            return NOTOK;
        
        }
     //设置片选线为自动还是手动
        switch(Nss)
        {
            case AotoNss:
            S.SPI_NSS=SPI_NSS_Soft;
            break;
            case ManualNss:
            S.SPI_NSS=SPI_NSS_Hard;
            default :
            return NOTOK;
        }
    //设置分频速度
        switch(Speed)
        {
            case 2:
            S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;
            break;
            case 4:
            S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_4;
            break;
            case 8:
            S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_8;
            break;
            case 16:
            S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_16;
            break;
            case 32:
            S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_32;
            break;
            case 64:
             S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_64;
            break;
            case 128:
            S.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_128;
            break;
            default :
            return NOTOK;
        }
  //设置高位优先还是地位优先
        switch(FirstBit)
        {
            case MSB:
            S.SPI_FirstBit=SPI_FirstBit_MSB;
            break;
            case LSB:
            S.SPI_FirstBit=SPI_FirstBit_LSB;
            break;
            default :
            return NOTOK;
        }

        S.SPI_CRCPolynomial=7;

        SPI_Init(SPIx,&S);
        SPI_Cmd(SPIx,ENABLE);
        return OK;

}

uint8_t SPI_NSS_Register(GPIO_TypeDef *GPIOx,uint16_t Channel)
{

    GPIO_InitTypeDef G;

    if(GPIOx==GPIOA)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
    else if(GPIOx==GPIOC)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
    else if(GPIOx==GPIOD)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
    else if(GPIOx==GPIOE)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
    else if(GPIOx==GPIOF)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO,ENABLE);
    else if(GPIOx==GPIOG)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO,ENABLE);

    G.GPIO_Mode=GPIO_Mode_Out_PP;
    G.GPIO_Pin=Channel;
    G.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOx,&G);
    return OK;

}

void Select_Channel(SPI_TypeDef* SPIx,uint16_t Channel)
{
    if(SPIx==SPI1)
    GPIO_ResetBits(SPI1_Port,Channel);
    else if(SPIx==SPI2)
    GPIO_ResetBits(SPI2_Port,Channel);

}
void Release_Channel(SPI_TypeDef* SPIx,uint16_t Channel)
{    
    if(SPIx==SPI1)
    GPIO_SetBits(SPI1_Port,Channel);
    else if(SPIx==SPI2)
    GPIO_SetBits(SPI2_Port,Channel);
}

uint8_t SPISendByteData(SPI_TypeDef* SPIx,uint8_t *Data,uint16_t Channel)///< 传送8位数据
{
    int DataSize,i=1000;
    DataSize=sizeof(Data)/sizeof(Data[0]);
    Select_Channel(SPIx,Channel);  //选通通道
    while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET)
    {
        if((i--)==0)
        return NOTOK;
    }
    if(i=0;i<=DataSize;i++)
    {
    SPI_I2S_SendData(SPIx,Data[i]);
    }
    Release_Channel(SPIx,Channel);
    return OK;
    

}

uint8_t SPISendHalfWordData(SPI_TypeDef* SPIx,uint16_t *Data,uint16_t Channel)///< 传送16位数据
{
    int DataSize,i=1000;
    DataSize=sizeof(Data)/sizeof(Data[0]);
    Select_Channel(SPIx,Channel);  //选通通道
    while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET)
    {
        if((i--)==0)
        return NOTOK;
    }
    if(i=0;i<=DataSize;i++)
    {
    SPI_I2S_SendData(SPIx,Data[i]);
    }
    Release_Channel(SPIx,Channel);
    return OK;
}

uint8_t SPIGetByteData(SPI_TypeDef* SPIx,uint8_t *Buffer,uint16_t Channel)///<获得8位数据
{
    int DataSize,i=1000;
    DataSize=sizeof(Buffer)/sizeof(Buffer[0]);
    Select_Channel(SPIx,Channel);   //选通通道
    while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_RXNE)==RESET)
    {
        if((i--)==0)
        return NOTOK;
    }
    if(i=0;i<=DataSize;i++)
    {
    Bufer[i]=SPI_I2S_ReceiveData(SPIx);
    }
    Release_Channel(SPIx,Channel);
    return OK;
}

uint8_t SPIGetHalfDate(SPI_TypeDef* SPIx,uint16_t *Buffer,uint16_t Channel)///< 获得16位数据
{
    int DataSize,i=1000;
    DataSize=sizeof(Buffer)/sizeof(Buffer[0]);
    Select_Channel(SPIx,Channel);  //选通通道
    while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET)
    {
        if((i--)==0)
        return NOTOK;
    }
    if(i=0;i<=DataSize;i++)
    {
    Bufer[i]=SPI_I2S_ReceiveData(SPIx);
    }
    Release_Channel(SPIx,Channel);
    return OK;
}

uint8_t SPISend_Get(SPI_TypeDef* SPIx,uint16_t Channel,uint16_t *Data,uint16_t *Buffer)///<同时获得获得和传输16位数据
{
    int DataSize,i=1000;
    DataSize=sizeof(Data)/sizeof(Data[0]);

    Select_Channel(SPIx,Channel); //选通通道

    while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET) //等待信号
    {
        if((i--)==0)
        return NOTOK;
    }
    if(i=0;i<=DataSize;i++)
    {
    SPI_I2S_SendData(SPIx,Data[i]);
    }

    i=1000;

    DataSize=sizeof(Buffer)/sizeof(Buffer[0]);

    while(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==RESET) 
    {
        if((i--)==0)
        return NOTOK;
    }
    if(i=0;i<=DataSize;i++)
    {
    Bufer[i]=SPI_I2S_ReceiveData(SPIx);
    }
    Release_Channel(SPIx,Channel);
    return OK;
}

void CloseSPI(SPI_TypeDef* SPIx);///<关闭SPI总线
{
    SPI_Cmd(SPIx,DISABLE);

}

void OpenSPI(SPI_TypeDef* SPIx);///<开启SPI总线 
{
    SPI_Cmd(SPIx,ENABLE);

}

 uint8_t SPI_IT_Config(void)
 { 
     //目前未开放SPI中断功能

 }

 uint8_t GetSPIFlag(SPI_TypeDef *SPIx,uint8_t Flag)
 {
     if(SPI_I2S_GetFlagStatus(SPIx,SPI_I2S_FLAG_TXE)==SET)
     return OK;
     else
     return NOTOK;


 }
 void ClearSPIFlag(SPI_TypeDef *SPIx,uint8_t Flag)
 {
     SPI_I2S_ClearFlag(SPIx,Flag);
 }