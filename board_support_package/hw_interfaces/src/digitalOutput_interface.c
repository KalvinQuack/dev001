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
    #include "observer.h"

    static digitalOutput* head = NULL;
    struct _digitalOutput
    {
        uint32_t    port;
        uint8_t     pin;
        uint32_t    val;
        uint8_t     id;
        observer* subscriber;


        digitalOutput *next;
    };

    static int _usageCheck( uint32_t _id)
    {
        digitalOutput* tracer = head; 
        if(head == NULL)return OK;
        else{
            while(tracer->next  !=  NULL){
                if(tracer->id != _id)return KO;
                else tracer = tracer->next;
            }
            return OK;
        }        
    }

    static void insertNode( digitalOutput** head, digitalOutput* node)
    {
        if(*head == NULL){
            *head = node;
            return;
        }
        digitalOutput* tracer = *head;
        while(tracer->next != NULL){
            tracer = tracer->next;
        }
        tracer->next = node;       
    }


    int digitalOutput_create(uint32_t _id)
    {
        if(_id > DIGITAL_OUTPUT_TOTAL || !(_usageCheck(_id))) return KO;
        digitalOutput* me = malloc(sizeof(digitalOutput));
        me->id = _id;
        me->pin = GPIO_outputMap[_id][PIN];
        me->port = GPIO_outputMap[_id][PORT];
        me->val = 0xDEADBEEF;
        me->subscriber = NULL;
        me->next = NULL;

        insertNode(&head, me);
        return OK;
        
    }

    int digitalOutput_config( uint32_t _id, sourceType _type)
    {
        digitalOutput* tracer = head; 
        if(head == NULL)return KO;
        else{
            while(tracer->id  !=  _id){
                tracer = tracer->next;
            }
        }

        switch(_type)
        {
            case OPEN_DRAIN:
                GPIOPinTypeGPIOOutputOD(tracer->port, tracer->pin);
            break;
            case PUSH_PULL:
                GPIOPinTypeGPIOOutput(tracer->port, tracer->pin);
            break;
        }

        return OK;
    }

    int digitalOutput_control(uint32_t _id, outputState val)
    {

        digitalOutput* tracer = head; 
        if(head == NULL)return KO;
        else{
            while(tracer->id  !=  _id){
                tracer = tracer->next;
            }
        }
        
        if(val){
            GPIOPinWrite(tracer->port, tracer->pin, tracer->pin);
        }else GPIOPinWrite(tracer->port, tracer->pin, !(tracer->pin));
        return OK;
    }
#endif