// Designed By TANSUNS//
//General Filter(FLOATING)//
//2018.5.15    Version 1.0

#ifdef __FILTER_H__
#define __FILTER_H__

#define DFT_T float   //Setting the default type of this Algorithms

//Range Security
typedef struct
{
    DFT_T UppLmt;//upperLimit
    DFT_T LwrLmt;//lowerLimit
    DFT_T LstVl;//LastValue
    DFT_T Output;

}RgSecrObj;

//APIS

extern uint8_t RangeSecureInit(RgSecrObj *p,DFT_T Up,DFT_T Low);
extern DFT_T RangeSecure(RgSecrObj *p,DFT_T CrtVal);

//

//Limiting filter 

typedef struct
{
    DFT_T LstVl; // LastValue
    DFT_T Error;  //Error
    DFT_T Output;
}LimFilterObj;

//APIS
extern uint8_t LimFilterInit(DFT_T Error);
extern DFT_T LimFilter(LimFilterObj *p,DFT_T CrtVal);

//Low PSS FILTER

typedef struct
{
    DFT_T Output;
}LPFilterObj;

//APIS
extern uint8_t LPFilterInit(void);
extern DFT_T LimFilter(LimFilterObj *p,DFT_T CrtVal);
//

#endif