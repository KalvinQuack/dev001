#ifndef __LEDS_H__
#define __LEDS_H__
    #include "common.h"


    typedef enum{
        ON, 
        OFF
    }ledState;

    uint32_t led_new(uint32_t BSP_pin, ledState startingState);
    void RGBled_new(uint32_t Rid, uint32_t Gid, uint32_t Bid);
    void led_dim(uint32_t id, uint32_t val);
    void led_control(uint32_t id, ledState state);
    
    /*
        create and led struct with the id place holder
        a subscriber function and value function 

        check type of led 
    */
#endif 