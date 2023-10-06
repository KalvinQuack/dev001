#include "pinmap.h"
#include "TivaWare_C_Series-2.2.0.295/inc/hw_memmap.h"
#include "TivaWare_C_Series-2.2.0.295/driverlib/gpio.h"

#ifdef PART_TM4C129XNCZAD

    uint32_t ports[NUM_OF_PORTS] ={
        GPIO_PORTA_BASE, 
        GPIO_PORTB_BASE, 
        GPIO_PORTC_BASE, 
        GPIO_PORTD_BASE, 
        GPIO_PORTE_BASE, 
        GPIO_PORTF_BASE, 
        GPIO_PORTG_BASE, 
        GPIO_PORTH_BASE, 
        GPIO_PORTJ_BASE, 
        GPIO_PORTK_BASE, 
        GPIO_PORTL_BASE, 
        GPIO_PORTM_BASE, 
        GPIO_PORTN_BASE, 
        GPIO_PORTP_BASE, 
        GPIO_PORTQ_BASE, 
        GPIO_PORTR_BASE, 
        GPIO_PORTS_BASE, 
        GPIO_PORTT_BASE
    };
    
    uint32_t pins[NUM_OF_PINS] = {
        GPIO_PIN_0, 
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4, 
        GPIO_PIN_5, 
        GPIO_PIN_6, 
        GPIO_PIN_7
    };


#endif 
#ifdef PART_TM4C123GH6PM
    uint32_t ports[NUM_OF_PORTS] ={
        GPIO_PORTA_BASE, 
        GPIO_PORTB_BASE, 
        GPIO_PORTC_BASE, 
        GPIO_PORTD_BASE, 
        GPIO_PORTE_BASE, 
        GPIO_PORTF_BASE, 
    };

    uint32_t pins[NUM_OF_PINS] = {
        GPIO_PIN_0, 
        GPIO_PIN_1,
        GPIO_PIN_2,
        GPIO_PIN_3,
        GPIO_PIN_4, 
        GPIO_PIN_5, 
        GPIO_PIN_6, 
        GPIO_PIN_7
    };

    
#endif 