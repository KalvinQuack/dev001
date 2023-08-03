#ifndef __DIGITAL_OUPUT_INTERFACE_H__
#define __DIGITAL_OUPUT_INTERFACE_H__
    /*standard includes*/
    #include "common.h"


    /*enum types*/
    typedef enum outputState{
        OFF,    // 0
        ON,     // 1
    }outputState;

    typedef enum sourceType{
        OPEN_DRAIN, //0 can drive only one state
        PUSH_PULL   //1 can drive two states
    }sourceType;
    
    typedef struct _digitalOutput digitalOutput;
    /*function prototypes*/
    int digitalOutput_create    (uint32_t id);
    int digitalOutput_config    (uint32_t id, sourceType type);
    int digitalOutput_control   (uint32_t id, outputState val);

#endif