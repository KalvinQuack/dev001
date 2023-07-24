
#ifndef __PINMAP_H__
#define __PINMAP_H__



    //standard includes
    #include <stdint.h>


    


    /* board devices*/
    #define DIGITAL_INPUT_TOTAL 5
    #define UART_TOTAL 2

    #define uart_base 0
    #define uart_rx 1
    #define uart_tx 2

    #define PERIPHERAL_CLOCKS_TOTAL 7
    extern const uint32_t digitalInput_portLookup[DIGITAL_INPUT_TOTAL];
    extern const uint32_t gpio_pinLookup[DIGITAL_INPUT_TOTAL];
    extern const uint32_t peripheralLookup[PERIPHERAL_CLOCKS_TOTAL];
    extern const uint32_t uartGPIO_lookup[UART_TOTAL][3];
    extern const uint32_t uart_lookup[UART_TOTAL][3];
    /* board devices*/
    typedef enum DEVICE 
    {
        DIGITAL_INPUTS, 
        LEDS, 
        RGB_LEDS,
        DIGITAL_OUTPUTS, 
        PWM_OUTPUTS, 
        UART, 

    }DEVICE;
    /*pinmap struct*/
    typedef struct PINOUT 
    {
         uint32_t device_peripheral;    //perpiheral register
         uint32_t device_port;          //port regsiter
         uint32_t device_pin;           //pin number
    }PINOUT;

    typedef struct UART_DEV UART_DEV;

    typedef struct TIMER_DEV TIMER_DEV;

    PINOUT* accessDevice_pinout(DEVICE deviceType, uint32_t deviceIndex);
    UART_DEV* accessUART_device(uint32_t UART_index);

#endif