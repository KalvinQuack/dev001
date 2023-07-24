#ifndef __SYSTEM_INIT_H__
#define __SYSTEM_INIT_H__
    /*standard includes*/
    #include <stdlib.h>
    #include <stdint.h>
    #include <stdbool.h>

    /*environment includes*/
   

    /*function prototypes*/
    uint8_t     init_digitalInputs  ( uint32_t index );
    uint8_t     init_digitalOutputs ( uint32_t index );
    uint32_t    init_systemClock    ( uint32_t speed_hz );
    uint8_t     init_sysTick        ( bool interrupt, uint32_t interval, uint32_t clkSrc );
    uint8_t     init_peripherals    ( void );
    uint8_t     init_interrupts     ( bool config );
    void        sysTickHandler      ( void );
    uint8_t     initPeriph_UART     ( uint32_t index );
    void        disable_IRQ         ( void );
    void        enable_IRQ          ( void );
    void        switch_task         ( void );
    
#endif      