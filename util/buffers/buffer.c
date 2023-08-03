#ifndef __BUFFER_C__
#define __BUFFER_C__
    #include "common.h"
    #include "buffer.h"
    



   buffer* buffer_create( void )
   {
    buffer* me = malloc(sizeof(buffer));
    me->buffFull = false;
    me->count =0;
    me->lock = UNLOCKED;
    me->read_head = 0;
    me->read_tail = 0;
    me->write_head = 0; 
    me->write_tail = 0;
    me->dataAvail = false; 
    for(uint32_t i = 0; i < BUFF_SIZE; i++)
    {
        me->circBuff[i] = '\0';
        me->readBuff[i] = '\0';
    }
    return me;
   } 

#endif