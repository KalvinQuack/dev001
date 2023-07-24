#ifndef __DIGITAL_INPUT_INTERFACE__
#define __DIGITAL_INPUT_INTERFACE__
    /* standard includes */
    #include "common.h"
    /*HAL*/
    #include "dev001HAL.h"

    typedef enum inputTypes 
    {
        normallyClosed,  //0 normal state -> 1, active state -> 0

        normallyOpen ,  //1 normal state -> 0, active state -> 1

    }inputTypes;

    typedef struct _digitalInput digitalInput;

    /*FUNCTION PROTOTYPES*/
    int         digitalInput_init_All( void );
    int         digitalInput_config_ALL(bool internalPull, inputTypes type);
    int         digitalInput_create(uint8_t pin);
    void        digitalInput_config( uint8_t pin, bool internalPull, inputTypes type);
    uint32_t    digitalInput_read( void );
    int         digitalInput_subscribe(uint8_t pin, void* subscriber);
    void        digitalInput_process( void );

    

    

    

#endif 