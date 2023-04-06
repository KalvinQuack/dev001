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
    #include "pinmap.h"
    
    #define MAX_PINS 2
    uart_comm uart_obj[UART_TOTAL];
    static char done[] = "#### UART INIT ####";


    void config_UART(HAL_UARTS device, bool interrupt, uint32_t baudRate, uint32_t clk){
        
        if(device > UART_TOTAL){
            while(1){}
        }

         UART_DEV* uart_ptr = accessUART_device((uint32_t)device);
         PINOUT* uart_pin[MAX_PINS];

        for(uint8_t i = 0; i < MAX_PINS; i++){
            uart_pin[i] = accessDevice_pinout(UART, (uint32_t)device+i);
        }

        UARTDisable(uart_ptr->uart_base);

        GPIOPinConfigure(uart_ptr->uart_rx);
        GPIOPinConfigure(uart_ptr->uart_tx);
        GPIOPinTypeUART(uart_pin[0]->device_port, 
                        uart_pin[0]->device_pin | uart_pin[1]->device_pin);

        UARTConfigSetExpClk(    
            uart_ptr->uart_base, 
            clk, 
            baudRate, 
            UART_CONFIG_WLEN_8|
            UART_CONFIG_STOP_ONE|
            UART_CONFIG_PAR_NONE
            ); 
        //UARTFIFOEnable(uart_ptr->uart_base);
        UARTEnable(uart_ptr->uart_base);

        for(int i = 0; i < sizeof(BUFF_SIZE); i++){
            uart_obj[(uint32_t)device].circBuff[i] = '\0';
        }
        uart_obj[(uint32_t)device].write_head   = 0;
        uart_obj[(uint32_t)device].read_head    = 0;
        uart_obj[(uint32_t)device].write_tail   = 0;
        uart_obj[(uint32_t)device].read_tail    = 0;
        uart_obj[(uint32_t)device].buffFull     = false;


    }

    uint8_t send_UART (HAL_UARTS device){
        UART_DEV* uart_ptr = accessUART_device((uint32_t)device);
        uart_comm* buffer = &uart_obj[(uint32_t)device];
        
        if(buffer->write_tail == buffer->write_head && !buffer->buffFull){
            //buffer is empty
            return 0;
        }
        if((buffer->write_tail+1)%BUFF_SIZE != buffer->write_head){
            UARTCharPutNonBlocking(uart_ptr->uart_base, buffer->circBuff[buffer->write_tail]);
            buffer->write_tail = (buffer->write_tail+1) % BUFF_SIZE;
        }
        buffer->buffFull = false;
        return 1;
    }
#endif 