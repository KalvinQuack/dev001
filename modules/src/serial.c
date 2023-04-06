/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __SERIAL_C__
#define __SERIAL_C__

    #include "serial.h"
    #include "UART_interface.h"
    #include "testHAL.h"
    #include "string.h"
    extern uart_comm uart_obj[UART_TOTAL];
    
    uint8_t serial_write( const char *format, ...){

        uart_comm* uart_buff =  &uart_obj[SYSTEM_UART];
        va_list args;
        char temp[BUFF_SIZE] = "\0";

        /*decode and convert args into chars*/
        va_start(args, format);
            vsprintf(temp, format, args);
        va_end(args); 

         if((uart_buff->write_head+1)%BUFF_SIZE == uart_buff->write_tail){
          uart_buff->buffFull = true;
            return 0;
            //buffer is full
        } 
        /*run through temporary buffer and add chars into uart buffer*/
         for(int i = 0; i < strlen(temp); i++){
            uart_buff->circBuff[uart_buff->write_head] = temp[i];
            uart_buff->write_head = (uart_buff->write_head+1);
        }
        return 1;
    }

    uint8_t serial_print(char *string){

        uart_comm* uart_buff =  &uart_obj[SYSTEM_UART];
        //va_list args;
        //char temp[BUFF_SIZE] = "\0";
        /*decode and convert args into chars*/
        //va_start(args, format);
            //vsprintf(temp, format, args);
        //va_end(args); 

         if((uart_buff->write_head+1)%BUFF_SIZE == uart_buff->write_tail){
          uart_buff->buffFull = true;
            return 0;
            //buffer is full
        } 
        /*run through temporary buffer and add chars into uart buffer*/
         for(int i = 0; i < strlen(string); i++){
            uart_buff->circBuff[uart_buff->write_head] = string[i];
            uart_buff->write_head = (uart_buff->write_head+1);
        }
        return 1;
    }
#endif