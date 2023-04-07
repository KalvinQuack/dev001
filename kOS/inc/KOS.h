#ifndef __KOS_H__
#define __KOS_H__
    #include "queue.h"
    #include "task_manager.h"
    #include "kernel.h"
    #include "system_init.h"

    /* FUNCTION PROTOTYPES*/
    void P              (SEMAPHORE *s);
    void V              (SEMAPHORE *s);
    void OS_init        ( void );
    void OS_start       ( void );
#endif