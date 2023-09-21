#ifndef __LEDS_H__
#define __LEDS_H__
    #include "common.h"

    typedef struct __led led;
    typedef enum _state
    {
        ON,
        OFF
    }state;

    void led_dim(uint32_t id, uint32_t val);
    void led_control(uint32_t id, state val);
    
    /*
        create and led struct with the id place holder
        a subscriber function and value function 

        check type of led 
    */
#endif 