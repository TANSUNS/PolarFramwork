#include<FR_Filter.h>
#include <IncludeList.h>

//特别注意 滤波器系数大于等于4且为偶数，所以阶数应该大于等于3且为奇数
uint8_t FastLowPassFR(float32_t *Src,float32_t *Des,float32_t *firCoeffs32)
{
    q15_t *temp;
    q15_t *Outtemp;
    int SIZE;
    int NUM;    
    arm_status Status;
    arm_fir_instance_q15 *S;
    float32_t *STATE;//缓冲区

    SIZE=sizeof(Src)/sizeof(Src[0]);//转换数据块的大小
    NUM=sizeof(firCoeffs32)/(firCoeffs32[0]);//滤波器系数的个数
    STATE=(float32_t *)malloc(size(float32_t)*(SIZE+NUM-1));

     arm_float_to_q15（Src，temp，SIZE);//将浮点数转换成Q15的定点数
     Status=arm_fir_init_q15(S,NUM,(float32_t *)&firCoeffs32[0],STATE,SIZE);//初始化滤波器
     if(Status==ARM_MATH_SUCCESS)
     {
         arm_fir_fast_q15(S,temp,Outtemp,SIZE);//滤波
         arm_q15_to_float(Outtemp,Des,SIZE);
         return 1;
）	
     }

     else
     return 0;

}  
