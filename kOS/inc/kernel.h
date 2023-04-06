#ifndef __KERNEL_H__
#define __KERNEL_H__
    #include <stdint.h>
    #include "KOS.h"
    
    /*definitions*/
    #define NPROC 9
    #define SSIZE 1024

    /*prototypes*/
    void kernel_init( void );
    int kernel_fork( int function, uint8_t priority);
    void kernel_exit( void );
    int scheduler ( void );
    int testBody( void );
    void tswitch( void );

#endif