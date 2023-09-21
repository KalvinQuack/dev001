/*
This is a test file under LOR Mobile Controls
THIS IS NOT DISTRIBUTED FOR COMMERCIAL USE
*/

#ifndef __BSP_H__
    #define __BSP_H__

    #ifdef _DEV001_DEVICE_

   //!HARDWARE ENABLES MUST BE CONFIGURED FIRST BEFORE ASSIGNING BSP PINS
    #define BSP_ENABLE_CLOCKS 
    #define BSP_ENABLE_GPIO
    #define BSP_ENABLE_UART 
    #define BSP_ENABLE_PWM
    //#define BSP_ENABLE_INTERRUPTS 
   //!HARDWARE ENABLES MUST BE CONFIGURED FIRST BEFORE ASSIGNING BSP PINS

   //! FREQUENCY MUST BE LESS THAN OR 120 MHZ
    #define BSP_SYSCLK_FREQ 120000000
   //! FREQUENCY MUST BE LESS THAN OR 120 MHZ

    /**
     ** Configure the BSP pins for the correct hardware
     ** NAMING CONVENTION:

    */
    #ifdef BSP_ENABLE_GPIO
        #define BSP_PORT_MCL_BUTTON_IN1 
        #define BSP_PORT_MCL_BUTTON_IN2 1
        #define BSP_PORT_MOP_LED_OUT1 2
        #define BSP_PORT_MOP_LED_OUT2 3
    #endif 

    #ifdef BSP_ENABLE_UART
        #define BSP_PERP_UART0 0
        #define BSP_UART0_DEFBAUD 9600

        #define BSP_PERP_UART1 1
        #define BSP_UART1_DEFBAUD 9600
    #endif

    #ifdef BSP_ENABLE_PWM
        #define BSP_GEN0_DEFFREQ 2400
        #define BSP_PWM0_DEFDUTY 1200
        #define BSP_PWM1_DEFDUTY 600
        


    #endif

    


    /**
     ** Configure the BSP pins for the correct hardware
    */


#endif
#endif 



