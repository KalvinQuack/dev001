/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
//standard includes 
#include <stdint.h>
#include <stdbool.h>
//hardware abstraction layer include
#include "dev001HAL.h"
//module includes
#include "system.h"
#include "application.h"
//operating system
#include "KOS.h"
#include "digitalOutput_interface.h"
#include "digitalInput_interface.h"
#include "systemControl_interface.h"
#include "UART_interface.h"
#include "buttons.h"
#include "dev001HAL.h"
#include "BSP.h"
#include "main_TMC129XNCZAD.h"
#include "serial.h"

#include "common.h"

uint32_t input01 = IN_01_DI;
uint32_t input02 = IN_02_DI;
uint32_t input03 = IN_03_DI;



SEMAPHORE s = {1, NULL};
SEMAPHORE DIN = {1, NULL};

hardwareSystem* machine;

#ifndef __INTERRUPT_HANDLERS__


static void SYS_ISR( void ){

    system_enableInterrupts(false);
    system_enableSysTick(false);
    kernel_tick();
    if(scheduler())system_triggerPendSV();
    system_enableInterrupts(true);
    system_enableSysTick(true);
    
}

/* INTERRUPT HANDLERS */
#define __INTERRUPT_HANDLERS__
#endif

#ifndef __HARDWARE_SETUP__
#define __HARDWARE_SETUP__
    static void setupHardware( void ){
        /*singleton system instance*/
        system_init();
        system_configClock(_25mhz, mhz_480, 60000000);
        system_configSysTick(10, &SYS_ISR);
        system_initPeripherals();
        system_initUART();
        uart_create(UART_SYS);
        uart_create(UART_0);
        uart_config(UART_SYS,system_getClock(), 115200, PAR_NONE, STP_ONE, LEN_8);

        digitalOutput_config(OUT_01_DO, PUSH_PULL);
        digitalOutput_config(OUT_02_DO, PUSH_PULL);
        digitalOutput_config(OUT_03_DO, PUSH_PULL); 
    }

    static void setupDigital_inputs( void )
    {
        if(digitalInput_init_All())
        {
            digitalInput_config_ALL( true, normallyClosed);
        }
    }

#endif

#ifndef __PROCESS_SETUP__
#define __PROCESS_SETUP__
    static void proc01( void ){
        while(1){
            digitalInput_process();
            //serial_printf("Proc 1: Active \n");
            task_sleep(&DIN);
        }
    }
    static void proc02( void ){
        while(1){
            //put code here
            //serial_printf("Proc 2: Active \n");
            if(!getVal_button(input01))
            {
                serial_printf("BUTTON ONE ACTIVE \n");
            }
            digitalOutput_control(OUT_01_DO, getVal_button(input01));
            kernel_delay(5);

            
        }
    }
    static void proc03( void ){
        while(1){
            
            //serial_printf("Proc 3: Active \n");
            kernel_delay(5);

        }
    }
    static void proc04( void ){
        while(1){
            //uart_send(UART_SYS);
            kernel_delay(5);
            //put code here
        }
    }
    static void proc05( void ){
        while(1){
            //put code here
        }
    }
    static void proc06( void ){
        while(1){
            //put code here
        }
    }
    static void proc07( void ){
        while(1){
            //put code here
        }
    }
    static void proc08( void ){
        while(1){
            //put code here
        }
    }


#endif

#ifndef __TEST_SETUP__
#define __TEST_SETUP__
    static void test(){
       button_config(IN_01_DI, NC);
       button_config(IN_02_DI, NC);
       button_config(IN_03_DI, NC);
        
        
    }
#endif 




int main()
{   

    OS_init();
    setupHardware();
    setupDigital_inputs();
    test();

    //button01 = button_create(IN_01_DI, normallyClosed);
    //button02 = button_create(IN_02_DI, normallyClosed);
    kernel_fork(&proc04, 6);
    kernel_fork(&proc02, 3);
    kernel_fork(&proc03, 5);
    kernel_fork(&proc01, 7);
    system_enableInterrupts(true);
    system_enableSysTick(true);
    while(1){

    }
    return 0;
}

