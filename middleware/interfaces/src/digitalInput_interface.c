/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __digital_interface_C__
#define __digital_interface_C__
    /* environment includes */
    
    #include "digitalInput_interface.h"
    /*device specific driver*/
    #include "driverlib/gpio.h"
    #include "driverlib/interrupt.h"
    /*utils*/
    #include "subject.h"
    #include "MCU.h"

//! ---------------INTERNAL USAGE PORTION--------------- !
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    static digitalInput* head = NULL;
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
       struct _digitalInput 
    {                           
        uint32_t    port;       
        //* gpio port source 
        uint8_t    pin;        
        //* gpio pin source 
        uint32_t    val; 
        //* id of the object 
        uint8_t     id;      
        
        publisher*  subject;    
        
        //bool        (*interruptStatus)(struct _digitalInput*);
        
        void        (*read)(struct _digitalInput*);
 
        void        (*destroy)(struct _digitalInput*);
        
        //void        (*ISR)(void);
        
        
        digitalInput* next;
    };
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    static void insertList( digitalInput** head, digitalInput* node)
    {
        if(*head == NULL){
            *head = node;
            return;
        }
        digitalInput* tracer = *head;
        while(tracer->next != NULL){
            tracer = tracer->next;
        }
        tracer->next = node;
    }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
   static void _read(digitalInput* me)
   {
        me->val = (GPIOPinRead(me->port, me->pin) && me->pin);
        //notify when created observer/subject
   }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    static void _destroy(digitalInput* me)
    {
        if(me != NULL){
            free(me);
            me = NULL;
        }
    }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    static void _process_digitalInput( void )
    {
        digitalInput* tracer = head;
        uint32_t flagPin = GPIOIntStatus(tracer->port, false);
        while(!(tracer->pin & flagPin))
        {
            tracer = tracer->next;
            
        }
                GPIOIntClear(tracer->port, tracer->pin);
                 _read(tracer);
                tracer->subject->notifySubs(tracer->subject, tracer->val);
            
    }
    
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    static void _config(inputType type, digitalInput* me)
    {
        
        uint32_t pullType = 0; 

        switch(type)
        {
            case INTERNAL_PU:
                pullType = GPIO_PIN_TYPE_STD_WPU;
            break;
            case INTERNAL_PD:
                pullType = GPIO_PIN_TYPE_STD_WPD;
            break;
            case EXTERNAL_PUD:
                pullType = GPIO_PIN_TYPE_STD;
            break;
        }

        GPIOPinTypeGPIOInput(me->port, me->pin);
        GPIOPadConfigSet(me->port, me->pin, GPIO_STRENGTH_2MA, pullType);
        GPIOIntTypeSet(me->port, me->pin, GPIO_BOTH_EDGES);
        GPIOIntRegister(me->port, &_process_digitalInput);
        GPIOIntEnable(me->port, me->pin);
    }

    static bool _usageCheck( uint8_t pin)
    {
        digitalInput *tracer = head;
        if(tracer == NULL)return true;
            while(tracer->id != pin){
                if(tracer->next == NULL){
                    return OK;
                }
                tracer = tracer->next;
            }
        return KO;
    }

//! ---------------INTERNAL USAGE PORTION--------------- !


//* ---------------PUBLIC USAGE PORTION---------------*
    int digitalInput_create(uint8_t id)
    {   
        
        //if(id > DIGITAL_INPUT_TOTAL)return KO; //is it a valid pin?
        if(!_usageCheck(id))return KO; //has it already been created?
        digitalInput* me = (digitalInput*)malloc(sizeof(digitalInput));
        me->port = gpio_registerLookup(id);
        me->pin = gpio_pinLookup(id);
        me->id = id;
        me->val = 0xDEADBEEF;
        me->read = (void(*)(digitalInput*))_read;
        me->destroy = (void(*)(digitalInput*))_destroy;
        me->next = NULL;
        me->subject = publisher_create(me, 1);
        insertList(&head, me);
        return OK;
       
    }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    int digitalInput_init_All( void )
    {
        uint8_t portLength = IN_TOTAL_DI;
        uint8_t id;
        
        for(id = 0; id < portLength;)
        {
          if(digitalInput_create(id))id++;
        }
        return OK;
    }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    void digitalInput_config(uint8_t pin, inputType type)
    {
        digitalInput* tracer = head;
        while(tracer->id != pin){
            tracer = tracer->next;
        }
        _config(type, tracer);

    }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    int digitalInput_config_ALL(inputType type)
    {
        digitalInput* tracer = head;
        while(tracer->next != NULL){
            _config(type, tracer);
            tracer = tracer->next;
        }
        return OK;
    }
    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    int digitalInput_subscribe(uint8_t pin, void* subscriber)
    {
        if(pin < DIGITAL_INPUT_TOTAL){
            digitalInput* tracer = head;
            while(tracer->id != pin){
                tracer = tracer->next;
            }
            tracer->subject->subscribe(tracer->subject, (observer*)subscriber);
            return OK;
        }else return KO;
    }

    /**********************************************
     * Method: 
     * 
     * Description: 
     * 
     * Notes: 
     * 
     * Returns: 
     * 
    **********************************************/
    void digitalInput_process( void )
    {
        digitalInput* tracer = head; 
        while(tracer->next != NULL){
            _read(tracer);
            tracer->subject->notifySubs(tracer->subject, tracer->val);
            tracer = tracer->next;
        }
    }
//* ---------------PUBLIC USAGE PORTION---------------*
#endif