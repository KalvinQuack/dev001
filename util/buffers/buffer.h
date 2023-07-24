#ifndef __BUFFER_H__
#define __BUFFER_H__

    #define BUFF_SIZE 1024
    typedef enum buffLock
    {
        LOCKED, 
        UNLOCKED

    }buffLock;  

    typedef struct _buffer
    {
        uint8_t     circBuff[BUFF_SIZE];
        uint32_t    write_head;
        uint32_t    write_tail;
        uint32_t    read_head;
        uint32_t    read_tail;
        uint32_t    count;
        buffLock    lock;      
        bool        buffFull; 
    }buffer;

    buffer* buffer_create( void );
    
#endif 