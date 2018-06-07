#include "Polar_DMA.h"


uint8_t DMA_INIT(DMA_Channel_TypeDef *Channel,uint8_t Level,uint32_t DataNum,uint32_t PeriAdr,uint32_t PeriByte,uint8_t PeriInc,uint32_t MemAdr,uint32_t MemByte,uint8_t MemInc,Who_To_Who Way,uint8_t CircleFlag)
{
    DMA_InitTypeDef D;
    D.DMA_PeripheralBaseAddr=PeriAdr; //设置基本的地址
    D.DMA_MemoryBaseAddr=MemAdr;
    D.DMA_BufferSize=DataNum;      //设置数据量
    switch (CircleFlag)
    {
        case Circle:
        D.DMA_Mode=DMA_Mode_Circular;
        case Onece:
        D.DMA_Mode=DMA_Mode_Normal;
    }  
    switch (MemInc) //设置地址增加与否
    {
        case Inc:
        D.DMA_MemoryInc=DMA_PeripheralInc_Enable;
        break;
        case Hold:
        D.DMA_MemoryInc=DMA_PeripheralInc_Disable;
        break;
        }

    switch (PeriInc)
    {
        case Inc:
        D.DMA_PeripheralInc=DMA_PeripheralInc_Enable;
        break;
        case Hold:
        D.DMA_PeripheralInc=DMA_PeripheralInc_Disable;\
        break;
        }
    
    switch (Way)  //设置传输方向
    {
        case MEMTOMEM:
        D.DMA_DIR=DMA_DIR_PeripheralSRC;
        D.DMA_M2M=DMA_M2M_Enable;
        D.DMA_Mode=DMA_Mode_Normal; //内存到内存情况下，DMA只允许调用正常模式
        break;

        case PERIPHTOMEM:
        D.DMA_DIR=DMA_DIR_PeripheralSRC;
        D.DMA_M2M=DMA_M2M_Disable;
        break;

        case MEMTOPERIPH:
        D.DMA_DIR=DMA_DIR_PeripheralDST;
        D.DMA_M2M=DMA_M2M_Disable;
        break;
    }

    switch (Level)
    {
        case MostLevel:
        D.DMA_Priority=DMA_Priority_VeryHigh;
        break;
        case HighLevel:
        D.DMA_Priority=DMA_Priority_High;
        break;
        case MediumLevel:
        D.DMA_Priority=DMA_Priority_Medium;
        break;
        case LowLevel:
        D.DMA_Priority=DMA_Priority_Low;
        break;
        
    }

    switch (PeriByte)
    {
        case Bytes:
        D.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
        break;
        case HalfWords:
        D.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
        break;
        case Words:
        D.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
        break;

    }
    switch (MemByte)
    {
        case Bytes:
        D.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
        break;
        case HalfWords:
        D.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
        break;
        case Words:
        D.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Word;
        break;

    }

    DMA_Init(Channel,&D);
    DMA_Cmd(Channel,ENABLE);
    

   return OK;

}


void CloseDMA(DMA_Channel_TypeDef *Channel)  //关闭DMA通道
{
    DMA_Cmd(Channel,DISABLE);
}

void OpenDMA(DMA_Channel_TypeDef *Channel)  //打开DMA通道/软件触发
{
    DMA_Cmd(Channel,ENABLE);

}

void Start_DMA_Convers(DMA_Channel_TypeDef *Channel,uint16_t DataSize) //一次传递后重启下一次
{
    CloseDMA(Channel);
    DMA_SetCurrDataCounter  (Channel, DataSize);
    OpenDMA(Channel); 

}

uint8_t DMAIsFinish(DMA_Channel_TypeDef *Channel)//判断传输是否完成
{


}
 uint8_t Mem_ByteDataTransfer(uint8_t *Src,uint8_t *Des,DMA_Channel_TypeDef *Channel) //8位数据传输
 {
     int NUM;
     NUM=sizeof(Des)/sizeof(Des[0]);
     DMA_INIT(Channel,HighLevel,NUM,(uint32_t)Des,Bytes,Inc,(uint32_t)Src,Bytes,Inc,MEMTOMEM,Onece);
     return OK;
 }

 uint8_t Mem_HalfWordDataTransfer(uint16_t *Src,uint16_t *Des,DMA_Channel_TypeDef *Channel)//16位数据传输
 {
     int NUM;
     NUM=sizeof(Des)/sizeof(Des[0]);
     DMA_INIT(Channel,HighLevel,NUM,(uint32_t)Des,HalfWords,Inc,(uint32_t)Src,HalfWords,Inc,MEMTOMEM,Onece);
     return OK;
 }

 uint8_t Mem_WordDataTransfer(uint32_t *Src,uint32_t *Des,DMA_Channel_TypeDef *Channel)//32位数据传输
 {
          int NUM;
     NUM=sizeof(Des)/sizeof(Des[0]);
     DMA_INIT(Channel,HighLevel,NUM,(uint32_t)Des,Words,Inc,(uint32_t)Src,Words,Inc,MEMTOMEM,Onece);
     return OK;
 }

 uint8_t DMA_IT_Config(DMA_Channel_TypeDef *Channel,uint32_t WichType) //允许DMA中断，只能被IT组件调用
 {}
 uint8_t Clea_DMA_IT_Flag(DMA_Channel_TypeDef *Channel) //清除中断FLAG函数
 {}

static void PeriphDMAInit(void)        //外设响应允许通道
{
    //每个通道的连接函数必须被放置到此处
}