#ifndef __BUTTONS_H__
#define __BUTTONS_H__
    /*standard includes */
    #include <stdlib.h>
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdint.h>
    #include "testHAL.h"
    typedef enum ERROR{
        OPEN, 
        SHORT,
        NA
    }error_status;

    typedef enum TYPE{
        DI,
        AI,
        INT
    }button_type;

    typedef struct BUTTON{

        uint32_t        VALUE;
        error_status    ERROR;
        button_type     TYPE;
        uint16_t        THRESH_LOW;
        uint16_t        THRESH_HIGH;
        HAL_DINS        ID;
        struct BUTTON  *NEXT;

    }BUTTON;

    /*function prototypes*/
    uint32_t newDigitalButton(HAL_DINS pin);
    uint8_t readButton(uint32_t button);
    int processButtons( void );


#endif