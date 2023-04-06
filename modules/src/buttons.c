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
extern digitalInput digitalInputs[IN_TOTAL_DI];
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
uint32_t newDigitalButton( HAL_DINS pin ){
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
    digitalInput_config(BINARY_NO, false, pin);
    /*return the pointer address in uint32_t*/
    return (uint32_t)button;
}
/**********************************************
 * Method:  processButtons( void )
 * 
 * Description: 
 *              
 * 
 * Notes:
 * 
 * Returns: 0
 * 
**********************************************/
int processButtons( void ){
    if(buttonList != NULL){
        readDigitalPin(buttonList->ID, BINARY_NO);
        buttonList->VALUE = digitalInputs[buttonList->ID].value;
        buttonList = buttonList->NEXT;
        }
    return 0;
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
    return temp->VALUE;
}
