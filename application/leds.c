#include "leds.h"
#include "HAL/inc/HAL_io.h"
#include "board_configuration.h"
#include "HAL/inc/HAL_pwm.h"

 typedef struct led{
    uint32_t id;
    gpioStruct_t* pin;
    uint32_t value;
    struct led* next;
} ledStruct_t;

static ledStruct_t* head = NULL;
static uint32_t idGen = 0;


void appendLed(ledStruct_t** head, ledStruct_t* led){
   if(*head == NULL){
        *head = led;
   }else{
    ledStruct_t* tracer = *head;
    while(tracer->next != NULL){
        tracer = tracer->next;
    }
    tracer->next = led;
   }
}

uint32_t led_new(uint32_t BSP_pin, ledState startingState){
    ledStruct_t* me = (ledStruct_t*)malloc(sizeof(ledStruct_t));
    gpioStruct_t* dev = get_pin(BSP_pin);
    me->id = (dev->pin+dev->port);
    me->value = startingState;
    me->pin = dev;

    appendLed(&head, me);
    return me->id;
}

void led_control( uint32_t id, ledState state){
    ledStruct_t* tracer = head;
    while(tracer->id != id){
        tracer = tracer->next;
    }
    switch(tracer->pin->pull){
        case EXT_PULLUP:
            HAL_writeIO(tracer->pin, 0);
        break;
        case EXT_PULLDOWN:
            HAL_writeIO(tracer->pin, 1);
            break;
        case INT_PULLUP:
            HAL_writeIO(tracer->pin, 1);
            break;
        case INT_PULLDOWN:
            HAL_writeIO(tracer->pin, 0);
            break;
    }
    
}
 