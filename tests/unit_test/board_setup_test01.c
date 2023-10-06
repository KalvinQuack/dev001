#include "board_setup_test01.h"
#include "board_configuration.h"
uint8_t test01( void ){
    if(BSP_init_hardware()){
        return OK;
    }
}