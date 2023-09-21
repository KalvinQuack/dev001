#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__
#include "util/common.h"

void BSP_PWM_ON( uint32_t id);
void BSP_PWM_FREQ(uint32_t id, uint32_t freq);
void BSP_PWM_FreqTog(uint32_t id, uint32_t freq, uint32_t enable);

/**
 * @struct pwmStruct_t 
 * @brief This is a struct that represents a pwm module
 * 
 * This struct is used for interfacing with pwm components
 *
 */
typedef struct{
    uint32_t gen;
    uint32_t base;
    uint32_t pwmOne;
    uint32_t pwmTwo;
}pwmStruct_t;
/**
 * @brief This function inits PWM peripheral
 * 
 * @param pwm 
 * @param config config is the OR of all PWM configurations
 */
void HAL_initPWM(pwmStruct_t* pwm, uint32_t config);
/**
 * @brief This function deinits PWM peripheral
 * 
 * @param pwm 
 */
void HAL_deinitPWM(pwmStruct_t* pwm);
/**
 * @brief This sets the period (1/f) of the pwm generator
 * 
 * @param pwm 
 * @param period 
 */
void HAL_PWMsetPeriod(pwmStruct_t* pwm, uint32_t period);
/**
 * @brief This sets the duty cylce of a pwm output
 * 
 * @param pwm 
 * @param pwmOutput can be OR'd by mutliple outputs on the same module
 * @param dutyCycle 
 */
void HAL_PWMsetDuty(pwmStruct_t* pwm, uint32_t pwmOutput, uint32_t dutyCycle);
/**
 * @brief This function turns on the PWM output(s)
 * 
 * @param pwm 
 * @param pwmOutput can be OR'd by mutliple outputs on the same module
 */
void HAL_PWMenable(pwmStruct_t* pwm, uint32_t pwmOutput);

#endif/* __BSP_PWM_H__ */
