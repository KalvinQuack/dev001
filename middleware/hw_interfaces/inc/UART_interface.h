#ifndef __UART_INTERFACE_H__
#define __UART_INTERFACE_H__
    #include <stdint.h>
    #include <stdbool.h>

    #include "dev001HAL.h"
    #define BUFF_SIZE 1024
    typedef struct UART_struct{

        uint8_t circBuff[BUFF_SIZE];
        uint32_t write_head;
        uint32_t write_tail;
        uint32_t read_head;
        uint32_t read_tail;
        uint32_t count;
        bool     buffFull;
        
    }uart_comm;


    void UART_config    ( HAL_UARTS device, 
                          bool interrupt, 
                          uint32_t baudRate, 
                          uint32_t clk 
                        );
    void enable_UART    ( HAL_UARTS device );
    void disable_UART   ( HAL_UARTS device );
    uint8_t send_UART   ( HAL_UARTS device );
    uint8_t recieve_UART( HAL_UARTS device );
#endif