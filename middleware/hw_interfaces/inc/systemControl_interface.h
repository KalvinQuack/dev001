#ifndef __SYSTEM_CONTROL_INTERFACE_H__
#define __SYSTEM_CONTROL_INTERFACE_H__
    /* standard includes */
    #include <stdint.h>
    #include <stdbool.h>
    /*environment includes*/
    typedef enum XTAL_FREQ{

        _5MHZ_, 
        _6MHZ_,
        _8MHZ_, 
        _10MHZ_, 
        _12MHZ_, 
        _16MHZ_, 
        _18MHZ_,
        _20MHZ_,
        _24MHZ_, 
        _25MHZ_,
        _CUSTOM_,
        _XTAL_UNUSED_
    }XTAL_FREQ;

    typedef enum OSC_SOURCE{

        MAIN_OSC,   //external oscillator      
        INT_OSC,    //16 Mhz internal oscillator 
        INT30_OSC,  //low frequency internal oscillator 
        EXT32_OSC   //32.786 kHz oscillator (only available with deviced with the hibernation module)
    }OSC_SOURCE;

    typedef enum PLL_FREQ{

        VCO_480_MHZ,    //pll fixed frequency 480 Mhz
        VCO_320_MHZ,     //pll fixed frequency 320 Mhz
        PLL_UNUSED
        
    }PLL_FREQ;

    /*FUNCTION PROTOTYPES*/
    uint8_t peripheralInit(uint32_t peripheral);
    #ifdef DEVICE_TM4C123
    #else
    /*SYSTEM CLOCK*/
    uint32_t systemClockInit    ( bool externalOsc, XTAL_FREQ desiredFrequency_xtal, OSC_SOURCE oscillatorSource, bool enablePLL, 
                                  PLL_FREQ pllFrequency_type, uint32_t desiredFrequency_hz);
    /*SYSTEM TICK*/
    void config_sysTick         ( uint32_t interval_ms, uint32_t clockFreq_hz );
    void enable_sysTick         ( uint8_t enable, uint8_t enableInterrupt, void(*handler)(void));
    void disable_sysTick_int    ( void );
    void enable_sysTick_int     ( void );
    void enable_NVIC            ( void );
    void disable_NVIC           ( void );
    void trigger_PendSV          ( void );


    
    #endif 
    
#endif