#ifndef __BUTTONS_H__
#define __BUTTONS_H__
    /*standard includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdint.h>
    
    #include "dev001HAL.h"
  
    typedef enum _state
    {
        NC, 
        NO
    }button_state;
    typedef enum _error
    {
        OPEN, 
        SHORT,
        NA
    }button_error;

    typedef enum _type
    {
        DI,
        AI,
    }button_type;

    typedef struct __button button;

    /*FUNCTION PROTOTYPES*/
    void button_config(HAL_DINS __inputPin, button_state __state);
    uint32_t getVal_button(HAL_DINS __inputPin);

    





#endif