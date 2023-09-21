#ifndef __UART_INTERFACE_H__
#define __UART_INTERFACE_H__
    #include "common.h"

    #include "dev001HAL.h"
/*     #define BUFF_SIZE 1024

    typedef enum buffLock
    {
        LOCKED, 
        UNLOCKED
    }buffLock; */

    typedef enum _parity
    {
        PAR_NONE, 
        PAR_EVEN, 
        PAR_ODD, 
        PAR_ONE, 
        PAR_ZERO

    }parity;
    typedef enum _stopBit
    {
        STP_ONE, 
        STP_TWO
        
    }stopBit;

    typedef enum _dataBit
    {
        LEN_8, 
        LEN_7, 
        LEN_6, 
        LEN_5

    }dataBit;
    

    typedef struct _uart uart;

    int     uart_create( uint32_t id );
    void    uart_send( uint32_t id);
    int     uart_insertBuff(char data, uint32_t id);
    int     uart_checkLock( uint32_t id);
    void    uart_lockBuff( uint32_t id );
    void    uart_unlockBuff( uint32_t id );
    void    uart_process(uint32_t id);
    void uart_read(uint32_t id);
    int     uart_config(uint32_t id,  uint32_t clockSource, uint32_t baud, parity uart_par, stopBit uart_stop, dataBit uart_dataLen);
    int uart_config_ALL(uint32_t clockSource, uint32_t baud, parity uart_par, stopBit uart_stop, dataBit uart_dataLen);
    int uart_init_ALL( void );
    char* uart_get( uint32_t _id, char* buffer);
    bool uart_dataAvail( uint32_t id);

#endif /* __UART_INTERFACE_H__ */
