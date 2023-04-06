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
    #include "testHAL.h"
    #include "pinmap.h"
    #include "digitalInput_interface.h"
    #include "driverlib/gpio.h"
    #include "driverlib/interrupt.h"
    /* interface includes */
    //#include "systemControl_interface.h"
    
    
    digitalInput digitalInputs[IN_TOTAL_DI];

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
                    GPIOUnlockPin(digitalDevice->device_port,
                                        digitalDevice->device_pin);
                    GPIOPinTypeGPIOInput(digitalDevice->device_port,
                                        digitalDevice->device_pin);      
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
            case INTERUPT:
            break;
        };
    }
    /**********************************************
     * Method:  void readDigitalPin( HAL_DINS index, inputTypes type );
     * 
     * Description: reads GPIO pin status and stores in
     *              
     * 
     * Notes:
     * 
     * Returns: int 
     * 
    **********************************************/
    void readDigitalPin(HAL_DINS index, inputTypes type){
        PINOUT* digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, index);
        uint32_t val;
        switch(type){
            case BINARY_NC:
                val = GPIOPinRead(
                        digitalDevice->device_port, 
                        digitalDevice->device_pin);

                if(val & digitalDevice->device_pin) val = 1;
                else val = 0;
                digitalInputs[index].value = (uint8_t)val;
            break;
            case BINARY_NO:
                val = GPIOPinRead(
                        digitalDevice->device_port, 
                        digitalDevice->device_pin);

                if(val & digitalDevice->device_pin) val = 1;
                else val = 0;
                digitalInputs[index].value = (uint8_t)val;
            break;
        }

    }
    uint8_t readPin(HAL_DINS index){
        PINOUT* digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, index);
        uint8_t val = GPIOPinRead(digitalDevice->device_port, 
                                digitalDevice->device_pin);
        return val;
    }
    

#endif