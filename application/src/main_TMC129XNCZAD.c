/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/

//standard includes 
#include <stdint.h>
#include <stdbool.h>
#include <main_TMC129XNCZAD.h>
//hardware abstraction layer include
#include "dev001HAL.h"
//module includes
#include "system.h"
#include "application.h"
//operating system
#include "KOS.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "inc/hw_ints.h"
#include "UART_interface.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
//#include "digitalOutput_interface.h"
#include "digitalInput_interface.h"
#include "buttons.h"
#include "dev001HAL.h"
#include "pinmap.h"

SEMAPHORE s = {1, NULL};
SEMAPHORE DIN = {1, NULL};
digitalInput* dins[IN_TOTAL_DI];
button* button01;
button* button02;

static void DIN_ISR( void ){
    for(HAL_DINS i = IN_01_DI; i < IN_TOTAL_DI; i ++){
        dins[i]->clearInt(dins[i]);
    }
    task_wakeup(&DIN);
}

static void setupHardware( void ){
    uint32_t clockSrc = init_systemClock(100000000);
    init_peripherals();
    enable_IRQ();
    init_sysTick(true, 2, clockSrc); 
    //UART_config(SYSTEM_UART, false, 115200, clockSrc);
    //digitalOutput_config(OUT_01_DO, PUSH_PULL);
    //digitalOutput_config(OUT_02_DO, PUSH_PULL);
    //digitalOutput_config(OUT_03_DO, PUSH_PULL); 
}
 void process_digital( void ){
    while(1){
        for(HAL_DINS i = IN_01_DI; i < IN_TOTAL_DI; i++){
            dins[i]->read(dins[i]);
        }
        task_sleep(&DIN);
    }
    
 }



int main()
{   

    OS_init();
    setupHardware();
     for(int i = 0; i < IN_TOTAL_DI; i++){
        PINOUT* bsp = accessDevice_pinout(DIGITAL_INPUTS, (uint32_t)i);
        dins[i] = digitalInput_create(bsp->device_peripheral, bsp->device_port, bsp->device_pin); 
        dins[i]->config(true, &DIN_ISR, false, normallyClosed, dins[i]);
    } 
    //button01 = button_create(IN_01_DI, normallyClosed);
    //button02 = button_create(IN_02_DI, normallyClosed);
    kernel_fork(&process_digital, 3);

    
    //kernel_fork(&process_application, 2);
    //kernel_fork(&process_digital, 4);
    init_interrupts(true);
    while(1){
        
    };
    return 0;
}

