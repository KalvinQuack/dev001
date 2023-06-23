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
   
    #include "digitalInput_interface.h"
    /* interface includes */

   void __read(digitalInput* me){
        me->val = (GPIOPinRead(me->port, me->pin) && me->pin);
        //notify when created observer/subject
   }
  
    void __destroy(digitalInput* me){
        if(me != NULL){
            free(me);
            me = NULL;
        }
    }

    bool __getInterrupt(digitalInput *me){
        return GPIOIntStatus(me->port, true);
    }

    int __clearInterrupt(digitalInput* me){
            GPIOIntClear(me->port, me->pin);
            return OK;
    }

    void __config(bool interrupt, void(*ISR)(void), bool internalPull, inputTypes type, struct __digitalInput* me){
        switch(type){
            case normallyClosed:
                if(internalPull){
                    GPIOPadConfigSet(me->port, me->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPD);
                }else GPIOPadConfigSet(me->port, me->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
            break;
            case normallyOpen :
                if(internalPull){
                    GPIOPadConfigSet(me->port, me->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
                }else GPIOPadConfigSet(me->port, me->pin, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD);
            break;
        }
        if(interrupt){
            GPIOIntTypeSet(me->port, me->pin, GPIO_BOTH_EDGES);
            GPIOIntRegister(me->port, ISR);
            GPIOIntEnable(me->port, me->pin);
        }else me->interruptStatus = NULL;
    }



    digitalInput* digitalInput_create(uint32_t __perph, uint32_t __port, uint32_t __pin){
        digitalInput* me = (digitalInput*)malloc(sizeof(*me));
        me->perph = __perph;
        me->port = __port;
        me->pin = __pin;
        me->val = 0xDEADBEEF;
        me->config = (void(*)(bool, void(*)(void), bool, inputTypes, struct __digitalInput*))__config;
        me->read = (void(*)(struct __digitalInput*))__read;
        me->destroy = (void(*)(struct __digitalInput*))__destroy;
        me->clearInt = (int(*)(struct __digitalInput*))__clearInterrupt;
        me->interruptStatus = (bool(*)(struct __digitalInput*))__getInterrupt;
        return me;
    }
#endif