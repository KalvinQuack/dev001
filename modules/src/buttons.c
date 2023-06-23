/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
/*standard includes*/

/*environment includes*/
#include "buttons.h"
#include "digitalInput_interface.h"

/*total inputs*/
button* head;
/**********************************************
 * Method:  uint32_t newDigitalButton( HAL_DINS pin )
 * 
 * Description: 
 *              
 * 
 * Notes:
 * 
 * Returns: uint32_t
 * 
**********************************************/

static void __destroy(button* me){
   if(me != NULL){
    free(me);
    me = NULL;
   }
}

static void __config(button* me, button_state __state, HAL_DINS __inputPin){
    me->ID = __inputPin;
    me->state = __state;
    me->type = DI;
    
}


button* button_create(HAL_DINS __inputPin, button_state __state){
    button* me   = (button*)malloc(sizeof(button*));
    me->ID = __inputPin;
    me->state = __state;
    me->status = NA;
    me->type =  DI;
    me->destroy = (void(*)(button*))__destroy;
    me->config = (void(*)(struct __button*, button_state, HAL_DINS))__config;
    me->value = 0xDEADBEEF;
    return me;
      
}



