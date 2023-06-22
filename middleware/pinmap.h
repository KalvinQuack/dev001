
#ifndef __PINMAP_H__
#define __PINMAP_H__
    //environment includes
    #include "inc/hw_memmap.h"
    #include "driverlib/pin_map.h"

    //standard includes
    #include <stdint.h>
    /* defines */
    #define PERP 0
    #define PORT 1
    #define PIN  2

    /* board devices*/
    typedef enum DEVICES {
        DIGITAL_INPUTS, 
        LEDS, 
        RGB_LEDS,
        DIGITAL_OUTPUTS, 
        PWM_OUTPUTS, 
        UART, 

    }DEVICE;
    /*pinmap struct*/
    typedef struct PINOUT {
         uint32_t device_peripheral;    //perpiheral register
         uint32_t device_port;          //port regsiter
         uint32_t device_pin;           //pin number
    }PINOUT;

    typedef struct UART_DEV {
        uint32_t uart_peripheral;       //uart peripheral
        uint32_t uart_base;             //uart base
        uint32_t uart_rx;               //uart_rx
        uint32_t uart_tx;               //uart_tx
    }UART_DEV;

    typedef struct TIMER_DEV {
        uint32_t timer_base;
        uint32_t timerA;
        uint32_t timerB;
    }TIMER_DEV;

    PINOUT* accessDevice_pinout(DEVICE deviceType, uint32_t deviceIndex);
    UART_DEV* accessUART_device(uint32_t UART_index);

#endif