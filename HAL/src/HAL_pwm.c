#include "inc/HAL_pwm.h"
#include "board_configuration.h"
#include "pwm.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"


void HAL_initPWM(pwmStruct_t* pwm, uint32_t  config){
    MAP_PWMGenConfigure(pwm->base, pwm->gen, config);
}
