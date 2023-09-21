#ifndef __BSP_IO_H__
#define __BSP_IO_H__
    #include "util/common.h"
    #define ON 1
    #define OFF 0


    typedef enum{
        INPUT, 
        OUTPUT,
        ADC,
        CAN,
        COMP,
        EPI,
        ETH_LED,
        ETH_MII,
        OUTPUT_OD,
        I2C,
        I2CSCL,
        LCD,
        PWM,
        QEI,
        SSI,
        TIMER,
        UART,
        USB_ANALOG,
        USB_DIGITAL,
        WAKE_HIGH,
        WAKE_LOW
    }PinType;

    typedef struct{
        uint32_t port;
        uint32_t pin;
    }gpioStruct_t;

    uint32_t HAL_readIO(gpioStruct_t* gpioStruct);
    void HAL_writeIO(gpioStruct_t* gpioStruct, uint32_t val);
    void HAL_initIO(gpioStruct_t* gpioStruct, PinType pinType, uint32_t pull, uint32_t strength, uint32_t alt);
    void HAL_deinitIO(gpioStruct_t* gpioStruct);

#endif/* __BSP_IO_H__ */
