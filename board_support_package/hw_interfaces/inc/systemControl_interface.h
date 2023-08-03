#ifndef __SYSTEM_CONTROL_INTERFACE_H__
#define __SYSTEM_CONTROL_INTERFACE_H__
    /* standard includes */
    #include "common.h"

    
    typedef enum __oscType{
        _4mhz, 
        _5mhz, 
        _6mhz, 
        _8mhz, 
        _10mhz, 
        _12mhz, 
        _16mhz, 
        _18mhz, 
        _20mhz, 
        _24mhz, 
        _25mhz, 
        _internal, 
        _internalLow, 
        _hibernate, 
        source_total
    }oscType;

    typedef enum __oscSource{

        sourceExternal,   //external oscillator      
        sourceInteral,    //16 Mhz internal oscillator 
        sourceInternal_low,  //low frequency internal oscillator 
        sourceHibernate   //32.786 kHz oscillator (only available with deviced with the hibernation module)

    }oscSource;

    typedef enum __PLLfrequency{

        mhz_320,    //pll fixed frequency 320 Mhz
        mhz_480,     //pll fixed frequency 480 Mhz
        unused
        
    }PLLfrequency;

    typedef enum __sysSource{
        pll_source,
        main_source,
    }sysSource;

    typedef struct __hardwareSystem{
        uint32_t        clockFreq;
        uint32_t        desiredFreq;
        oscType         oscType;
        PLLfrequency    PLL;
        sysSource       systemSource;
        uint32_t        systickValue;
        uint32_t        (*clkConfig)(oscType type,PLLfrequency enablePLL,uint32_t desiredFreq,struct __hardwareSystem*);
        uint32_t        (*systickConfig)(uint32_t interval_ms, void(*handler)(void), struct __hardwareSystem*);
        void            (*systickEnable)(bool enable);
        void            (*triggerSwitch)( void );
        void            (*enableInts)(bool enable);
        void            (*perphInit)(uint32_t perph); 
    }hardwareSystem;

    #ifdef DEVICE_TM4C123
    #else
    /*
    FUNCTION PROTOTYPES
    */
    hardwareSystem* getSystem   ( void );
    int system_init ( void );
    int system_configClock ( oscType type, PLLfrequency enablePLL, uint32_t desiredFreq);
    int system_configSysTick(uint32_t interval_ms, void(*handler)(void));
    int system_initPeripherals ( void );
    int system_initUART( void );
    void system_enableInterrupts( bool );
    void system_enableSysTick( bool );
    void system_triggerPendSV( void );
    uint32_t system_getClock( void );
 
    





    
    #endif 
    
#endif