/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
//standard includes 
#include <stdint.h>
#include <stdbool.h>
//hardware abstraction layer include
//#include "dev001HAL.h"//module includes
#include "system.h"
#include "application.h"
//operating system
#include "KOS.h"
/* #include "digitalOutput_interface.h"
#include "digitalInput_interface.h"
#include "systemControl_interface.h"
#include "UART_interface.h"
#include "buttons.h"
#include "dev001HAL.h"
#include "MCU.h" 
*/
#include "main_TMC129XNCZAD.h"
#include "serial.h"
#include "system.h"
#include "common.h"    
#include "string.h"
#include <stdarg.h>
#include <stdio.h>

#include "tests/unit_test/unit_test01.h"





SEMAPHORE s = {1, NULL};
SEMAPHORE DIN = {1, NULL};
char compare[1024];


#ifndef __MAIN_TMC129XNCZAD_C__
#define __MAIN_TMC129XNCZAD_C__
    static void proc01( void ){
        while(1){
            //digitalInput_process();
            //serial_printf("Proc 1: Active \n");
            //task_sleep(&DIN);
        }
    }
    static void proc02( void ){
        while(1){

            
        }
    }
    static void proc03( void ){
        while(1){
           

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


#endif/* __MAIN_TMC129XNCZAD_C__ */

#ifndef __TEST_SETUP__
#define __TEST_SETUP__
    static void test(){
/*        button_create(IN_01_DI, NC);
       button_create(IN_02_DI, NC);
       button_create(IN_03_DI, NC); */
        
        
    }
#endif/* __MAIN_TMC129XNCZAD_C__ */





    int main()
{   

/*     OS_init();
    init_machine();
    test();
    
    
    kernel_fork(&proc04, 6);
    kernel_fork(&proc02, 3);
    kernel_fork(&proc03, 5);
    //kernel_fork(&proc01, 7);
    start_machine(); */
    board_config_test01();

    while(1){

    }
    return 0;
}

