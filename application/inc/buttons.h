#ifndef __BUTTONS_H__
#define __BUTTONS_H__
    /*standard includes */
    #include "common.h"
  
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

    typedef struct _button button;
    typedef struct _smartButton smartButton;

    /*FUNCTION PROTOTYPES*/
    uint32_t button_create(uint32_t id, button_state state);
    void smartButton_config(uint32_t id_1, uint32_t id_2);
    int getVal_button(uint32_t id);

    





#endif