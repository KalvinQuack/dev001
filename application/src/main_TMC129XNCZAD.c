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
#include "digitalOutput_interface.h"

SEMAPHORE s = {1, NULL};

void critical_section( int x ){
    int a = x;
    for(int i = 0; i < a; i++){
      
    }
}

void init_machine( void ){
    uint32_t clockSrc = init_systemClock();
    init_peripherals();
    init_sysTick(true, 5, clockSrc);  
    config_UART(SYSTEM_UART, false, 9600, clockSrc);
    digitalOutput_config(OUT_01_DO, PUSH_PULL);
    digitalOutput_config(OUT_02_DO, PUSH_PULL);
    digitalOutput_config(OUT_03_DO, PUSH_PULL);  
}
void start_system( void ){
    init_interrupts(true);
}

void process_digitalInputs ( void ){
    while(1){     
    app();
    kernel_delay(1);
      
    }
}
void  process_application ( void ){
    while(1){
      
      //data going to the buffer
      P(&s);
      
      messages();
      digitalOutput_control(OUT_01_DO, 0);
      //kernel_delay(10);
      V(&s);
      kernel_delay(100);
      
      
    }
}
void  process_app( void ){
    while(1){
       
       //data beiong processed and sent via UART
       P(&s);
       send_UART(SYSTEM_UART);
       digitalOutput_control(OUT_01_DO, 1);
       //kernel_delay(10);
       V(&s);
        kernel_delay(1);
        
    }
    
}

int main()
{   
    OS_init();
    init_machine();
    kernel_fork(&process_app, 3);
    kernel_fork(&process_application, 2);
    kernel_fork(&process_digitalInputs, 4);
    app_config();
    start_system();
    while(1){};
    return 0;
}

