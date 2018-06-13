#include "Polar_1602.h"

uint8_t LCD1602_Init(LCD_1602Obj *LCD) //初始化1602管脚
{
    GPIO_INIT(LCD->Port,LCD->RS,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->RW,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->E,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D0,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D1,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D2,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D3,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D4,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D5,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D6,LOW_Speed,6);
    GPIO_INIT(LCD->Port,LCD->D7,LOW_Speed,6);

}

static void WriteCom(LCD_1602Obj *LCD,uint8_t *ComGrp)//按组写入命令
{
    int i,SIZE,j;
    uint8_t *DATABIT;
    uiny16_t Protect;//保护其他端口的数据
    SIZE=sizeof(ComGrp)/sizeof(ComGrp[0]);

    Protect=GPIO_ReadOutputData(LCD->Port);

   


    for(i=0;i<SIZE;i++)
    { 
    DATABIT=TEST_8_Bit(ComGrp[i]);
    Low_GPIO(LCD->Port,LCD->RS);       
    Low_GPIO(LCD->Port,LCD->RW);
    delay_ms(1);

    for(j=0;j<8;j++)
    {
        switch(j)
        {
        case 0:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

       case 1:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 2:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 3:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 4:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 5:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 6:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 7:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;


        }
    }
    
    delay_ms(1);
    High_GPIO(LCD->Port,LCD->RS);
    High_GPIO(LCD->Port,LCD->RW);
    delay_ms(1);
    }

    return OK;
    
}

//static uint8_t LCDRead(LCD_1602Obj *LCD,uint8_t Mode);//读取1602的数据

void LCD1602_Display(LCD_1602Obj *LCD,uint8_t *Data)//在1602上显示数据
{
    int i,SIZE,j;
    uint8_t *DATABIT,*Addr;
    *Addr=FIRST
    SIZE=sizeof(Data)/sizeof(Data[0]);
    WriteCom(LCD,Addr);

    Protect=GPIO_ReadOutputData(LCD->Port);

    DATABIT=TEST_8_Bit(Data);


    for(i=0;i<SIZE;i++)
    {
    DATABIT=TEST_8_Bit(Data[i]);
    High_GPIO(LCD->Port,LCD->RS);       
    Low_GPIO(LCD->Port,LCD->RW);
    delay_ms(1);

    for(j=0;j<8;j++)
    {
        switch(j)
        {
        case 0:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

       case 1:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 2:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 3:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 4:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 5:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 6:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;

        case 7:
        switch(DATABIT[j])
        {
            case 1:
            High_GPIO(LCD->Port,LCD->D0);
            break;

            case 0:
            Low_GPIO(LCD->Port,LCD->D0);
            break;
        }
        break;


        }
    }
    
    delay_ms(1);
    High_GPIO(LCD->Port,LCD->RS);
    High_GPIO(LCD->Port,LCD->RW);
    delay_ms(1);
    }

    return OK;
    
}

void ClearAll(LCD_1602Obj *LCD)//清屏
{
    uint8_t *Addr;
    *Add=CLEARDISPLAY;
     WriteCom(LCD,Addr);

}