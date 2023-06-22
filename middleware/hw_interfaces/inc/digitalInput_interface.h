#ifndef __DIGITAL_INPUT_INTERFACE__
#define __DIGITAL_INPUT_INTERFACE__
    /* standard includes */
    #include <stdint.h>
    #include <stdbool.h>
    /*environment*/
    #include "dev001HAL.h"
    typedef enum inputTypes {
        BINARY_NC,  //0 normal state -> 1, active state -> 0
        BINARY_NO,  //1 normal state -> 0, active state -> 1
    }inputTypes;


/*     typedef struct digitalInput{
        uint8_t value;
    }digitalInput; */

    /*FUNCTION PROTOTYPES*/
    void digitalInput_config                (   
                                             inputTypes           type,   
                                             uint8_t              internalPull,
                                             HAL_DINS             index);

    uint8_t     readPin_digital             (HAL_DINS index);
    void        processDigital_inputs       ( void );
    void        digitalInterrupts_enable    ( bool enable, void(*pfunction)(void));
    void        digitalInterrupts_clear     ( void );
    

    

    

#endif 