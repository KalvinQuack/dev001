#include "inc/HAL_io.h"
#include "board_configuration.h"
#include "gpio.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"




void HAL_initIO(gpioStruct_t* gpioStruct, PinType pinType, uint32_t pull, uint32_t strength, uint32_t alt){
    switch(pinType){
        case INPUT: 
            MAP_GPIOPinTypeGPIOInput(gpioStruct->port, gpioStruct->pin);
        break; 
        case OUTPUT: 
            MAP_GPIOPinTypeGPIOOutput(gpioStruct->port, gpioStruct->pin);
        break;
        case ADC:
            MAP_GPIOPinTypeADC(gpioStruct->port, gpioStruct->pin);
        break;
        case CAN:
            MAP_GPIOPinTypeCAN(gpioStruct->port, gpioStruct->pin);
        break;
        case COMP:
            MAP_GPIOPinTypeComparator(gpioStruct->port, gpioStruct->pin); 
        break;
        case EPI:
            MAP_GPIOPinTypeEPI(gpioStruct->port, gpioStruct->pin);
        break;
        case ETH_LED:
            MAP_GPIOPinTypeEthernetLED(gpioStruct->port, gpioStruct->pin);
        break;
        case ETH_MII:
            MAP_GPIOPinTypeEthernetMII(gpioStruct->port, gpioStruct->pin);
        break;
        case OUTPUT_OD:
            MAP_GPIOPinTypeGPIOOutputOD(gpioStruct->port, gpioStruct->pin);
        break;
        case I2C:
            MAP_GPIOPinTypeI2C(gpioStruct->port, gpioStruct->pin);
        break;
        case I2CSCL:
            MAP_GPIOPinTypeI2CSCL(gpioStruct->port, gpioStruct->pin);
        break;
        case LCD:
            MAP_GPIOPinTypeLCD(gpioStruct->port, gpioStruct->pin); 
        break;
        case PWM:
            MAP_GPIOPinTypePWM(gpioStruct->port, gpioStruct->pin);
        break;
        case QEI:
            MAP_GPIOPinTypeQEI(gpioStruct->port, gpioStruct->pin);
        break;
        case SSI:
            MAP_GPIOPinTypeSSI(gpioStruct->port, gpioStruct->pin);
        break;
        case TIMER:
            MAP_GPIOPinTypeTimer(gpioStruct->port, gpioStruct->pin);
        break;
        case UART: 
            MAP_GPIOPinTypeUART(gpioStruct->port, gpioStruct->pin);
        break;
        case USB_ANALOG:
            MAP_GPIOPinTypeUSBAnalog(gpioStruct->port, gpioStruct->pin);
        break;
        case USB_DIGITAL:
            MAP_GPIOPinTypeUSBDigital(gpioStruct->port, gpioStruct->pin);
        break;
        case WAKE_HIGH:
            MAP_GPIOPinTypeWakeHigh(gpioStruct->port, gpioStruct->pin);
        break;
        case WAKE_LOW:
            MAP_GPIOPinTypeWakeLow(gpioStruct->port, gpioStruct->pin);
        break;
    }if(pinType != INPUT ||pinType != OUTPUT) MAP_GPIOPinConfigure(alt);
    MAP_GPIOPadConfigSet(gpioStruct->port, gpioStruct->pin, strength, pull);
}

void HAL_writeIO(gpioStruct_t* gpioStruct, uint32_t val){
    MAP_GPIOPinWrite(gpioStruct->port, gpioStruct->pin, (gpioStruct->pin)*val);
}

uint32_t HAL_readIO(gpioStruct_t* gpioStruct){
    return MAP_GPIOPinRead(gpioStruct->port, gpioStruct->pin);
}
  