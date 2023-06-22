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
        #ifndef _DIGITAL_INPUTS_
        #define _DIGITAL_INPUTS_
        /*DIGITAL INPUTS*/
            typedef enum DIGITAL_INPUTS{
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
            typedef enum DIGITAL_OUTPUTS{
                OUT_01_DO, //0
                OUT_02_DO, //1
                OUT_03_DO, //2
                OUT_04_DO, //3
                OUT_05_DO, //4
                OUT_06_DO, //5
                OUT_TOTAL_DO //total number of digital outputs
            }HAL_DOUTS;
        
        #endif

        #ifndef _UARTS_
        #define _UARTS_
            typedef enum UARTS{
                SYSTEM_UART,
                UART_01,
                UART_TOTAL
            }HAL_UARTS;
        #endif
    #endif
#endif



