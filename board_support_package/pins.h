#ifndef __PINS_H__
#define __PINS_H__
#include "inc/hw_memmap.h"
#include "pin_map.h"
#include "gpio.h"

#define PORT(val) ((val)&0xFFFFF000)
#define PIN(val)    ((val&0x00000FFF))

#define CLOCK_FREQ          120000000
#define CLOCK_SRC           SYSCTL_USE_PLL              
#define OSC_SRC             SYSCTL_OSC_MAIN
#define PLL_FREQ            SYSCTL_CFG_VCO_480            
#define EXT_CLKFREQ         SYSCTL_XTAL_25MHZ         

#define PERPH_A             SYSCTL_PERIPH_GPIOA
#define PERPH_B             SYSCTL_PERIPH_GPIOB
#define PERPH_P             SYSCTL_PERIPH_GPIOP
#define PERPH_K             SYSCTL_PERIPH_GPIOK
#define PERPH_F             SYSCTL_PERIPH_GPIOF
#define PERPH_UART6         SYSCTL_PERIPH_UART6
#define PERPH_UART4         SYSCTL_PERIPH_UART4
#define PERPH_PWM0          SYSCTL_PERIPH_PWM0

#define INTERNAL_PULLUP     GPIO_PIN_TYPE_STD_WPU
#define INTERNAL_PULLDOWN   GPIO_PIN_TYPE_STD_WPD

#define HAL_BUTTON01_PIN    GPIO_PIN_0
#define HAL_BUTTON01_PORT   GPIO_PORTA_BASE
#define HAL_BUTTON02_PIN    GPIO_PIN_1
#define HAL_BUTTON02_PORT   GPIO_PORTA_BASE

#define HAL_LED01_PIN       GPIO_PIN_0
#define HAL_LED01_PORT      GPIO_PORTB_BASE
#define HAL_LED02_PIN       GPIO_PIN_1
#define HAL_LED02_PORT      GPIO_PORTB_BASE

#define HAL_UART01_PORT     GPIO_PORTP_BASE
#define HAL_UART01TX_PIN    GPIO_PIN_1
#define HAL_UART01RX_PIN    GPIO_PIN_0
#define HAL_UART02_PORT     GPIO_PORTK_BASE
#define HAL_UART02TX_PIN    GPIO_PIN_1
#define HAL_UART02RX_PIN    GPIO_PIN_0

#define HAL_PWM0BLOCK_PORT  GPIO_PORTF_BASE
#define HAL_PWM0A_PIN       GPIO_PIN_0
#define HAL_PWM0B_PIN       GPIO_PIN_1




#endif/* __PINS_H__ */
