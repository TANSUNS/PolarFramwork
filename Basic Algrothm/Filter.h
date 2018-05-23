// Designed By TANSUNS//
//General Filter(FLOATING)//
//2018.5.15    Version 1.2


#ifdef __FILTER_H__
#define __FILTER_H__

#define DFT_T float   //Setting the default type of this Algorithms

//COM 
extern DFT_T ABS(DFT_T NUM);

//Range Security
typedef struct
{
    DFT_T UppLmt;//upperLimit
    DFT_T LwrLmt;//lowerLimit
    DFT_T LstVl;//LastValue
    DFT_T Output;

}RgSecrObj;

//APIS

extern uint8_t RangeSecureInit(RgSecrObj *p, DFT_T Up, DFT_T Low);
extern DFT_T RangeSecure_I(RgSecrObj *p,DFT_T CrtVal);
extern DFT_T RangeSecure_II(RgSecrObj *p,DFT_T CrtVal);
 


//

//Limiting filter 

typedef struct
{
    DFT_T LstVl; // LastValue
    DFT_T Error;  //Error
    DFT_T Output;
    DFT_T FstFlg; //是否是第一次的标志位
}LimFilterObj;

//APIS
extern uint8_t LimFilterInit(LimFilterObj *p,DFT_T Error);
extern DFT_T LimFilter(LimFilterObj *p,DFT_T CrtVal);


#endif