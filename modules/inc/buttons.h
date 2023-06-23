#ifndef __BUTTONS_H__
#define __BUTTONS_H__
    /*standard includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include "dev001HAL.h"
    #include "digitalInput_interface.h"
    #include "main_TMC129XNCZAD.h"
    //#include "util/inc/observer.h"
    typedef enum __state{
        NC, 
        NO
    }button_state;
    typedef enum __error{
        OPEN, 
        SHORT,
        NA
    }button_error;

    typedef enum __type{
        DI,
        AI,
    }button_type;

    typedef struct __button{
        uint32_t value;
        button_error status;
        button_type type;
        button_state state;
        HAL_DINS ID;
        void(*subscribe)(struct __button*, void*);
        void(*destroy)(struct __button*);
        void(*config)(struct __button*, button_state, HAL_DINS);
    }button;

    
    /*function prototypes*/
    button* button_create(HAL_DINS __inputPin, button_state __state);

    





#endif