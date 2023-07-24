/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __UART_INTERFACE_C__
#define __UART_INTERFACE_C__

    #include "UART_interface.h"
    #include "driverlib/uart.h"
    #include "driverlib/sysctl.h"
    #include "driverlib/gpio.h"
    #include "util/buffers/buffer.h"
    #include "driverlib/interrupt.h"
    #include "inc/hw_ints.h"

    #include "BSP.h"
    
    #define MAX_PINS 2
    struct _uart
    {
        uint32_t    id;
        uint32_t    baud;
        uint32_t    base;
        bool        overunError;
        bool        breakError;
        bool        parityError;
        bool        framingError;
        bool        recieveTimeout;
        void        (*ISR)(void);
        uint32_t    txpin;
        uint32_t    rxpin;
        buffer*     buff;
        uart*       next;
        void        (*config)(uint32_t clockSource, uint32_t baud, uart* me, parity uart_par, stopBit uart_stop, dataBit uart_dataLen);

        
    };

    static uart* head = NULL;
    static const char init[] = "UART INIT \n";
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
    uart* getUart(uint32_t id)
    {
        uart* tracer = head;
        while(tracer->id != id)
        {
            tracer = tracer->next;
        }
        return tracer;
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
    static void _interruptHandler( void )
    {
        uart* tracer = head;
        while(tracer->next != NULL)
        {
            uint32_t flag = UARTIntStatus(tracer->base, false);
            if(flag & UART_INT_TX)
            {
                //UARTIntClear(tracer->base, UART_INT_TX);
                uart_process(tracer->id);
                UARTIntDisable(tracer->base, UART_INT_TX);
            }
            tracer = tracer->next;
        }
        
        
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
    static void _config( uint32_t clockSource, uint32_t baud, uart* me, parity uart_par, stopBit uart_stop, dataBit uart_dataLen)
    {
        uint32_t parity_bit = 0;
        uint32_t stop_bit = 0;
        uint32_t data_bits = 0;

        switch(uart_dataLen){
            case LEN_8:
                data_bits = UART_CONFIG_WLEN_8;
            break;
            case LEN_7:
                data_bits = UART_CONFIG_WLEN_7;
            break; 
            case LEN_6:
                data_bits = UART_CONFIG_WLEN_6;
            break;
            case LEN_5:
                data_bits = UART_CONFIG_WLEN_5;
            break;
        }
        switch(uart_par)
        {
            case PAR_NONE:
                parity_bit = UART_CONFIG_PAR_NONE;
            break;
            case PAR_EVEN:
                parity_bit = UART_CONFIG_PAR_EVEN;
            break;
            case PAR_ODD:
                parity_bit = UART_CONFIG_PAR_ODD;
            break;
            case PAR_ONE:
                parity_bit = UART_CONFIG_PAR_ONE;
            break;
            case PAR_ZERO:
                parity_bit = UART_CONFIG_PAR_ZERO;
            break;
        }
        switch(uart_stop)
        {
            case STP_ONE:
                stop_bit = UART_CONFIG_STOP_ONE;
            break;
            case STP_TWO:
                stop_bit = UART_CONFIG_STOP_TWO;
            break;

        }
        UARTConfigSetExpClk(me->base, clockSource, baud, data_bits|parity_bit|stop_bit);
        
        UARTFIFOEnable(me->base);
        UARTTxIntModeSet(me->base, UART_TXINT_MODE_EOT);
            //IntEnable(INT_UART6_TM4C129);
        UARTIntRegister(me->base, &_interruptHandler);
        UARTIntEnable(me->base, UART_INT_TX); 
           for(int i = 0; i < sizeof(init); i++)
           {
            UARTCharPutNonBlocking(me->base, init[i]);
           }
           
        
            //UARTCharPutNonBlocking(me->base, 'Test FIFO');
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
    static void insertList( uart** head, uart* node)
    {
        if(*head == NULL){
            *head = node;
            return;
        }
        uart* tracer = *head;
        while(tracer->next != NULL){
            tracer = tracer->next;
        }
        tracer->next = node;
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
    static int usageCheck(uint32_t id)
    {
        uart* tracer = head;
        if(head == NULL)return OK;
        else{
            while(tracer->next != NULL){
                if(tracer->id == id) return KO;
                tracer = tracer->next;

            }
            return OK;
        }
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
    int uart_create( uint32_t id ){

        if(id > UART_TOTAL || !usageCheck(id))return KO;
 
        uart* new = (uart*)malloc(sizeof(uart));
        new->id  = id;
        new->base = uart_lookup[id][uart_base];
        new->rxpin = uart_lookup[id][uart_rx];
        new->txpin = uart_lookup[id][uart_tx];
        new->baud = 0;
        new->buff = buffer_create();
        new->config = (void(*)(uint32_t clockSource, uint32_t baud, uart* me, parity uart_par, stopBit uart_stop, dataBit uart_dataLen))_config;
        new->next = NULL;
        insertList(&head, new);
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
    int uart_config(uint32_t id, uint32_t clockSource, uint32_t baud, parity uart_par, stopBit uart_stop, dataBit uart_dataLen)
    {
        
        getUart(id)->config(clockSource, baud, getUart(id), uart_par, uart_stop, uart_dataLen);
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
    int uart_checkLock( uint32_t id)
    {
        
        if(getUart(id)->buff->lock == LOCKED)return OK;
        else return KO;
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
    void uart_lockBuff( uint32_t id)
    {
        getUart(id)->buff->lock = LOCKED;
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
    void uart_unlockBuff( uint32_t id)
    {
        getUart(id)->buff->lock = UNLOCKED;       
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
   int uart_insertBuff( char data, uint32_t id)
    {
        uart* tracer = getUart(id);

        if((tracer->buff->write_head+1)%BUFF_SIZE != tracer->buff->write_tail){
            tracer->buff->circBuff[tracer->buff->write_head] = data;
            tracer->buff->write_head = (tracer->buff->write_head+1)%BUFF_SIZE;
            tracer->buff->count = tracer->buff->count+1;
            return OK;
        }else
        {
            tracer->buff->buffFull = true;
            return KO;
        }

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
    void uart_process(uint32_t id)
    {
        uart* tracer = getUart(id);

        while((tracer->buff->write_tail) != (tracer->buff->write_head)){
          if(UARTCharPutNonBlocking(tracer->base, tracer->buff->circBuff[tracer->buff->write_tail])){
            tracer->buff->write_tail = (tracer->buff->write_tail+1)%BUFF_SIZE;
            tracer->buff->count = tracer->buff->count-1;
          }
        }
        tracer->buff->buffFull = false;

    }

    void uart_send( uint32_t id)
    {
        uart* tracer = getUart(id);
        UARTIntEnable(tracer->base, UART_INT_TX);
    }

#endif 