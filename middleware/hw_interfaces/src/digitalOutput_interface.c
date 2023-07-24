/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __DIGITAL_OUTPUT_INTERFACE_C__
#define __DIGITAL_OUTPUT_INTERFACE_C__
    /*standard includes*/
    #include <stdio.h>
    #include <stdbool.h>
    #include <stdlib.h>
    /*environment includes*/
    #include "dev001HAL.h"
    #include "BSP.h"
    #include "driverlib/gpio.h"
    #include "digitalOutput_interface.h"

    void digitalOutput_config(HAL_DOUTS index, sourceType type){
        PINOUT *device = accessDevice_pinout(DIGITAL_OUTPUTS, (uint32_t)index);
        switch(type){
            case OPEN_DRAIN:
                GPIOPinTypeGPIOOutputOD(
                        device->device_port,    //device port specified in pinmap 
                        device->device_pin      //device pin specified in pinmap
                        );
            break;
            case PUSH_PULL:
                GPIOPinTypeGPIOOutput(
                    device->device_port,    //device port specified in pinmap 
                    device->device_pin      //device pin specified in pinmap
                );
            break;
 
        };
    }

    void digitalOutput_control(HAL_DOUTS index, outputState val){
        PINOUT *device = accessDevice_pinout(DIGITAL_OUTPUTS, (uint32_t)index);
        if(val){
            GPIOPinWrite(device->device_port, device->device_pin, device->device_pin);
        }else GPIOPinWrite(device->device_port, device->device_pin, !(device->device_pin));
        
    }
#endif