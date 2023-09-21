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
    #include "systemControl_interface.h"
        /*drivers*/
    #include "driverlib/sysctl.h"
    #include "driverlib/systick.h"
    #include "driverlib/interrupt.h"
    #include "driverlib/gpio.h"
    /*deivce includes*/
    #include "inc/hw_ints.h"
    #include "MCU.h"

    static hardwareSystem* machine = NULL;

    uint32_t oscillator[source_total] = 
    {
        SYSCTL_XTAL_4MHZ,
        SYSCTL_XTAL_5MHZ, 
        SYSCTL_XTAL_6MHZ,
        SYSCTL_XTAL_8MHZ,
        SYSCTL_XTAL_10MHZ,
        SYSCTL_XTAL_12MHZ,
        SYSCTL_XTAL_16MHZ,
        SYSCTL_XTAL_18MHZ,
        SYSCTL_XTAL_20MHZ,
        SYSCTL_XTAL_24MHZ,
        SYSCTL_XTAL_25MHZ, 
        SYSCTL_OSC_INT,
        SYSCTL_OSC_INT30,
        SYSCTL_OSC_EXT32
    };

    uint8_t __peripheralInit(uint32_t peripheral){
        if(SysCtlPeripheralPresent(peripheral)){
            if(SysCtlPeripheralReady(peripheral)){
                return OK;
            }else{
                SysCtlPeripheralEnable(peripheral);
                while(!SysCtlPeripheralReady(peripheral)){}
                return OK;

            } 
        }else return KO;
    }

    #ifdef DEVICE_TM4C123
    void SystemClockConfig(){}
    #else
    static uint32_t __config(oscType type, PLLfrequency enablePLL, uint32_t desiredFreq, hardwareSystem* sys){
        if(type < source_total && desiredFreq <= 120000000){
            uint32_t actualFreq = 0;
            switch(type){
                case _internalLow:
                    actualFreq = SysCtlClockFreqSet(oscillator[type]|SYSCTL_USE_OSC, 30000);
                    sys->systemSource = main_source;
                break;

                case _hibernate:
                    actualFreq = SysCtlClockFreqSet(oscillator[type]|SYSCTL_USE_OSC, 32786);
                    sys->systemSource = main_source;
                break;

                default:
                    switch(enablePLL){
                        case mhz_320:
                        if(type != _4mhz && (5000000 <= desiredFreq && desiredFreq <= 320000000)){
                            actualFreq = SysCtlClockFreqSet(oscillator[type]|SYSCTL_USE_PLL|SYSCTL_CFG_VCO_320, desiredFreq);
                            sys->systemSource = pll_source;
                        }
                        break;

                        case mhz_480:
                        if(type != _4mhz && (5000000 <= desiredFreq && desiredFreq <= 480000000)){
                            actualFreq = SysCtlClockFreqSet(oscillator[type]|SYSCTL_USE_PLL|SYSCTL_CFG_VCO_480, desiredFreq);
                            sys->systemSource = pll_source;
                        }else return KO;
                        break;
                        case unused:
                            if(4000000 <= desiredFreq && desiredFreq <= 25000000){
                                actualFreq = SysCtlClockFreqSet(oscillator[type]|SYSCTL_USE_OSC, desiredFreq);
                                sys->systemSource = main_source;
                            }else return KO;
                        break;
                    }
                    
                break;
            }
            sys->oscType = type;
            sys->PLL = enablePLL;
            sys->desiredFreq = desiredFreq;
            sys->clockFreq = actualFreq;
            return OK;
        }else return KO;
    }


    static void __systickEnable( bool enable){
        if(enable){
            SysTickEnable();
        }else SysTickDisable();
    }

    

    static uint32_t __systickConfig( uint32_t interval_ms, void(*handler)(void), hardwareSystem* sys){
        if(sys->clockFreq ==  0xDEADBEEF){
            return KO;
        }
        float desiredInterval = ((float)interval_ms/1000)*(sys->clockFreq);
        if(!(1 <= desiredInterval) && !(desiredInterval <= 16777216))return KO;
        SysTickPeriodSet((uint32_t)desiredInterval);
        if(handler != NULL){
            SysTickIntRegister(handler);
            IntPrioritySet(FAULT_SYSTICK, 0);
            __systickEnable(false);
        }
        sys->systickValue = desiredInterval;
        return OK;
    }


    static void __triggerPendSV( void ){
        IntPendSet(FAULT_PENDSV);
    }

    static void __enableNVIC( bool enable){
        if(enable)IntMasterEnable();
        else IntMasterDisable();
    }

    hardwareSystem* getSystem(void){
        static hardwareSystem instance;
        

        


        return &instance;
    }

    int system_init( void )
    {
        if(machine != NULL)return KO;
        else
        {
            machine = (hardwareSystem*)malloc(sizeof(hardwareSystem));
            machine->clkConfig      = (uint32_t(*)(oscType type,PLLfrequency enablePLL,uint32_t desiredFreq,struct __hardwareSystem*))__config;
            machine->systickConfig  = (uint32_t(*)(uint32_t interval_ms, void(*handler)(void), struct __hardwareSystem*))__systickConfig;
            machine->systickEnable  = (void(*)(bool))__systickEnable;
            machine->triggerSwitch  = (void(*)(void))__triggerPendSV;
            machine->enableInts     = (void(*)(bool))__enableNVIC;
            machine->perphInit      = (void(*)(uint32_t))__peripheralInit;
            machine->enableInts(false);
            machine->clockFreq      = 0xDEADBEEF;
            machine->desiredFreq    = 0xDEADBEEF;
        }
        return OK;//system object has been initiliazed but not config
    }

    int system_configClock( oscType type,PLLfrequency enablePLL,uint32_t desiredFreq )
    {
        if(machine != NULL)
        {
            if(machine->clkConfig(type, enablePLL, desiredFreq, machine))return OK;
            else return KO;
        }else return KO;

    }
    int system_configSysTick(uint32_t interval_ms, void(*handler)(void))
    {
        if(machine != NULL)
        {
            if(machine->systickConfig(interval_ms, handler, machine))return OK;
            else return KO;
        }
    }

    int system_initPeripherals ( void )
    {
        if(machine != NULL)
        {
            uint8_t length = sizeof(peripheralLookup)/sizeof(peripheralLookup[0]);
            for(uint8_t i = 0; i < length;)
            {
                uint32_t peripheral = peripheralLookup[i];
                machine->perphInit(peripheral);
                i++;
            }
            return OK;            
        }else return KO;
    }
    void system_enableInterrupts( bool state){
        if(machine != NULL){
            machine->enableInts(state);
        }
    }

    void system_enableSysTick( bool state){
        if(machine != NULL){
            machine->systickEnable(state);
        }
    }
    void system_triggerPendSV( void )
    {
        if(machine != NULL)
        {
            machine->triggerSwitch();
        }
    }
    int system_initUART( void )
    {
        uint8_t length = sizeof(uartGPIO_lookup)/sizeof(uartGPIO_lookup[0]);
        for(uint8_t i = 0; i<length; i++)
        {
            GPIOPinConfigure(uart_lookup[i][uart_rx]);
            GPIOPinConfigure(uart_lookup[i][uart_tx]);
            GPIOPinTypeUART(uartGPIO_lookup[i][uart_base], uartGPIO_lookup[i][uart_rx]|uartGPIO_lookup[i][uart_tx]);

        }
        return OK;
    }
    uint32_t system_getClock( void )
    {
        if(machine != NULL)
        {
            return machine->clockFreq;
        }else return KO;
    }
    void system_start( void )
    {
        //check through all the precursors to make sure everything is correct
    }
    
    #endif

#endif