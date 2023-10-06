    #include "HAL_io.h"

/*     
void HAL_initIO(gpioStruct_t* gpioStruct){
    switch(gpioStruct->type){
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
            //MAP_GPIOPinTypeLCD(gpioStruct->port, gpioStruct->pin); 
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
    }

    if(gpioStruct->type != INPUT ||gpioStruct->type != OUTPUT){MAP_GPIOPinConfigure(gpioStruct->alt);}
    else{
        switch(gpioStruct->pull){
            case EXT_PULLDOWN:
                MAP_GPIOPadConfigSet(gpioStruct->port, gpioStruct->pin, gpioStruct->strength, GPIO_PIN_TYPE_STD);  
            break;
            case EXT_PULLUP:
                MAP_GPIOPadConfigSet(gpioStruct->port, gpioStruct->pin, gpioStruct->strength, GPIO_PIN_TYPE_STD);  
            break;
            case INT_PULLDOWN:
                MAP_GPIOPadConfigSet(gpioStruct->port, gpioStruct->pin, gpioStruct->strength, GPIO_PIN_TYPE_STD_WPD);  
            break;
            case INT_PULLUP:
                MAP_GPIOPadConfigSet(gpioStruct->port, gpioStruct->pin, gpioStruct->strength, GPIO_PIN_TYPE_STD_WPU);
            break;
            case NO_PULL:
            break;
        }
    }


}

void HAL_writeIO(gpioStruct_t* gpioStruct, uint8_t val){
    MAP_GPIOPinWrite(gpioStruct->port, gpioStruct->pin, val*(gpioStruct->pin));
}

uint32_t HAL_readIO(gpioStruct_t* gpioStruct){
    return MAP_GPIOPinRead(gpioStruct->port, gpioStruct->pin);
}
 */
uint8_t test(void){
    return 1;
}
