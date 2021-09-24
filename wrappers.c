#include "wrappers.h"
#include <stdio.h>
#include "aht10.h"


extern aht10Data_t aht10Data;
//------------------------wrappers-----------------------
//      
//typedef void ( *aht10WriteFcn_t )(uint8_t , void*, uint8_t);
void  WrapperParaescribir(uint8_t addr, void* buffer, uint8_t amount){
        /*fncion de i2c de microcontrolador*/
        printf("WrapperParaescribir\n");

}




//typedef void ( *aht10ReadFcn_t )(uint8_t , void*, uint8_t, uint8_t);
void  WrapperParaLeer(uint8_t addr, void* buffer, uint8_t amount, uint8_t sizeReg){
      /*fncion de i2c de microcontrolador*/
      /*i2cstart
      i2cWrite(slave)
      i2cWrite(0x02)
      i2cread(buffer)
      i2cstop*/
     // aht10Data.dataRaw ,
      printf("i2cstart\n");
      printf("i2cWrite(addrslave)\n");
      printf("i2cWrite(buffer)\n");
      printf("i2cread(buffer)\n");
      printf("i2cstop\n");
}