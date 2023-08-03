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
#include "dev001HAL.h"

button* head = NULL;

struct _button
{
    uint32_t id; //unique indentifier for button struct
    uint32_t value;
    button_error status;
    button_type type;
    button_state state;
    uint32_t key; //key used to communicate with board level interfaces 
    observer* subscriber; //observer 
    struct _button* next;
    void(*subscribe)(struct _button*, HAL_DINS pin);
    void(*destroy)(struct _button*);
    void(*config)(struct _button*, button_state);
    
};



int32_t getVal_button(uint32_t pin)
{
    button* tracer = head;
    while(tracer->key != pin){
        tracer = tracer->next;
    }if(tracer->value != 0xDEADBEEF){
        return tracer->value;
    }
    return -1;
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

static void _destroy(button* me)
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

void _subscribe_DI(button* me)
{
    digitalInput_subscribe(me->key, me->subscriber);
}

static void _config(button* me, button_state _state)
{
    me->state = _state;
    me->type = DI;
   
}

static bool _usageCheck(uint32_t _id)
{
    button* tracer = head;
    if(tracer = NULL)return OK;

    while(tracer->next != NULL){
        if(tracer->id = _id) return KO;
        tracer = tracer->next;
    }
    return OK;
    
}




uint32_t button_create(uint32_t _key, button_state _state)
{
    button* me   = (button*)malloc(sizeof(button));
    me->id  = (_key | 0xA );
    me->key = _key;
    me->state = _state;
    me->status = NA;
    me->type =  DI;
    me->destroy = (void(*)(button*))_destroy;
    me->config = (void(*)(struct _button*, button_state))_config;
    me->value = 0xDEADBEEF;
    me->subscriber = observer_create(me, (void(*)(uint32_t, observer*))test);
    me->next = NULL;
    _subscribe_DI(me);
    insertButton(&head, me);
    return me->id;
    
}







