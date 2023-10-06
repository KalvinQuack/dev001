#ifndef __HAL_SYSCTL_H__
#define __HAL_SYSCTL_H__
#include "../util/common.h"



uint32_t HAL_initSysClock(uint32_t desiredFreq, uint32_t externalFreq, uint32_t oscSource, uint32_t clkSource, uint32_t PLLFreq);
void HAL_initPerph(uint32_t peripheral);


#endif/* __HAL_SYSCTL_H__ */
