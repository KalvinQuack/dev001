/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __SYSTEM_CONTROL_INTERFACE__
#define __SYSTEM_CONTROL_INTERFACE__
    /*standard includes*/
    #include <stdlib.h>
    #include <stdint.h>
    #include <stdbool.h>
    /*environment includes*/
    #include "driverlib/sysctl.h"
    #include "driverlib/systick.h"
    #include "driverlib/interrupt.h"
    #include "inc/hw_ints.h"
    #include "systemControl_interface.h"
    

    uint8_t peripheralInit(uint32_t peripheral){
        if(SysCtlPeripheralPresent(peripheral)){
            if(SysCtlPeripheralReady(peripheral)){
                return 1;
            }else{
                SysCtlPeripheralEnable(peripheral);
                while(!SysCtlPeripheralReady(peripheral)){}
                return 1;

            } 
        }else return 0;
    }
    #ifdef DEVICE_TM4C123
    void SystemClockConfig(){}
    #else
   uint32_t systemClockInit(bool externalOsc, XTAL_FREQ desiredFrequency_xtal, OSC_SOURCE oscillatorSource, bool enablePLL, PLL_FREQ pllFrequency_type, uint32_t desiredFrequency_hz){
    uint32_t sysClock;
    if(externalOsc && (oscillatorSource == MAIN_OSC)){
            switch(desiredFrequency_xtal){
                case _5MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_5MHZ);
                break;
                case _6MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_6MHZ);
                break;
                case _8MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_8MHZ);
                break;
                case _10MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_10MHZ);
                break;
                case _12MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_12MHZ);
                break;
                case _16MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_16MHZ);
                break;
                case _18MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_18MHZ);
                break;
                case _20MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_20MHZ);
                break;
                case _24MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_24MHZ);
                break;
                case _25MHZ_:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                        SYSCTL_USE_OSC,
                                        SYSCTL_XTAL_25MHZ);
                break;
                case _CUSTOM_:
                    /* if using PLL the desired frequency can be anything between
                        5Mhz-25Mhz*/
                    if(enablePLL){
                        switch(pllFrequency_type){
                            case VCO_320_MHZ:
                                sysClock = SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                                    SYSCTL_USE_PLL|
                                                    SYSCTL_CFG_VCO_320,
                                                    desiredFrequency_hz);
                            break;
                            case VCO_480_MHZ:
                                sysClock =SysCtlClockFreqSet( SYSCTL_OSC_MAIN|
                                                    SYSCTL_USE_PLL|
                                                    SYSCTL_CFG_VCO_480,
                                                    desiredFrequency_hz);
                            break;
                        }
                    }else sysClock = 0; 
                break;
            };
        }else{
            switch(oscillatorSource){
                case INT_OSC:
                    if(enablePLL){
                        switch (pllFrequency_type){
                            /*is using PLL the desired frequency can be anything between
                                16Mhz-320Mhz*/
                            case VCO_320_MHZ:
                              sysClock = SysCtlClockFreqSet( SYSCTL_OSC_INT|
                                                    SYSCTL_USE_PLL|
                                                    SYSCTL_CFG_VCO_320,
                                                    desiredFrequency_hz);
                            break;
                            case VCO_480_MHZ:
                            /*is using PLL the desired frequency can be anything between
                                16Mhz-480Mhz*/
                                sysClock = SysCtlClockFreqSet( SYSCTL_OSC_INT|
                                                    SYSCTL_USE_PLL|
                                                    SYSCTL_CFG_VCO_480,
                                                    desiredFrequency_hz);
                            break;
                        };
                    }else{
                        sysClock = SysCtlClockFreqSet( SYSCTL_OSC_INT|
                                            SYSCTL_USE_OSC,
                                            desiredFrequency_hz);

                    }
                break;
                /*  Cannot use PLL with low frequency oscillator
                    Tiva C Series TM4C129 User Manual pg 237    */
                case INT30_OSC:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_INT30|
                                        SYSCTL_USE_OSC,
                                        desiredFrequency_hz);
                break;
                /*  Cannot use PLL with HIB Module Oscillator 
                    Tiva C Series TM4C129 User Manual pg 237  */
                case EXT32_OSC:
                    sysClock = SysCtlClockFreqSet( SYSCTL_OSC_EXT32|
                                        SYSCTL_USE_OSC,
                                        desiredFrequency_hz);
                break;
            };
        }
        return sysClock;    
    }

    void enable_NVIC( void ){
        IntMasterEnable();
    }

    void disable_NVIC( void ){
        IntMasterDisable();
    }

    void config_sysTick( uint32_t interval_ms, uint32_t clockFreq_hz){
        float desiredInterval = ((float)interval_ms/1000)*clockFreq_hz;
        if(!desiredInterval || desiredInterval > 16777216){
            while(1){
                //error handling
            }
        }
        SysTickPeriodSet((uint32_t)desiredInterval);
    }

    void enable_sysTick(uint8_t enable, uint8_t enableInterrupt, void (*handler)(void)){
        if(enableInterrupt){
            SysTickIntRegister(handler);
            IntPrioritySet(FAULT_SYSTICK, 0);
            SysTickIntEnable();
        }
        SysTickEnable();
    }

    void disable_sysTick_int( void ){
        SysTickIntDisable();
    }

    void enable_sysTick_int( void ){
        SysTickIntEnable();
    }

    void enable_PendSV ( void ){
        IntPendSet(FAULT_PENDSV);
    }
    #endif
    

#endif