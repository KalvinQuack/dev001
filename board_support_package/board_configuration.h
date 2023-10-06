#ifndef __BOARD_CONFIGURATION_H__
#define __BOARD_CONFIGURATION_H__

    #include "util/common.h"
    #include "HAL/inc/HAL_io.h"
    #include "HAL/inc/HAL_pwm.h"

   #ifdef BOARD_IS_DEVELOPY
    #endif 

    #ifdef BOARD_DEVELOPY_M2
    #endif 
    #define NUM_PORTS 12


 
    uint8_t BSP_init_hardware ( void );
    gpioStruct_t* get_pin( uint32_t index);

    extern port_map[NUM_PORTS];


#endif/* __BOARD_CONFIGURATION_H__ */
