/**
 * @file aht10.c
 * @brief sensor dirver aht10
 * @author .....
 * @date 12-09-2021
*/


#include "aht10.h"
#include <string.h>

static void aht10ReadReg(aht10Data_t *obj, uint8_t regToRead , uint8_t amount);
static void aht10WriteReg(aht10Data_t *obj, uint16_t data, uint8_t reg , uint8_t amount);

// Nota: la funcion leer en el i2c internamente conlleva que debe escribir primero el 
//registro para luego leerlo


//Nota: temp y hum son de 20 bits
void aht10Init(aht10Data_t *obj, aht10WriteFcn_t fcnWrappWriteI2c, aht10ReadFcn_t fcnWrappReadI2c, uint8_t addrSlave){

    obj->addresSlave = addrSlave;
    obj->readI2c = fcnWrappReadI2c;
    obj->writeI2c = fcnWrappWriteI2c;
    obj->status = 0;
}


//se usan para reutilizar codigo de lectura o escritura de registro
void aht10WriteReg(aht10Data_t *obj, uint16_t data, uint8_t regTowrite , uint8_t amount){
    // escribir en los registros

    /*registro , dato 0 , dato 1*/
    uint8_t bufferOut[3] ={0};// 1 registro y 2 para el dato(dato 0 y dato 1)
    bufferOut[0] = regTowrite;
    bufferOut[1] = (data & 0x00ff); //dato 0      11110000        10101010
    bufferOut[2] = data >> 8 ;       //dato 1

    obj->writeI2c(obj->addresSlave, (void*)bufferOut, (amount+1));//escribir(0x38, "hola mundo", 2)
}

void aht10ReadReg(aht10Data_t *obj, uint8_t regToRead , uint8_t amount){

 //leer en los regstros
    uint8_t bufferForRead[6]={0};

    bufferForRead[0]=regToRead;  // en el buffer de lectura primero coloco el registro a leer para que en la lectura primero
    //deba escribir( el registro a leer) y luego proceda a leer , cuando lea sobre escribe ese buffer de 6 posiciones
    //con status data0 data1 data2(4bit hum y 4 bits temp) data3 data 4
    obj->readI2c(obj->addresSlave, bufferForRead ,amount, AHT10_SIZE_REG);//read(uint8_t addr, void* data, uint8_t amount, uint8_t leng_register)
    
    memcpy(obj->dataRaw,bufferForRead,6);
    //despues de la respuesta de lectura
    obj->status = bufferForRead[0];
}

void ahtReadDataRaw(aht10Data_t *obj){
    aht10ReadReg(obj,AHT10_CMD_TRIGGER_MEASUREMENT,6);
}

float ahtReadTemperature(aht10Data_t *obj){
    //        1                 2            3
  //  x x x x x x x x   x x x x x x x x   x x x x
    return 25.0;// (uint16_t)( ( (uint32_t)bufferForRead[1] <<16 |  (uint16_t)bufferForRead[2] << 8 ) | bufferForRead[3]>>4);

     //(((uint32_t)((uint16_t)bufferForRead[1] <<8 |  bufferForRead[2] ) ) )<<4 ) |  bufferForRead[3]>>4;
}

float aht10ReadHumidity(aht10Data_t *obj){
    return 100.0;  //(((uint32_t)((uint16_t)bufferForRead[1] <<8 |  bufferForRead[2] ) ) )<<4 ) |  bufferForRead[3]>>4;
}

/*
  void Write_I2C(uint8_t Address, void *data, uint8_t amount){
    uint8_t *DatatoSend = (uint8_t *)data;
    HAL_I2C_Master_Transmit(&hi2c1,Address,DatatoSend,amount,10);
  }
  void Read_I2C(uint8_t Address, void *Register, uint8_t amount, uint8_t Sizereg){
    uint8_t *DatatoSend = (uint8_t *)Register;
    HAL_I2C_Master_Transmit(&hi2c1,Address,DatatoSend, Sizereg, 10);
    HAL_I2C_Master_Receive(&hi2c1,Address,DatatoSend, amount, 10);
  }*/