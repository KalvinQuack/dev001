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
#include "digitalOutput_interface.h"
#include "digitalInput_interface.h"
SEMAPHORE s = {1, NULL};
SEMAPHORE DIN = {1, NULL};

static void DIN_ISR( void ){
    digitalInterrupts_clear();
    task_wakeup(&DIN);
}

static void setupHardware( void ){
    uint32_t clockSrc = init_systemClock(100000000);
    init_peripherals();
    init_sysTick(true, 2, clockSrc); 
    UART_config(SYSTEM_UART, false, 115200, clockSrc);
    digitalOutput_config(OUT_01_DO, PUSH_PULL);
    digitalOutput_config(OUT_02_DO, PUSH_PULL);
    digitalOutput_config(OUT_03_DO, PUSH_PULL); 
}

static void setupInterrupts( void ){
    digitalInterrupts_enable(true, &DIN_ISR);
}

static void init_machine( void ){
    setupHardware();
    setupInterrupts();
 
}

static void start_system( void ){
    init_interrupts(true);
}

static void process_digital (void ){
    while(1){
        kernel_delay(5);//10 ms debounce
        processDigital_inputs();
        task_sleep(&DIN);       
    }
}

static void process_application ( void ){
    while(1){
    P(&s);
      digitalOutput_control(OUT_01_DO, 0);
      //app();
      kernel_delay(5);
    V(&s);  
      
    }
}

static void process_app( void ){
    while(1){
       digitalOutput_control(OUT_01_DO, 1);
       send_UART(SYSTEM_UART);
       kernel_delay(1);      
    }
    
}

void test01(){
    int a = 1;
}
void test02(){
    int a = 1;
}
int main()
{   

    app* newApp = app_create((char*)'X', (void(*)(void))test01, (void(*)(void))test02);
    OS_init();
    init_machine();
    
    kernel_fork(&process_app, 3);
    kernel_fork(&process_application, 2);
    kernel_fork(&process_digital, 4);
    start_system();
    while(1){};
    return 0;
}

