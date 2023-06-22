/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __SERIAL_C__
#define __SERIAL_C__

    #include "serial.h"
    #include "UART_interface.h"
    #include "dev001HAL.h"
    #include "string.h"
    #include <stdarg.h>
    #include <stdio.h>

    extern uart_comm uart_obj[UART_TOTAL];
    
/**********************************************
 * Method:  uint8_t serial_printf(char *string, ...)
 * 
 * Description: concatenates a string to then be 
 * inserted into a circular buffer. 
 *              
 * 
 * Notes: tread lightly with this function, 
 * it takes a lot of resources 
 * 
 * Returns: uint8_t
 * 
**********************************************/
    uint8_t serial_printf(char *string, ...){

        uart_comm* uart_buff =  &uart_obj[SYSTEM_UART];
        va_list args;
        char temp[BUFF_SIZE] = "\0";
        /*decode and convert args into chars*/
        va_start(args, string);
            vsprintf(temp, string, args);
        va_end(args); 
        
        if((uart_buff->write_head+1)%BUFF_SIZE == uart_buff->write_tail){
            uart_buff->buffFull = true;
            return 0;
        } 

        for(int i = 0; i < strlen(temp);i++){
            if((uart_buff->write_head+1)%BUFF_SIZE != uart_buff->write_tail){
                uart_buff->circBuff[uart_buff->write_head] = temp[i];
                uart_buff->write_head = (uart_buff->write_head+1)%BUFF_SIZE;
                uart_buff->count = uart_buff->count++;
            }else{
                uart_buff->buffFull = true;
                return 0;                   
            }
        }

        return 1;
    }

#endif