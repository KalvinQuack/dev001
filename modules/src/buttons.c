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
BUTTON* buttonList = NULL;
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
uint32_t newDigitalButton( HAL_DINS pin, button_state state){
    BUTTON* button = malloc(sizeof(BUTTON)); 
    if(pin < IN_TOTAL_DI){
        /*initialize ID*/
        button->ID = pin;
        /*initialize ERROR*/
        button->ERROR = NA;
        /*circular linked list*/
        if(buttonList == NULL){
            button->NEXT = button;
            buttonList = button;
        }else{
            BUTTON* tracer = buttonList;
            while(buttonList->NEXT != tracer){
                buttonList = buttonList->NEXT;
            }
            button->NEXT = buttonList->NEXT;
            buttonList->NEXT = button;
        }
        /*initialize TYPE, THRESH*/
        button->TYPE = DI;
        button->THRESH_HIGH = 0;
        button->THRESH_LOW = 0; 
        button->VALUE = 0xb00d1e;   
    }
    switch(state){
        case NC:
            digitalInput_config(BINARY_NC, true, pin);
        break;
        case NO:
            digitalInput_config(BINARY_NO, true, pin);
        break;
    };
    /*return the pointer address in uint32_t*/
    return (uint32_t)button;
}

/**********************************************
 * Method:  readButton(uint32_t button)
 * 
 * Description: 
 *              
 * 
 * Notes:
 * 
 * Returns: uint8_t
 * 
**********************************************/
uint8_t readButton(uint32_t button){
    BUTTON* temp = (BUTTON*)button;
    switch(temp->TYPE){
        case DI: temp->VALUE = readPin_digital(temp->ID);
        break;
        case AI:
        break;
    };
    return temp->VALUE;
}
