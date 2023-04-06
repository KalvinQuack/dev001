/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#include <stdint.h>
#include <stdbool.h>
#include "testHAL.h"
#include "buttons.h"
#include "serial.h"
#include "driverlib/uart.h"

uint32_t button1;
uint32_t button2;
uint32_t button3; 
uint32_t button4; 
uint32_t button5; 
uint32_t state;

void app_config(){
     button1 = newDigitalButton(IN_01_DI);
     button2 = newDigitalButton(IN_02_DI);
     button3 = newDigitalButton(IN_03_DI);
     button4 = newDigitalButton(IN_04_DI);
     button5 = newDigitalButton(IN_05_DI); 
}

void app(){
    if(readButton(button1)==1){
        state = 1;
    }else state = 0;
}