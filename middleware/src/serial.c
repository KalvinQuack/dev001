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

    
    #define SERIAL_LIMIT 1024
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

        
        va_list args;
        char temp[SERIAL_LIMIT] = "\0";
        /*decode and convert args into chars*/
        va_start(args, string);
            vsprintf(temp, string, args);
        va_end(args); 

        if(uart_checkLock(UART_SYS)){
          uart_send(UART_SYS);
            return KO;
        }
        else
        {
            uart_lockBuff(UART_SYS);
            for(int i = 0; i < strlen(temp);)
            {
                if(uart_insertBuff(temp[i], UART_SYS))i++;
                else {
                    uart_unlockBuff(UART_SYS);
                    uart_send(UART_SYS);
                    return KO;
                }
            }
            uart_unlockBuff(UART_SYS);
            
        }

        uart_send(UART_SYS);
        return OK;
    }
/**********************************************
 * Method: 
 * 
 * Description: 
 * 
 * Notes: 
 * 
 * Returns: 
 * 
**********************************************/
    char* serial_read(char* string)
    {   
        for(int i = 0; string[i] != '\0'; i++)
        {
            string[i] = '\0';
        }

        if(uart_dataAvail(UART_SYS))
        {
            uart_get(UART_SYS, string); 
            return string;
            
        }
       return NULL;
    }

#endif