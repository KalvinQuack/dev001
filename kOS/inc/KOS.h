#ifndef __KOS_H__
#define __KOS_H__
    #include "queue.h"
    #include "task_manager.h"
    #include "kernel.h"
    #include "system.h"

    /* FUNCTION PROTOTYPES*/
    void P              (SEMAPHORE *s);
    void V              (SEMAPHORE *s);
    void task_sleep     (SEMAPHORE *s);
    void task_wakeup    (SEMAPHORE *s);
    void OS_init        ( void );
    void OS_start       ( void );
#endif