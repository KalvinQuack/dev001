/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE
*/
//standard includes 
#include <stdint.h>
#include <stdbool.h>
#include <main_TMC129XNCZAD.h>
//hardware abstraction layer include
#include "testHAL.h"
//module includes
#include "system_init.h"
#include "application.c"
//operating system
#include "KOS.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "inc/hw_ints.h"
#include "UART_interface.h"
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
uint32_t clockSrc;
char k = 'm';
void init_machine( void ){
    clockSrc = init_systemClock();
    init_peripherals();
    init_sysTick(true, 10, clockSrc);
    config_UART(SYSTEM_UART, false, 9600, clockSrc);
    app_config();
    init_interrupts(true);
     
}
int process_digitalInputs ( void ){
    while(1){
        processButtons();
    }
}
int process_application ( void ){
    while(1){
        send_UART(SYSTEM_UART);
    }
}
int process_app( void ){
    while(1){
        //serial_print("t");
    }
    
}

int main()
{   
    kernel_init();
    kernel_fork((int)process_application, 2);
    kernel_fork((int)process_digitalInputs, 2);
    kernel_fork((int)process_app, 2);
    init_machine();
    while(1){};
    return 0;
}

