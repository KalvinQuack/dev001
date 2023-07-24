/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.04
*/
#ifndef __KERNEL_C__
#define __KERNEL_C__
    /*standard includes*/
    /*environment includes*/
    #include "KOS.h"

    
    PROC proc[NPROC], *running, *freelist, *readyQueue, *next, init_proc, *sleepQueue;
    
    int procsize = sizeof(PROC);

    /**********************************************
     * Method:  int kernel_init( void );
     * 
     * Description: initializes the kernel and
     *              creates process0 (main)
     * 
     * Notes:
     * 
     * Returns: int 
     * 
    **********************************************/
   void kernel_init( void ){
    PROC *p;
    /*initialize processes*/
    for(uint8_t i=0; i<NPROC; i++){
        p = &proc[i];
        p->pid = i;
        p->proc_state = FREE;
        p->next = &proc[i+1];
    }
    proc[NPROC-1].next = NULL; //set the tail node to point to null

    /*initialize free and ready list*/
    freelist = &proc[0];       
    readyQueue = NULL;

    /*set p0 as initial running process*/
    //p = get_proc(&freelist);
    //p->priority = 0; //lowest priority cannot be used by any other proc
    //running = p;
    p = &init_proc;
    p->proc_state = FREE;
    running = p;
   }
    /**********************************************
     * Method:  int kernel_fork( void );
     * 
     * Description: initializes a process
     *              from free list 
     * 
     * Notes:
     * 
     * Returns: int 
     * 
    **********************************************/
   int kernel_fork( void(*function)(void), uint8_t priority){
    PROC *p = get_proc(&freelist); //grab first node in freelist
    /*list is empty*/
    if(p == NULL){
        return -1;
    }
    /*initialize ready proc*/
    p->proc_state = READY;
    p->priority = priority;
    p->kstack[SSIZE-1] = (1U<<24);
    p->kstack[SSIZE-2] = (int)function;
    for(uint8_t i = 3; i < 9; i++){
        p->kstack[SSIZE-i] = (uint32_t)0xDECAF;
    }
    for(uint32_t i = 9; i<SSIZE; i++){
        p->kstack[SSIZE-i] = 0xDEADBEEF;
    }
    
    /*ksp points to where r0 contents will be located
      |
      v                                            */
    p->ksp = &(p->kstack[SSIZE-16]);
    queue_proc(&readyQueue, p);//insert proc into queue list
    return p->pid;
   }
    /**********************************************
     * Method:  void kernel_exit( void );
     * 
     * Description: terminates process 
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
   void kernel_exit( void ){
    running->proc_state = FREE;
    append_proc(&freelist, running);
    //add tswitch
   }
    /**********************************************
     * Method:  int scheduler( void );
     * 
     * Description: returns running proc back to 
     *              queue list and retrieves next 
     *              in list
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
   int scheduler( void ){
    if(running->proc_state == READY){ 
        queue_proc(&readyQueue, running);
    }
    next = deqeue_proc(&readyQueue);
    if(next != running){
        return 1;
    }else return 0;
   }
    /**********************************************
     * Method:  block(SEMAPHORE *s)
     * 
     * Description: blocks a process
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
   void block(SEMAPHORE *s){
    /*set running status to blocked*/
    running->proc_state = BLOCKED;
    /*queue the processes into the sempahore struct*/
    if(scheduler()){
        queue_proc(&s->queue, running);
        IntPendSet(FAULT_PENDSV);
    }
   }
    /**********************************************
     * Method:  signal(SEMAPHORE *s)
     * 
     * Description: prepares a process as ready 
     * and queues it in the ready queue
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
    void signal(SEMAPHORE *s){
        /*dequeue proc from semaphore queue and 
        and set to ready*/
        PROC *p = deqeue_proc(&s->queue);
        if(p != NULL){
            p->proc_state = READY;
            queue_proc(&readyQueue, p);
      }
    }
    /**********************************************
     * Method:  kernel_delay( uint32_t ticks)
     * 
     * Description: block thread and sets timeout tick
     * 
     * Notes:
     * 
     * Returns: none
     * 
    **********************************************/
    void kernel_delay( uint32_t ticks){
        IntMasterDisable();
        running->proc_state = BLOCKED;
        running->timeout = ticks;
        //scheduler();
        if((int)scheduler()){
            IntPendSet(FAULT_PENDSV);
        }
        IntMasterEnable();
        
    }
    /**********************************************
     * Method:  kernel_tick( void )
     * 
     * Description: counts down timeout and readys task
     * 
     * Notes: ticks * systick interrupt occurence 
     * = total delay
     * 
     * Returns: none
     * 
    **********************************************/
    void kernel_tick( void ){
        for(uint32_t i = 1; i<NPROC; i++){
            PROC *p = &proc[i];
            if(p->timeout != 0){
                --p->timeout;
                if(p->timeout == 0){
                    p->proc_state = READY;
                    queue_proc(&readyQueue, p);
                }
            }
        }
    }




    

    


#endif