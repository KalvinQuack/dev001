#ifndef __DIGITAL_OUPUT_INTERFACE_H__
#define __DIGITAL_OUPUT_INTERFACE_H__
    /*standard includes*/
    #include <stdio.h>
    #include <stdbool.h>

    /*environment includes*/
    #include "testHAL.h"

    /*enum types*/
    typedef enum outputState{
        OFF,    // 0
        ON,     // 1
    }outputState;

    typedef enum sourceType{
        OPEN_DRAIN, //0 can drive only one state
        PUSH_PULL   //1 can drive two states
    }sourceType;
    

    /*function prototypes*/
    void digitalOutput_config(HAL_DOUTS index, sourceType type);
    void digitalOutput_control(HAL_DOUTS index, outputState val);

#endif