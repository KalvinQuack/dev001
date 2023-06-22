/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef _PINOUT_C_
#define _PINOUT_C_
    /* standard includes */
    #include <stdint.h>
    #include <stdbool.h>
    /* environment includes */
    #include "pinmap.h"
    #include "driverlib/sysctl.h"
    #include "driverlib/gpio.h"
    #include "driverlib/pin_map.h"


    #ifdef _DEV001_DEVICE_
        #ifndef _DIGITAL_INPUT_PM_
        #define _DIGITAL_INPUT_PM_
            PINOUT digitalInputs_pinout[] = {
                {SYSCTL_PERIPH_GPIOA, GPIO_PORTA_BASE, GPIO_PIN_0}, //PORT A, PIN 0
                {SYSCTL_PERIPH_GPIOA, GPIO_PORTA_BASE, GPIO_PIN_1}, //PORT A, PIN 1
                {SYSCTL_PERIPH_GPIOA, GPIO_PORTA_BASE, GPIO_PIN_2}, //PORT A, PIN 2
                {SYSCTL_PERIPH_GPIOA, GPIO_PORTA_BASE, GPIO_PIN_3}, //PORT A, PIN 3
                {SYSCTL_PERIPH_GPIOA, GPIO_PORTA_BASE, GPIO_PIN_4}, //PORT A, PIN 4
            };
        #endif

        #ifndef _DIGITAL_OUTPUT_PM_
        #define _DIGITAL_OUTPUT_PM_
            PINOUT digitalOutputs_pinout[] = {
                {SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_0}, //PORT B, PIN 0
                {SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_1}, //PORT B, PIN 1
                {SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_2}, //PORT B, PIN 2
                {SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_3}, //PORT B, PIN 3
                {SYSCTL_PERIPH_GPIOB, GPIO_PORTB_BASE, GPIO_PIN_4}  //PORT B, PIN 4
            };
        #endif

        #ifndef _RGB_LED_PM_
        #define _RGB_LED_PM_
            PINOUT RGBled_pinout[] = {
                {SYSCTL_PERIPH_GPIOR, GPIO_PORTR_BASE, GPIO_PIN_0}, //PORT R, PIN 0
                {SYSCTL_PERIPH_GPIOR, GPIO_PORTR_BASE, GPIO_PIN_1}, //PORT R, PIN 1
                {SYSCTL_PERIPH_GPIOR, GPIO_PORTR_BASE, GPIO_PIN_2}  //PORT R, PIN 2
            };

        #endif

        #ifndef _UART_PM_
        #define _UART_PM_
            PINOUT UARTS_pinout[] = {
                {SYSCTL_PERIPH_GPIOP, GPIO_PORTP_BASE, GPIO_PIN_0}, //UART 6 PP0 Rx
                {SYSCTL_PERIPH_GPIOP, GPIO_PORTP_BASE, GPIO_PIN_1}, //UART 6 PP1 Tx
                {SYSCTL_PERIPH_GPIOK, GPIO_PORTK_BASE, GPIO_PIN_0}, //UART 4 PP0 Rx
                {SYSCTL_PERIPH_GPIOK, GPIO_PORTK_BASE, GPIO_PIN_1}, //UART 4 PP1 Tx
            };

            UART_DEV UARTS[] = {
                {SYSCTL_PERIPH_UART6, UART6_BASE, GPIO_PP0_U6RX, GPIO_PP1_U6TX}, //UART 6
                {SYSCTL_PERIPH_UART4, UART4_BASE, GPIO_PK0_U4RX, GPIO_PK1_U4TX}  //UART 4
            };
        #endif 
    #endif 

    PINOUT* accessDevice_pinout(DEVICE deviceType, uint32_t deviceIndex){
        PINOUT *device_ptr;
    switch(deviceType){
        
        case DIGITAL_INPUTS:           
            device_ptr = &digitalInputs_pinout[deviceIndex];          
        break;
        case DIGITAL_OUTPUTS:      
            device_ptr = &digitalOutputs_pinout[deviceIndex];           
        break;
        case RGB_LEDS:          
            device_ptr = &RGBled_pinout[deviceIndex];           
        break;
        case UART:           
             device_ptr = &UARTS_pinout[deviceIndex];       
        break;

    };
   return device_ptr; 
}
    UART_DEV* accessUART_device(uint32_t UART_index){
        UART_DEV *uart_ptr;
        uart_ptr = &UARTS[UART_index];
        return uart_ptr;
    }


#endif