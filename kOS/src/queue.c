/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#ifndef __QUEUE_C__
#define __QUEUE_C__

 #include <stdlib.h>
 #include "task_manager.h"
 #include "queue.h"
    /**********************************************
     * Method:  *get_proc(PROC **list)
     * 
     * Description: pulls the head node from linked list
     * 
     * Notes:
     * 
     * Returns: PROC *p 
     * 
    **********************************************/
    PROC *get_proc(PROC **list){
        PROC *head = *list;
        if(head == NULL){
            return NULL;
        }
        *list = (*list)->next;
        return head;
    }
    /**********************************************
     * Method:  append_proc(PROC **list, PROC *node)
     * 
     * Description: inserts node at the end of 
     *              a linked list
     * 
     * Notes:
     * 
     * Returns: 0
     * 
    **********************************************/
    int append_proc(PROC **list, PROC *node){

        PROC **tracer = list;

        if(*tracer == NULL){
            *tracer = node;
            node->next = NULL;
        }

        while((*tracer)->next != NULL){
            tracer = &(*tracer)->next;
        }
        node->next = *tracer;
        *tracer = node; 
        
        return 0;
    }
    /**********************************************
     * Method:  queue_proc(PROC **queue, PROC *node)
     * 
     * Description: inserts node into the queue list 
     *              based on node priority 
     * 
     * Notes:
     * 
     * Returns: 0
     * 
    **********************************************/
    int queue_proc(PROC **queue, PROC *node){
        PROC **tracer = queue;
        if((*tracer) == NULL){
            node->next = (*tracer);
            *tracer = node;
            return 0;
        }
        /*condition 1: node priority > tracer priority*/
        if((*tracer)->priority < node->priority){
            node->next = (*tracer);
            *tracer = node;
            return 0;
        }
        /*condition 2: node priority < tracer priority*/
        if((*tracer)->priority > node->priority){
            while((*tracer)->next->priority > node->priority && (*tracer)->next != NULL){
                tracer = &(*tracer)->next;
            }
            /*sort through the list again if the node priority 
            equals the new node priority to find end */
            if((*tracer)->next->priority == node->priority){
                while((*tracer)->next->priority == node->priority){
                    tracer = &(*tracer)->next;
                }
            }
            /*set new nodes->next to previous nodes->next*/
            node->next = (*tracer)->next;
            (*tracer)->next = node;
            return 0;                   
        }
        /*condition 3 node priority = tracer priority*/
        if((*tracer)->priority == node->priority){
            while((*tracer)->next->priority == node->priority && (*tracer)->next != NULL){
                tracer = &(*tracer)->next;
            }
            node->next = (*tracer)->next;
            (*tracer)->next = node;
            return 0;
        }
        return 1;
    }
    /**********************************************
     * Method:  dequeue_proc(PROC **queue)
     * 
     * Description: returns first ready node 
     * 
     * Notes:
     * 
     * Returns: *PROC node
     * 
    **********************************************/
   PROC* deqeue_proc(PROC** queue){
    PROC *head = *queue;
    if(head == NULL){
        return NULL;
    }
    *queue = (*queue)->next;
    return head;
   }
#endif