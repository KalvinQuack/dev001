#ifndef __SERIAL_H__
#define __SERIAL_H__
    #include <stdint.h>
    #include <stdarg.h>
    /* FUNCTION PROTOTYPES*/
    uint8_t serial_write( const char *format, ...);
    uint8_t serial_printf(char *string, ...);
    char* serial_read( char* string );
    
#endif