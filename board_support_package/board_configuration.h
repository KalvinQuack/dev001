#ifndef __BOARD_CONFIGURATION_H__
#define __BOARD_CONFIGURATION_H__

    #include "util/common.h"
    #include "HAL/inc/HAL_io.h"
    
    extern gpioStruct_t PA1;
    extern gpioStruct_t PA2;
    extern gpioStruct_t PA3;
    extern gpioStruct_t PA4;
    extern gpioStruct_t PB1;
    extern gpioStruct_t PB2;
    extern gpioStruct_t PB3;
    
    

 
    uint8_t BSP_init_hardware ( void );
     



#endif/* __BOARD_CONFIGURATION_H__ */
