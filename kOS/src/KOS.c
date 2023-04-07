/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/

/*standard includes*/
#include <stdint.h>
#include <stdbool.h>

/*environment includes*/
#include "KOS.h"
/**********************************************
 * Method:  OS_idle ( void )
 * 
 * Description: is the idle proc
 * lowest priority proc
 * Notes:
 * 
 * Returns: none
 * 
**********************************************/
void OS_idle ( void ){
    while(1){
        //put cpu to sleep state?
    };
}
/**********************************************
 * Method:  OS_init( void )
 * 
 * Description: inits the number of threads
 * and forks process 0 as the idle thread
 * 
 * Notes:
 * 
 * Returns: none
 * 
**********************************************/
void OS_init( void ){
    kernel_init();
    //lowest process (idle process)
    kernel_fork(&OS_idle, 0);
}
/**********************************************
 * Method:  P( SEMAPHORE *s)
 * 
 * Description: checks to see if critical 
 * region is protected, blocks proc if true
 * 
 * Notes:
 * 
 * Returns: none
 * 
**********************************************/
void P( SEMAPHORE *s){
    /*atomic function*/
    disable_IRQ();
    s->value--;
    if(s->value < 0){
        block(s);
    }
    enable_IRQ();
}    
/**********************************************
 * Method:  V(SEMAPHORE *s)
 * 
 * Description: signals process to be ready 
 * if critical region is not locked
 * 
 * Notes:
 * 
 * Returns: none
 * 
**********************************************/
void V(SEMAPHORE *s){
    /*atomic function*/
    disable_IRQ();
    s->value++;
    if(s->value >= 0){
        signal(s);
    }
    enable_IRQ();
}