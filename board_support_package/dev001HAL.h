/*
This is a test file under LOR Mobile Controls
THIS IS NOT DISTRIBUTED FOR COMMERCIAL USE
*/

#ifndef HAL
    #define HAL
    //standard includes
    #include <stdint.h>
    /*application specific includes*/
    #ifdef _DEV001_DEVICE_
    //#include "buttons.h"
    //#define OR_HEX(VAL1, VAL2)((VAL1)|(VAL2))

        #ifndef _DIGITAL_INPUTS_
        #define _DIGITAL_INPUTS_
        /*DIGITAL INPUTS*/
        

        

        #define DI_01 0
        #define DI_02 1
        #define DI_03 2
        #define DI_04 3
        #define DI_05 4

        #define DI_TOTAL 5

        #define UART_SYS 0
        #define UART_0 1
        #define UART_TOTAL 2

        #define DO_01 0
        #define DO_02 1
        #define DO_03 2
        #define DO_04 3
        #define DO_05 4


        #define LED_01 0 
        #define LED_02 1
        #define LED_03 2
        #define LED_04 3
        #define LED_05 4

        










        
        
            typedef enum DIGITAL_INPUTS
            {
                IN_01_DI, //0
                IN_02_DI, //1
                IN_03_DI, //2 
                IN_04_DI, //3
                IN_05_DI, //4
                IN_TOTAL_DI //total number of digital inputs
            }HAL_DINS;
        #endif

        #ifndef _OUTPUTS_
        #define _OUTPUTS_
        /*DIGITAL OUTPUTS*/
            typedef enum DIGITAL_OUTPUTS
            {
                OUT_01_DO, //0
                OUT_02_DO, //1
                OUT_03_DO, //2
                OUT_04_DO, //3
                OUT_05_DO, //4
                OUT_06_DO, //5
                OUT_TOTAL_DO //total number of digital outputs
            }HAL_DOUTS;
        
        #endif
        #ifndef _ANALOG_INPUTS_
        #define _ANALOG_INPUTS_
        /*DIGITAL INPUTS*/
            typedef enum ANALOG_INPUTS{
                IN_01_AI, //0
                IN_02_AI, //1
                IN_03_AI, //2 
                IN_04_AI, //3
                IN_05_AI, //4
                IN_TOTAL_AI //total number of digital inputs
            }HAL_AINS;
        #endif

        #ifndef _SERIAL_
        #define _SERIAL_/* 
            typedef enum UARTS{
                UART_01,
                UART_02,
                UART_TOTAL
            }HAL_UARTS; */
        #endif

    #endif
#endif



