#ifndef __KERNEL_H__
#define __KERNEL_H__
    #include <stdint.h>
    #include "KOS.h"
    
    /*definitions*/
    #define NPROC 9
    #define SSIZE 1024

    /*prototypes*/
    void kernel_init    ( void );
    int  kernel_fork    ( void(*function)(void), uint8_t priority);
    void kernel_exit    ( void );
    int  scheduler      ( void );
    void block          ( SEMAPHORE *s );
    void signal         ( SEMAPHORE *s );
    void kernel_tick    ( void );
    void kernel_delay   ( uint32_t ticks );
    
    void kernel_sleep   ( void );
    void kernel_wake    ( void );

#endif/* __KERNEL_H__ */
