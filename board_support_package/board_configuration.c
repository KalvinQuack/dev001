#ifndef __BOARD_CONFIGURATION_C__
#define __BOARD_CONFIGURATION_C__

#include "BSPInterface.h"
#include "board_configuration.h"
#include "uart.h"
#include "gpio.h"
#include "pwm.h"
#include "sysctl.h"
#include "pins.h"

#include "HAL/inc/HAL_sysctl.h"
#include "HAL/inc/HAL_pwm.h"
/*!order is important*/
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
    
    //bsp pin setup
    gpioStruct_t PA1;
    gpioStruct_t PA2;
    gpioStruct_t PA3;
    gpioStruct_t PA4;
    gpioStruct_t PB1;
    gpioStruct_t PB2;
    gpioStruct_t PB3;


    


  
    static void BSP_init_clock( void ){
        uint32_t clkFreq = HAL_initSysClock(CLOCK_FREQ, EXT_CLKFREQ, OSC_SRC, CLOCK_SRC, PLL_FREQ);
    }
    
    static void BSP_init_peripheralClk( void ){
        //#ifdef BOARD_IS_DEVELOPY
            HAL_initPerph(PERPH_A);
            HAL_initPerph(PERPH_B);
            HAL_initPerph(PERPH_K);
            HAL_initPerph(PERPH_P);
            HAL_initPerph(PERPH_UART4);
            HAL_initPerph(PERPH_UART6);
            HAL_initPerph(PERPH_PWM0);
        //#endif
             
    }
    static void BSP_init_gpio( void ){

    };


/*     static void BSP_init_gpio( void ){

        for(uint8_t i = 0; i < (sizeof(gpio) / sizeof(gpio[0])); i++){

            GpioChannel* temp = &gpio[i];
            uint32_t temp_port = (temp->gpioPin & PORT);
            uint8_t  temp_pin = (temp->gpioPin & PIN);

            if(temp->gpioAltFunction != DISABLED){
                MAP_GPIOPinConfigure(temp->gpioAltFunction);
                switch(temp->gpioPinType){
                    case INPUT: 
                    //should never be here
                    break; 
                    case OUTPUT: 
                    //should never be here 
                    break;
                    case ADC:
                        MAP_GPIOPinTypeADC(temp_port, temp_pin);
                    break;
                    case CAN:
                        MAP_GPIOPinTypeCAN(temp_port, temp_pin);
                    break;
                    case COMP:
                        MAP_GPIOPinTypeComparator(temp_port, temp_pin); 
                    break;
                    case EPI:
                        MAP_GPIOPinTypeEPI(temp_port, temp_pin);
                    break;
                    case ETH_LED:
                        MAP_GPIOPinTypeEthernetLED(temp_port, temp_pin);
                    break;
                    case ETH_MII:
                        MAP_GPIOPinTypeEthernetMII(temp_port, temp_pin);
                    break;
                    case OUTPUT_OD:
                        MAP_GPIOPinTypeGPIOOutputOD(temp_port, temp_pin);
                    break;
                    case I2C:
                        MAP_GPIOPinTypeI2C(temp_port, temp_pin);
                    break;
                    case I2CSCL:
                        MAP_GPIOPinTypeI2CSCL(temp_port, temp_pin);
                    break;
                    case LCD:
                        MAP_GPIOPinTypeLCD(temp_port, temp_pin); 
                    break;
                    case PWM:
                        MAP_GPIOPinTypePWM(temp_port, temp_pin);
                    break;
                    case QEI:
                        MAP_GPIOPinTypeQEI(temp_port, temp_pin);
                    break;
                    case SSI:
                        MAP_GPIOPinTypeSSI(temp_port, temp_pin);
                    break;
                    case TIMER:
                        MAP_GPIOPinTypeTimer(temp_port, temp_pin);
                    break;
                    case UART: 
                        MAP_GPIOPinTypeUART(temp_port, temp_pin);
                    break;
                    case USB_ANALOG:
                        MAP_GPIOPinTypeUSBAnalog(temp_port, temp_pin);
                    break;
                    case USB_DIGITAL:
                        MAP_GPIOPinTypeUSBDigital(temp_port, temp_pin);
                    break;
                    case WAKE_HIGH:
                        MAP_GPIOPinTypeWakeHigh(temp_port, temp_pin);
                    break;
                    case WAKE_LOW:
                        MAP_GPIOPinTypeWakeLow(temp_port, temp_pin);
                    break;
                }
            }else{
                if(temp->gpioPinType == INPUT){
                    MAP_GPIOPinTypeGPIOInput(temp_port, temp_pin);
                }else{
                    MAP_GPIOPinTypeGPIOOutput(temp_port, temp_pin);
                }
            }

        }
    }
     */
    uint8_t BSP_init_hardware( void ){
      return 0;
    }



 



#endif/* __BOARD_CONFIGURATION_C__ */
