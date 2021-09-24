#ifndef _AHT10_H_
#define _AHT10_H_

#include <stdint.h>

#define AHT10_FALSE                         0   /*!< esto es un macro*/
#define AHT10_TRUE                          1  /* esto es un macro */  //esto es un macro no sirve para doxygen
#define AHT10_SIZE_REG                      1  /*!< tamaño del registro */  


#define AHT10_ADDRESS_SLAVE                 0x38    /* 7 bits*/


#define AHT10_CMD_INITIALIZE                0xE1    /*!< command initialization*/
#define AHT10_CMD_TRIGGER_MEASUREMENT       0XAC  /*!< Trigger measurement*/
#define AHT10_CMD_SOFT_RESET                0XBA  /*!< software reset*/

//      void  escribir(uint8_t addr, void* data, uint8_t amount)
typedef void ( *aht10WriteFcn_t )(uint8_t , void*, uint8_t);

//      void  read(uint8_t addr, void* data, uint8_t amount, uint8_t leng_register)  otro arhgumento podria ser el tamaño del registro.
typedef void ( *aht10ReadFcn_t )(uint8_t , void*, uint8_t, uint8_t);


//-----------------------------------------------------

//funciones que leen y escriben internamente en mi driver, no dependen del microcnotrolador
typedef struct aht10Data {
    /*write i2c */
    aht10WriteFcn_t writeI2c;
    /*read i2c*/
    aht10ReadFcn_t  readI2c;
    uint8_t addresSlave;
    uint8_t status;
    uint8_t dataRaw[6];

}aht10Data_t;

void aht10Init(aht10Data_t *obj, aht10WriteFcn_t fcnWrappWriteI2c, aht10ReadFcn_t fcnWrappReadI2c, uint8_t addrSlave);
/**
 * Note: read before ahtReadTemperature or aht10ReadHumidity
*/
void ahtReadDataRaw(aht10Data_t *obj);
float ahtReadTemperature(aht10Data_t *obj);
float aht10ReadHumidity(aht10Data_t *obj);

#endif



/*
wrapper( addr_slave, registro, longitud){
        i2c_write(alfgomas,  addr_slave, registro, longitud)
        pic_i2cWrite(addr,|registo)

        puntero_fx = pic_i2cWrite;

}*/