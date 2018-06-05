#include "Polar_EXTI.h"

uint8_t EXTI_Config(TriggerType *Trigger,uint32_t *Line, GPIO_TypeDef **GPIOXTable) //该函数只能在PeriphInterruptInit中被调用
{
    int SizeTri;//,SizeLine;
    EXTI_InitTypeDef E;
    GPIO_InitTypeDef G;
    SizeTri=sizeof(Trigger)/sizeof(Trigger[0]);
   // SizeLine=sizeof(Line)/sizeof(Line(0));

    for(int i=0;i<SizeTri;i++) //开始设置外部中断线和管脚配置
    {
        switch (Line[i])
        {
            case EXTI_Line0: 
            G.GPIO_Pin=GPIO_Pin_0;
            E.EXTI_Line=EXTI_Line0;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
          EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


            case EXTI_Line1:
            G.GPIO_Pin=GPIO_Pin_1;
            E.EXTI_Line=EXTI_Line1;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


            case EXTI_Line2:
            G.GPIO_Pin=GPIO_Pin_2;
            E.EXTI_Line=EXTI_Line2;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


            case EXTI_Line3:
            G.GPIO_Pin=GPIO_Pin_3;
            E.EXTI_Line=EXTI_Line3;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line4:
            G.GPIO_Pin=GPIO_Pin_4;
             E.EXTI_Line=EXTI_Line4;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line5:
            G.GPIO_Pin=GPIO_Pin_5;
            E.EXTI_Line=EXTI_Line5;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line6:
            G.GPIO_Pin=GPIO_Pin_6;
           E.EXTI_Line=EXTI_Line6;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


            case EXTI_Line7:
            G.GPIO_Pin=GPIO_Pin_7;
            E.EXTI_Line=EXTI_Line7;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


            case EXTI_Line8:
            G.GPIO_Pin=GPIO_Pin_8;
            E.EXTI_Line=EXTI_Line8;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


            case EXTI_Line9:
            G.GPIO_Pin=GPIO_Pin_9;
            E.EXTI_Line=EXTI_Line9;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line10:
            G.GPIO_Pin=GPIO_Pin_10;
            E.EXTI_Line=EXTI_Line10;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line11:
            G.GPIO_Pin=GPIO_Pin_11;
            E.EXTI_Line=EXTI_Line11;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line12:
            G.GPIO_Pin=GPIO_Pin_12;
            E.EXTI_Line=EXTI_Line12;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line13:
            G.GPIO_Pin=GPIO_Pin_13;
            E.EXTI_Line=EXTI_Line13;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line14:
            G.GPIO_Pin=GPIO_Pin_14;
            E.EXTI_Line=EXTI_Line14;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;

            case EXTI_Line15:
            G.GPIO_Pin=GPIO_Pin_15;
            E.EXTI_Line=EXTI_Line15;
            switch(Trigger[i]):
            {
                case RISE://上升沿触发，设置成下拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPD;
                E.Trigger=EXTI_Trigger_Rising;
                break;
                case FALL://下降沿触发，设置成上拉输入
                G.GPIO_Mode=GPIO_Mode_IN_IPU;
                E.Trigger=EXTI_Trigger_Falling;
                break;
            }
            E.EXTI_Mode=EXTI_Mode_Interrupt;
            E.EXTI_LineCmd=ENABLE;
            EXTI_Init(&E);
          EXTI_GPIO_Config(*GPIOXTable[i]);
          break;


    
        }
    }

    return 1;
}

void EXTI_GPIO_Config(GPIO_TypeDef *s)
{
    switch(s): //设置时钟
            {
                case GPIOA:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE); //开启GPIO时钟并开启复用时钟
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); //设置中断源
            GPIO_Init(GPIOA,&G); //初始化GPIO
            break;

                case GPIOB:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
            GPIO_Init(GPIOB,&G);
            break;
                case GPIOC:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource0);
            GPIO_Init(GPIOC,&G);
            break;
                case GPIOD:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);
            GPIO_Init(GPIOD,&G);
            break;
                case GPIOE:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO,ENABLE);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource0);
            GPIO_Init(GPIOE,&G);
            break;
                case GPIOF:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF|RCC_APB2Periph_AFIO,ENABLE);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOF,GPIO_PinSource0);
            GPIO_Init(GPIOF,&G);
            break;
                case GPIOG:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);
            GPIO_EXTILineConfig(GPIO_PortSourceGPIOG,GPIO_PinSource0);
            GPIO_Init(GPIOG,&G);
            break;

            }

}

extern void EXTI_FastConfig(GPIO_TypeDef *GPIOx,uint16_t Pin,TriggerType Trigger); //该函数只能在设置完优先级等级后才能使用
{
    EXTI_InitTypeDef E;
    GPIO_InitTypeDef G;
    G.GPIO_Pin=Pin;

    switch (Pin)
    {
        case GPIO_Pin_0:
        E.EXTI_Line=EXTI_Line0;
        break;
        case GPIO_Pin_1:
                E.EXTI_Line=EXTI_Line1;
        break;
        case GPIO_Pin_2:
                E.EXTI_Line=EXTI_Line2;
        break;
        case GPIO_Pin_3:
                E.EXTI_Line=EXTI_Line3;
        break;
        case GPIO_Pin_4:
                E.EXTI_Line=EXTI_Line4;
        break;
        case GPIO_Pin_5:
                E.EXTI_Line=EXTI_Line5;
        break;
        case GPIO_Pin_6:
                E.EXTI_Line=EXTI_Line6;
        break;
        case GPIO_Pin_7:
                E.EXTI_Line=EXTI_Line7;
        break;
        case GPIO_Pin_8:
                E.EXTI_Line=EXTI_Line8;
        break;
        case GPIO_Pin_9:
                E.EXTI_Line=EXTI_Line9;
        break;
        case GPIO_Pin_10:
                E.EXTI_Line=EXTI_Line10;
        break;
        case GPIO_Pin_11:
                E.EXTI_Line=EXTI_Line11;
        break;
        case GPIO_Pin_12:
                E.EXTI_Line=EXTI_Line12;
        break;
        case GPIO_Pin_13:
                E.EXTI_Line=EXTI_Line13;
        break;
        case GPIO_Pin_14:
                E.EXTI_Line=EXTI_Line14;
        break;
        case GPIO_Pin_15:
                E.EXTI_Line=EXTI_Line15;
        break;
    }

    switch(Trigger):
        {
            case RISE://上升沿触发，设置成下拉输入
            G.GPIO_Mode=GPIO_Mode_IN_IPD;
            E.Trigger=EXTI_Trigger_Rising;
            break;
            case FALL://下降沿触发，设置成上拉输入
            G.GPIO_Mode=GPIO_Mode_IN_IPU;
            E.Trigger=EXTI_Trigger_Falling;
            break;
        }
    
    E.EXTI_Mode=EXTI_Mode_Interrupt;
    E.EXTI_LineCmd=ENABLE;
    EXTI_Init(&E);
    EXTI_GPIO_Config(GPIOX);
}
extern uint8_t EXTICheckFlag(uint32_t Line);
extern uint8_t ClearEXTIFlag(uint32_t Line);