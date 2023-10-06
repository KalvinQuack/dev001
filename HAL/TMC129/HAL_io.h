#ifndef __BSP_IO_H__
#define __BSP_IO_H__
    #include "../util/common.h"


    #define NOT_USED 0 

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

    typedef enum{
        EXT_PULLUP,
        EXT_PULLDOWN,
        INT_PULLUP, 
        INT_PULLDOWN, 
        NO_PULL
    }PullType;

    typedef struct{
        uint32_t port;
        uint8_t pin;
        PinType  type;
        PullType pull;
        uint32_t strength;
        uint32_t alt; 
    }gpioStruct_t;

    uint32_t HAL_readIO(gpioStruct_t* gpioStruct);
    void HAL_writeIO(gpioStruct_t* gpioStruct, uint8_t val);
    void HAL_initIO(gpioStruct_t* gpioStruct);
    void HAL_deinitIO(gpioStruct_t* gpioStruct);
    uint8_t test(void);
    #define IO_WRITE(IO, VAL)  MAP_GPIOPinWrite(ports[TIVA_PORT(IO)], pins[TIVA_PIN(IO)], VAL)
    #define IO_PULLUP(IO)
    #define IO_PULLDOWN(IO)
    #define IO_READ(IO) 


    

#endif/* __BSP_IO_H__ */
