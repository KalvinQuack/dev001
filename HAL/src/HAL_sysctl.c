#include "inc/HAL_sysctl.h"
#include "sysctl.h"


uint32_t HAL_initSysClock(uint32_t desiredFreq, uint32_t externalFreq, uint32_t oscSource, uint32_t clkSource, uint32_t PLLFreq){
    return MAP_SysCtlClockFreqSet(oscSource|clkSource|externalFreq|PLLFreq, desiredFreq);
}
void HAL_initPerph(uint32_t peripheral){
    MAP_SysCtlPeripheralEnable(peripheral);
}

