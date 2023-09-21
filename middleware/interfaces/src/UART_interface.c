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
    #include "MCU.h"
    
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
    static const char init[] = "\n                    \n";

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

 

        while(tracer != NULL)
        {
                
            uint32_t flag = UARTIntStatus(tracer->base, true);
            UARTIntClear(tracer->base, flag);


             if((flag & UART_INT_TX))
            {
                //UARTIntClear(tracer->base, UART_INT_TX);
                uart_process(tracer->id);
                UARTIntDisable(tracer->base, UART_INT_TX);
            }

/*             if((flag & UART_INT_RX))
            {
                
                UARTIntClear(tracer->base, UART_INT_RX);
                uart_read(tracer->id);
                
            }  */
             if((flag & UART_INT_RT) || (flag & UART_INT_RX) )
            {
                UARTIntClear(tracer->base, UART_INT_RT | UART_INT_RX);
                uart_read(tracer->id);
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
        
        GPIOPinConfigure(uart_lookup[me->id][uart_rx]);
        GPIOPinConfigure(uart_lookup[me->id][uart_tx]);
        GPIOPinTypeUART(uartGPIO_lookup[me->id][uart_base], uartGPIO_lookup[me->id][uart_rx]|uartGPIO_lookup[me->id][uart_tx]);
        //set up uart module
        UARTConfigSetExpClk(me->base, clockSource, baud, data_bits|parity_bit|stop_bit);

        //set up the interrupt
        UARTFIFOEnable(me->base);
        UARTTxIntModeSet(me->base, UART_TXINT_MODE_EOT);
        UARTIntRegister(me->base, &_interruptHandler);

        
      
        /*
        To use the tx interrupt for UART, prime the buffer with values until 
        it gets triggered when the buffer is finish
        ed sending the last byte of data
        */
        for(uint32_t i = 0; i < sizeof(init); i++)
        {
            UARTCharPut(me->base, init[i]);
        }
             
        UARTIntEnable(me->base,  UART_INT_RX | UART_INT_TX | UART_INT_RT);
                  
           
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
    int uart_create( uint32_t _id ){

        if(_id > UART_TOTAL || !usageCheck(_id))return KO;
 
        uart* new = (uart*)malloc(sizeof(uart));
        new->id  = _id;
        new->base = uart_lookup[_id][uart_base];
        new->rxpin = uart_lookup[_id][uart_rx];
        new->txpin = uart_lookup[_id][uart_tx];
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
    void uart_send( uint32_t id )
    {
        uart* tracer = getUart(id);
        UARTIntEnable(tracer->base, UART_INT_TX);
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
    void uart_read( uint32_t id)
    {
        
        uint32_t i = 0;
        uart* tracer = head;
        while(tracer->id != id){
            tracer = tracer->next;
        }

        while(UARTCharsAvail(tracer->base))
        {     
            char data = UARTCharGetNonBlocking(tracer->base); 
            if((tracer->buff->read_head+1)%BUFF_SIZE != tracer->buff->read_tail)
            {
                tracer->buff->readBuff[tracer->buff->read_head] = data;
                tracer->buff->read_head = (tracer->buff->read_head+1)%BUFF_SIZE;
            }
            
            UARTCharPutNonBlocking(tracer->base, data);
            i++;
            
            tracer->buff->dataAvail = true; 
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
    bool uart_dataAvail( uint32_t id)
    {
        uart* tracer = head;
        while(tracer->id != id)
        {
            tracer = tracer->next;
        }

        if(tracer->buff->dataAvail)return OK;
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
    char* uart_get( uint32_t _id, char* buffer)
    {   
 
        
        uart* tracer = head;
        while(tracer->id != _id)
        {
            tracer = tracer->next;
        }
        uint32_t i = 0;

        while((tracer->buff->read_tail != tracer->buff->read_head))
        {   
            char datum = tracer->buff->readBuff[tracer->buff->read_tail];
            tracer->buff->read_tail = (tracer->buff->read_tail+1)%BUFF_SIZE;
            if(datum == '\n') return buffer;
            buffer[i] = datum;
            i++;
           
  
        }

        tracer->buff->dataAvail = false;
        
        return NULL;
        
        
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
    int uart_init_ALL( void )
    {
        uint8_t portLength = sizeof(uartGPIO_lookup)/sizeof(uartGPIO_lookup[0]);
        uint8_t id;
        
        for(id = 0; id < portLength;)
        {   

            if(uart_create(id))id++;
            else return KO; //uart init error return 
            
        }
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
    int uart_config_ALL(uint32_t clockSource, uint32_t baud, parity uart_par, stopBit uart_stop, dataBit uart_dataLen)
    {
        uint8_t portLength = sizeof(uartGPIO_lookup)/sizeof(uartGPIO_lookup[0]);
        uint8_t id;
        
        for(id = 0; id < portLength;)
        {   

            if(uart_config(id, clockSource, baud, uart_par, uart_stop, uart_dataLen))id++;
            else return KO; //uart init error return 
            
            
        }
        return OK;
    }


#endif 