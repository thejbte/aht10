#include <stdio.h>
#include "aht10.h"
#include "wrappers.h"

aht10Data_t aht10Data;

//gcc aht10.c wrappers.c main.c -o main
int main(int argc, char const *argv[])
{
    aht10Init(&aht10Data,  /*wirte*/ WrapperParaescribir , /*read*/  WrapperParaLeer ,AHT10_ADDRESS_SLAVE );
    ahtReadDataRaw(&aht10Data);
    ahtReadTemperature(&aht10Data);
    /* code */
    return 0;
}


//https://github.com/enjoyneering/AHT10/blob/master/src/AHT10.cpp