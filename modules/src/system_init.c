/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __SYSTEM_INIT_C__
#define __SYSTEM_INIT_C__

    /*standard includes*/
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    /*environment includes*/
    #include "system_init.h"
    #include "systemControl_interface.h"
    #include "testHAL.h"
    #include "pinmap.h"
    #include "KOS.h"
    


    /**********************************************
     * Method:  sysTickHandler( void )
     * 
     * Description: Runs the handler function for 
     * Systick interrupt. Defaulted to context switch function
     *              
     * 
     * Notes: This function is used in conjunction with 
     * kOS
     * 
     * Returns: None
     * 
    **********************************************/
    void sysTickHandler( void ){
        disable_NVIC();
        kernel_tick();//tick down for sleeping procs
        if(scheduler()){
            trigger_PendSV(); //trigger pendSV if next task is not the current
        }
        enable_NVIC();  
    }
    /**********************************************
     * Method:  init_systemClock( void )
     * 
     * Description: Initializes the system clock
     *              
     * 
     * Notes:
     * This function is pre-configured to set the 
     * frequency to 40 Mhz using internal oscillator
     * 
     * Returns: clock rate in Hz
     * 
    **********************************************/
    uint32_t init_systemClock( void ){
        uint32_t clock_config = systemClockInit(

            false,          //not using external osc
            _XTAL_UNUSED_,  //desired ext osc freq unused
            INT_OSC,        //using internal osc
            true,           //enable PLL
            VCO_320_MHZ,    //set the PLL freq to 320 Mhz
            40000000        //desired frequency (hz) 40 Mhz
        );

        if(!clock_config){
            while(1){
                //error handler
            }
        }
       return clock_config; //return system clock in HZ
    }
    /**********************************************
     * Method:  init_digitalInputs( uint32_t index )
     * 
     * Description: Runs through the device pinmap to 
     * initialze the peripheral clocks that are used 
     * as digital inputs
     *              
     * 
     * Notes:
     * 
     * Returns: uint8_t 
     * 
    **********************************************/
    uint8_t init_digitalInputs( uint32_t index ){
        PINOUT *digitalDevice = accessDevice_pinout(DIGITAL_INPUTS, index);
        if(index < IN_TOTAL_DI){
            while(!peripheralInit(digitalDevice->device_peripheral)){}
            return 1;
        }else return 0;
    }
    /**********************************************
     * Method:  init_digitalOutputs( uint32_t index )
     * 
     * Description: Runs through the device pinmap to
     * initialize the peripheral clock that are used as
     * digital outputs
     *              
     * 
     * Notes:
     * 
     * Returns: uint8_t
     * 
    **********************************************/
    uint8_t init_digitalOutputs( uint32_t index ){
        PINOUT *digitalDevice = accessDevice_pinout(DIGITAL_OUTPUTS, index);
        if(index < OUT_TOTAL_DO){
            while(!peripheralInit(digitalDevice->device_peripheral)){}
            return 1;
        }else return 0;
    }
    /**********************************************
     * Method:  init_peripherals( void )
     * 
     * Description: initiliazes all peripherals
     *              
     * 
     * Notes: Only digital inputs and digital outputs 
     * are inlcudes in this function
     * 
     * Returns: uint8_t
     * 
    **********************************************/
    uint8_t init_peripherals( void ){
        /*digital input peripherals*/
        for(int i = 0; i < IN_TOTAL_DI; i++){ 
                init_digitalInputs(i);
        }
        /*digital output peripherals*/
        for(int i = 0; i < OUT_TOTAL_DO; i++){
                init_digitalOutputs(i);
       }
       for(int i = 0; i < UART_TOTAL; i++){
            initPeriph_UART(i);
       }
       return 0;
    }

    /**********************************************
     * Method:  init_sysTick( bool interrupt, uint32_t interval_ms, uint32_t clkSrc )
     * 
     * Description: initializes the systick by configuring the tick rate 
     * and whether or not to generate an interrupt
     *              
     * 
     * Notes:
     * 
     * Returns: uint8_t
     * 
    **********************************************/
    uint8_t init_sysTick( bool interrupt, uint32_t interval_ms, uint32_t clkSrc ){
        if(interrupt){
            config_sysTick(interval_ms, clkSrc);
            enable_sysTick(true, true, &sysTickHandler);
        }else{
            config_sysTick(interval_ms, clkSrc);
            enable_sysTick(true, false, NULL);
        }
        return 0;
    }
    /**********************************************
     * Method:  init_interrupts( bool config )
     * 
     * Description: enables the NVIC
     *              
     * 
     * Notes:
     * 
     * Returns: uint8_t
     * 
    **********************************************/
    uint8_t init_interrupts( bool config ){
        if(config){
            enable_NVIC();
        }else disable_NVIC();

        return 0;
    }
    /**********************************************
     * Method:  initPeriph_UART( bool config )
     * 
     * Description: enables the clock for the GPIO and UART periph
     *              
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
    uint8_t initPeriph_UART( uint32_t index ){
        PINOUT* uart_pins = accessDevice_pinout(UART, index);
        UART_DEV* uart_device = accessUART_device(index);
        /*init peripheral clocks for for both GPIO and UART*/
        peripheralInit(uart_pins->device_peripheral);
        peripheralInit(uart_device->uart_peripheral);

        return 0;
    }
    /**********************************************
     * Method:  enable_IRQ( void )
     * 
     * Description: enables the master NVIC for the processor
     *              
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
    void enable_IRQ( void ){
        enable_NVIC();
    }
    /**********************************************
     * Method:  disable_IRQ( void )
     * 
     * Description: disables the master NVIC for the processor
     *              
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
    void disable_IRQ( void ){
        disable_NVIC();
    }

    void switch_task( void ){
        trigger_PendSV();
    }
#endif