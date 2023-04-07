#ifndef __TASK_MANAGER_H__
#define __TASK_MANAGER_H__
    #include <stdint.h>

    #define STACKSIZE 1024
    /*thread states*/
    typedef enum status{
        FREE,       //0
        READY,      //1
        BLOCKED,    //2
        RUNNING     //3

    }proc_status;
    
    //thread body function
    typedef void(*proc_function)( void ); 

    /* thread struct */
    typedef struct process{

        struct process *next;   //pointer to next process 
        int pid;                //specific process id
        int *ksp;               //holds stack pointer location when context switching
        proc_status proc_state; //state of process
        uint8_t priority;       //process priority
        int kstack[STACKSIZE];  //size of processs stack 
    }PROC;

    /* semaphore struct */
    typedef struct semaphore{

        int value;
        PROC *queue;
        
    }SEMAPHORE;

    /*prototypes*/
    PROC *get_proc(PROC **list);
    int append_proc(PROC **list, PROC *node);
    int queue_proc(PROC **queue, PROC *node);
    PROC *deqeue_proc(PROC **queue);

#endif