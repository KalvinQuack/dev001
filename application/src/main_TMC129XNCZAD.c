/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
//standard includes 
#include <stdint.h>
#include <stdbool.h>
//hardware abstraction layer include
#include "dev001HAL.h"//module includes
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
#include "system.h"
#include "common.h"    
#include "string.h"
    #include <stdarg.h>
    #include <stdio.h>

uint32_t input01 = IN_01_DI;
uint32_t input02 = IN_02_DI;
uint32_t input03 = IN_03_DI;



SEMAPHORE s = {1, NULL};
SEMAPHORE DIN = {1, NULL};
char compare[1024];


#ifndef __PROCESS_SETUP__
#define __PROCESS_SETUP__
    static void proc01( void ){
        while(1){
            //digitalInput_process();
            //serial_printf("Proc 1: Active \n");
            //task_sleep(&DIN);
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
            //digitalOutput_control(0, getVal_button(input01));
            kernel_delay(5);

            
        }
    }
    static void proc03( void ){
        while(1){
           
            
            //serial_printf("Proc 3: Active \n");
            serial_read(compare);
            
            if(!strcmp(compare, "ON"))
            {
                digitalOutput_control(0, ON);
                serial_printf("led on\n");
            }else if(!strcmp(compare, "OFF")){
                digitalOutput_control(0, OFF);
            }else if(!strcmp(compare, "MASTER CONTROL"))
            {
                serial_printf("ENTER PASSWORD: \n");
                bool x = false;
                while(!x)
                {
                    
                    if(!strcmp(compare, "PASSWORD")){
                        x = true;
                    }else serial_read(compare);
                }serial_printf("ACCESS GRANTED");



            
            }

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
       button_create(IN_01_DI, NC);
       button_create(IN_02_DI, NC);
       button_create(IN_03_DI, NC);
        
        
    }
#endif 





    int main()
{   

    OS_init();
    init_machine();
    test();
    
    
    kernel_fork(&proc04, 6);
    kernel_fork(&proc02, 3);
    kernel_fork(&proc03, 5);
    //kernel_fork(&proc01, 7);
    start_machine();
    while(1){

    }
    return 0;
}

