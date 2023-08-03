/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __SYSTEM_INIT_C__
#define __SYSTEM_INIT_C__

    /*environment includes*/
    #include "system.h"
    #include "systemControl_interface.h"
    #include "digitalInput_interface.h"
    #include "digitalOutput_interface.h"
    #include "UART_interface.h"
    #include "dev001HAL.h"
    #include "KOS.h"
    #include "serial.h"


    static char* startup[] = {
       "kkkkkkkk                OOOOOOOOO        SSSSSSSSSSSSSSS \n",
       "k::::::k              OO:::::::::OO    SS:::::::::::::::S\n",
       "k::::::k            OO:::::::::::::OO S:::::SSSSSS::::::S\n",
       "k::::::k           O:::::::OOO:::::::OS:::::S     SSSSSSS\n",
       "k:::::k    kkkkkkkO::::::O   O::::::OS:::::S   \n",
       "k:::::k   k:::::k O:::::O     O:::::OS:::::S \n",
       "k:::::k  k:::::k  O:::::O     O:::::O S::::SSSS \n",
       "k:::::k k:::::k   O:::::O     O:::::O  SS::::::SSSSS\n",
       "k::::::k:::::k    O:::::O     O:::::O    SSS::::::::SS \n",
       "k:::::::::::k     O:::::O     O:::::O       SSSSSS::::S \n",
       "k:::::::::::k     O:::::O     O:::::O            S:::::S\n",
       "k::::::k:::::k    O::::::O   O::::::O            S:::::S\n",
       "k::::::k k:::::k   O:::::::OOO:::::::OSSSSSSS     S:::::S\n",
       "k::::::k  k:::::k   OO:::::::::::::OO S::::::SSSSSS:::::S\n",
       "k::::::k   k:::::k    OO:::::::::OO   S:::::::::::::::SS\n",
       "kkkkkkkk    kkkkkkk     OOOOOOOOO      SSSSSSSSSSSSSSS\n"
    };

                    

    

    static void SYS_ISR( void )
    {

        system_enableInterrupts(false);
        system_enableSysTick(false);
        kernel_tick();
        if(scheduler())system_triggerPendSV();
        system_enableInterrupts(true);
        system_enableSysTick(true);
        
    }

    static void setupDigital_inputs( void )
    {
        if(digitalInput_init_All())
        {
            digitalInput_config_ALL(INTERNAL_PU);
        }
    }

    static void setupUART_modules( void )
    {
/*         if(uart_create(UART_SYS))
        {
            uart_config(UART_SYS, system_getClock(), 115200, PAR_NONE, STP_ONE, LEN_8);
        } */
        if(uart_init_ALL())
        {
            uart_config_ALL(system_getClock(), 9600, PAR_NONE, STP_ONE, LEN_8);
        } 
    }

    static void setupDigital_outputs( void )
    {
        digitalOutput_create(0);
        digitalOutput_config(0, PUSH_PULL);

    }



    void init_machine( void ){
        system_init();
        system_configClock(_25mhz, mhz_480, 60000000);
        system_initPeripherals();
        system_configSysTick(10, &SYS_ISR);
        setupDigital_inputs();
        setupDigital_outputs();
        setupUART_modules();

    }

    void start_machine( void ){
        system_enableInterrupts(true);
        for(uint8_t i = 0; i < (sizeof(startup)/sizeof(startup[0])); i++)
        {
            serial_printf(startup[i]);
        }
        system_enableSysTick(true);
    }
    

#endif

                                 
