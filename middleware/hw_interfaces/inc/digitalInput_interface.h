#ifndef __DIGITAL_INPUT_INTERFACE__
#define __DIGITAL_INPUT_INTERFACE__
    /* standard includes */
    #include <stdint.h>
    #include <stdbool.h>
    /*environment*/
    #include "dev001HAL.h"
    #include "util/common.h"
    #include "driverlib/pin_map.h"
    #include "driverlib/gpio.h"
    #include "driverlib/interrupt.h"
    typedef enum inputTypes {
        normallyClosed,  //0 normal state -> 1, active state -> 0
        normallyOpen ,  //1 normal state -> 0, active state -> 1
    }inputTypes;


    typedef struct __digitalInput{
        uint32_t    perph;
        uint32_t    port;
        uint32_t    pin;
        uint32_t    val;
        bool        (*interruptStatus)(struct __digitalInput*);
        void        (*read)(struct __digitalInput*);
        void        (*config)(bool interrupt, void(*ISR)(void), bool internalPull, inputTypes type, struct __digitalInput* me);
        void        (*destroy)(struct __digitalInput*);
        int        (*clearInt)(struct __digitalInput*);
        
    }digitalInput;

    /*FUNCTION PROTOTYPES*/
    digitalInput* digitalInput_create(uint32_t perph, uint32_t port, uint32_t pin);
    
/*     void digitalInput_config                (   
                                             inputTypes           type,   
                                             uint8_t              internalPull,
                                             HAL_DINS             index);

    uint8_t     readPin_digital             (HAL_DINS index);
    void        processDigital_inputs       ( void );
    void        digitalInterrupts_enable    ( bool enable, void(*pfunction)(void));
    void        digitalInterrupts_clear     ( void ); */
    

    

    

#endif 