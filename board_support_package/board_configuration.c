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

uint32_t clkFreq = 0;
    
    //bsp pin setup
    #ifdef BOARD_IS_DEVELOPY

    gpioStruct_t PA2 = {HAL_BUTTON02_PORT, HAL_BUTTON02_PIN,INPUT, INT_PULLDOWN, GPIO_STRENGTH_2MA, NOT_USED};
    gpioStruct_t PB1 = {HAL_LED01_PORT, HAL_LED01_PIN, OUTPUT,INT_PULLUP, GPIO_STRENGTH_2MA, NOT_USED};
    gpioStruct_t PB2 = {HAL_LED02_PORT, HAL_LED02_PIN, OUTPUT,INT_PULLUP, GPIO_STRENGTH_2MA, NOT_USED};
    gpioStruct_t PP0 = {HAL_UART01_PORT, HAL_UART01RX_PIN,UART, NO_PULL, GPIO_STRENGTH_2MA, GPIO_PP0_U6RX};
    gpioStruct_t PP1 = {HAL_UART01_PORT, HAL_UART01TX_PIN,UART, NO_PULL, GPIO_STRENGTH_2MA, GPIO_PP1_U6TX};
    gpioStruct_t PF0 = {HAL_PWM0BLOCK_PORT, HAL_PWM0A_PIN,PWM, NO_PULL, GPIO_STRENGTH_2MA, GPIO_PF0_M0PWM0};
    gpioStruct_t PF1 = {HAL_PWM0BLOCK_PORT, HAL_PWM0B_PIN,PWM, NO_PULL, GPIO_STRENGTH_2MA, GPIO_PF1_M0PWM1};
    gpioStruct_t PA0 = {HAL_BUTTON01_PORT,  HAL_BUTTON01_PIN,INPUT, INT_PULLUP, GPIO_STRENGTH_2MA, NOT_USED};

    
    pwmStruct_t PWM0 = {PWM_GEN_0, PWM0_BASE, PWM_OUT_0,};
    pwmStruct_t PWM1 = {PWM_GEN_0, PWM0_BASE, PWM_OUT_1};

    gpioStruct_t* pin_map[] = {
        &PA2, &PB1, &PB2, &PP0, &PP1, &PF0, &PF1
     
    };


    #endif

    #ifdef BOARD_IS_DEVELOPY_M2
    #endif 


    

    gpioStruct_t* get_pin( uint32_t index){
        return pin_map[index];
    }
  
    static void BSP_init_clock( void ){
        clkFreq = HAL_initSysClock(CLOCK_FREQ, EXT_CLKFREQ, OSC_SRC, CLOCK_SRC, PLL_FREQ);
    }
    
    static void BSP_init_peripheralClk( void ){
        #ifdef BOARD_IS_DEVELOPY
            HAL_initPerph(PERPH_A);
            HAL_initPerph(PERPH_B);
            HAL_initPerph(PERPH_K);
            HAL_initPerph(PERPH_P);
            HAL_initPerph(PERPH_F);
            HAL_initPerph(PERPH_UART4);
            HAL_initPerph(PERPH_UART6);
            HAL_initPerph(PERPH_PWM0);
        #endif
             
    }
    static void BSP_init_gpio( void ){
        #ifdef BOARD_IS_DEVELOPY
        HAL_initIO(&PA0);
        HAL_initIO(&PA2);
        HAL_initIO(&PB1);
        HAL_initIO(&PB2);
        HAL_initIO(&PP0);
        HAL_initIO(&PP1);
        HAL_initIO(&PF0);
        HAL_initIO(&PF1);
        #endif 
    };

    static void BSP_init_pwm( void ){
        #ifdef BOARD_IS_DEVELOPY
        HAL_initPWM(&PWM0, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        HAL_initPWM(&PWM1, PWM_GEN_MODE_DOWN | PWM_GEN_MODE_NO_SYNC);
        #endif
        
    }

    uint8_t BSP_init_hardware( void ){
        BSP_init_clock();
        BSP_init_peripheralClk();
        BSP_init_gpio();
        BSP_init_pwm();
      return 0;
    }



 



#endif/* __BOARD_CONFIGURATION_C__ */
