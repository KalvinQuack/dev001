#ifndef __PIN_TABLE_H__
#define __PIN_TABLE_H__

#include "util/common.h"

#ifdef PART_TM4C129XNCZAD
    #define NUM_OF_PORTS 18
    #define NUM_OF_PINS 8
#endif/* __PIN_TABLE_H__ */

#ifdef PART_TM4C123GH6PM
    #define NUM_OF_PORTS 6
    #define NUM_OF_PINS 8
#endif/* __PINS_H__ */

extern uint32_t ports[NUM_OF_PORTS];
extern uint32_t pins[NUM_OF_PINS];

#define TIVA_PORT(id) (id >> 0x3)
#define TIVA_PIN(id) (1 << (id & 0x7))


#endif/* __PINS_H__ */
