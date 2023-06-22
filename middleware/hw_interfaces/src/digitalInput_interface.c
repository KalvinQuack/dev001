/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __digital_interface_C__
#define __digital_interface_C__
    /* standard includes */
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    /* environment includes */
    #include "dev001HAL.h"
    #include "pinmap.h"
    #include "digitalInput_interface.h"
    #include "driverlib/gpio.h"
    #include "driverlib/interrupt.h"
    /* interface includes */
    //#include "systemControl_interface.h"
     struct digitalInput {
        uint8_t value;
    };

    struct digitalInput digitalInputs[IN_TOTAL_DI];

    void digitalInput_config(inputTypes type,
                             uint8_t internalPull, 
                             HAL_DINS index)
    {
        PINOUT *digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, (uint32_t)index);
        switch(type){
            /*binary normally closed switch will display a 0 in the normal state
                and a 1 when activated */
            case BINARY_NO:
                if(index < IN_TOTAL_DI){
                    if(internalPull){
                        GPIOPadConfigSet(
                            digitalDevice->device_port,  //specified port
                            digitalDevice->device_pin,   //specified pin
                            GPIO_STRENGTH_2MA,           //output drive strength (does not affect input)
                            GPIO_PIN_TYPE_STD_WPD        //configures internal weak pullup
                        );    
                    }else{
                        GPIOPadConfigSet(
                            digitalDevice->device_port, //specified port
                            digitalDevice->device_pin,  //specified pin
                            GPIO_STRENGTH_2MA,          //output drive strength (does not affect input)
                            GPIO_PIN_TYPE_STD           //configures standard (ext resistor required)
                        );
                    }                      
                }  
            break;
            /*binary normally closed switch will display a 1 in normal state
                and a 0 when activated*/
            case BINARY_NC:
                if(index < IN_TOTAL_DI){
                    if(internalPull){
                        GPIOPadConfigSet(
                            digitalDevice->device_port,  //specified port
                            digitalDevice->device_pin,   //specified pin
                            GPIO_STRENGTH_2MA,           //output drive strength (does not affect input)
                            GPIO_PIN_TYPE_STD_WPU        //configures internal weak pullup
                        );    
                    }else{
                        GPIOPadConfigSet(
                            digitalDevice->device_port, //specified port
                            digitalDevice->device_pin,  //specified pin
                            GPIO_STRENGTH_2MA,          //output drive strength (does not affect input)
                            GPIO_PIN_TYPE_STD           //configures standard (ext resistor required)
                        );
                    }                      
                } 
            break;
        };
    }
    /**********************************************
     * Method:  void readDigitalPin( HAL_DINS index, inputTypes type );
     * 
     * Description: reads GPIO pin status and stores in
     *              
     * 
     * Notes: private function
     * 
     * Returns: int 
     * 
    **********************************************/
    uint8_t readPin_digital(HAL_DINS index){
        uint32_t val;
        val = digitalInputs[index].value;
        return val; 

    }
    /**********************************************
     * Method:  void processDigital_inputs( void )
     * 
     * Description: Reads specific gpio pin and stores 
     * value into digitalInput linked list.
     *              
     * 
     * Notes:
     * 
     * Returns: None 
     * 
    **********************************************/
    void processDigital_inputs( void ){
        for(HAL_DINS i = 0; i < IN_TOTAL_DI; i++){
            PINOUT* digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, i);
           digitalInputs[i].value = GPIOPinRead(digitalDevice->device_port, digitalDevice->device_pin); 
        }
    }
    /**********************************************
     * Method:  digitalInterrupts_enable( bool enable )
     * 
     * Description: Goes through the hal digital inputs and 
     * enables the interrupts for only the digital pins that are
     * being used on the HAL
     *              
     * 
     * Notes:
     * 
     * Returns: None 
     * 
    **********************************************/   
    void digitalInterrupts_enable( bool enable, void(*pfunction)(void) ){
        if(enable){    
          for(HAL_DINS i = 0; i < IN_TOTAL_DI; i++){
            PINOUT* digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, i);
            GPIOIntEnable   (digitalDevice->device_port, digitalDevice->device_pin);
            GPIOIntTypeSet  (digitalDevice->device_port, digitalDevice->device_pin, GPIO_BOTH_EDGES);
            GPIOIntRegister (digitalDevice->device_port, pfunction);
            }  
        }
    }
    /**********************************************
     * Method:  digitalInterrupts_clear( void )
     * 
     * Description: Combs through digital inputs to clear interrupts
     *              
     * 
     * Notes:
     * 
     * Returns: None 
     * 
    **********************************************/  
    void digitalInterrupts_clear( void ){
        /*comb through each interrupt and clear it if it's digital input*/
        for(HAL_DINS i = 0; i < IN_TOTAL_DI; i++){
            PINOUT* digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, i);
            if(GPIOIntStatus(digitalDevice->device_port, true) == digitalDevice->device_pin){
                GPIOIntClear(digitalDevice->device_port, digitalDevice->device_pin);
            }
        }
    }

#endif