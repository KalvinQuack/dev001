#ifndef __DIGITAL_INPUT_INTERFACE__
#define __DIGITAL_INPUT_INTERFACE__
    /* standard includes */
    #include "common.h"
    /*HAL*/
    #include "dev001HAL.h"
    typedef enum _inputType
    {
        INTERNAL_PU,
        INTERNAL_PD, 
        EXTERNAL_PUD

    }inputType;

    typedef struct _digitalInput digitalInput;

    /*FUNCTION PROTOTYPES*/
    int         digitalInput_init_All( void );
    int         digitalInput_config_ALL(inputType type);
    int         digitalInput_create(uint8_t id);
    void        digitalInput_config( uint8_t pin, inputType type);
    uint32_t    digitalInput_read( void );
    int         digitalInput_subscribe(uint8_t pin, void* subscriber);
    void        digitalInput_process( void );

    

    

    

#endif 