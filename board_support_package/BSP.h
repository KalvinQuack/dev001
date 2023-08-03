
#ifndef __PINMAP_H__
#define __PINMAP_H__



    //standard includes
    #include <stdint.h>


    

    #define PORT    0
    #define PIN     1

    /* board devices*/
    #define DIGITAL_INPUT_TOTAL 5
    #define DIGITAL_OUTPUT_TOTAL 5
    #define UART_TOTAL 2

    #define uart_base 0
    #define uart_rx 1
    #define uart_tx 2

    #define PERIPHERAL_CLOCKS_TOTAL 7

    extern const uint32_t  GPIO_inputMap    [DIGITAL_INPUT_TOTAL]   [2];
    extern const uint32_t  GPIO_outputMap   [DIGITAL_OUTPUT_TOTAL]  [2];

    extern const uint32_t gpio_pinLookup[DIGITAL_INPUT_TOTAL];
    extern const uint32_t peripheralLookup[PERIPHERAL_CLOCKS_TOTAL];
    extern const uint32_t uartGPIO_lookup[UART_TOTAL][3];
    extern const uint32_t uart_lookup[UART_TOTAL][3];
    /* board devices*/

#endif