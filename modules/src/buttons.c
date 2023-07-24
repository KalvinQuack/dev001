/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
/*standard includes*/

/*environment includes*/
#include "buttons.h"
#include "digitalInput_interface.h"
#include "observer.h"

    button* head = NULL;

struct __button
{
    uint32_t value;
    button_error status;
    button_type type;
    button_state state;
    HAL_DINS ID;
    observer* subscriber; //observer 
    struct __button* next;
    void(*subscribe)(struct __button*, HAL_DINS pin);
    void(*destroy)(struct __button*);
    void(*config)(struct __button*, button_state);
    
};

uint32_t getVal_button(HAL_DINS pin)
{
    button* tracer = head;
    while(tracer->ID != pin){
        tracer = tracer->next;
    }if(tracer->value != 0xDEADBEEF){
        return tracer->value;
    }
    return 0;
}

static void insertButton( button** head, button* node)
{
   if(*head == NULL){
    *head = node;
    return;
   }
   button* tracer = *head;
   while(tracer->next != NULL){
    tracer = tracer->next;
   }
   tracer->next = node;
}

static void __destroy(button* me)
{
   if(me != NULL){
    free(me);
    me = NULL;
   }
}

static void test(uint32_t i, observer* data)
{
    button* this = (button*)(data->data);
    this->value = i;
}

void __subscribe_DI(button* me)
{
    digitalInput_subscribe(me->ID, me->subscriber);
}

static void __config(button* me, button_state __state)
{
    me->state = __state;
    me->type = DI;
   
}

void button_config(HAL_DINS __inputPin, button_state __state)
{
    button* me   = (button*)malloc(sizeof(button));
    //HAL DINS
    me->ID = __inputPin;
    //error state 
    me->state = __state;
    me->status = NA;
    me->type =  DI;
    me->destroy = (void(*)(button*))__destroy;
    me->config = (void(*)(struct __button*, button_state))__config;
    me->value = 0xDEADBEEF;
    me->subscriber = observer_create(me, (void(*)(uint32_t, observer*))test);
    me->next = NULL;
    __subscribe_DI(me);
    insertButton(&head, me);
    
}







