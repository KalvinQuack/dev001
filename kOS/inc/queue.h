#ifndef __QUEUE_H__
#define __QUEUE_H__
    #include "task_manager.h"
    
    /*prototypes*/
    PROC *get_proc(PROC **list);
    int append_proc(PROC **list, PROC *node);
    int queue_proc(PROC **queue, PROC *node);
    PROC *deqeue_proc(PROC **queue);

#endif