#include "subject.h"

static void __destroy(publisher* me){
    if(me != NULL){
        free(me);
    }
    me = NULL;
}

int __subscribe(publisher* publisher, observer* observer)
{
    if(publisher->subscriberCount == publisher->arraySize){
        //array full
        return 0;
    }
    int i = 0;
    while(publisher->subList[i] != NULL){
        i++;
    }
    publisher->subList[i] = observer;
    publisher->subscriberCount++;
    return 1;
}

int __unsubscribe(publisher* publisher, struct _observer* observer)
{
    for(int i = 0; i < publisher->arraySize; i++){
         if(publisher->subList[i] == observer){
            publisher->subList[i] = NULL;
        }
        publisher->subscriberCount--;
    } 
    return 1;
}

void __notify(publisher* me, uint32_t data){
    for(int i = 0; i<me->arraySize; i++){
        if(me->subList[i] != NULL){
            me->subList[i]->trigger(data,me->subList[i]);
        }
    }
}

 

publisher* publisher_create(void* data, uint32_t subSize)
{   
    publisher* new = (publisher*)malloc(sizeof(publisher));
    new->data = data;
    if(subSize <= MAX_SUBS)new->arraySize = subSize;
    else return NULL;
    new->destroy = (void(*)(publisher*))__destroy;
    new->notifySubs = (void(*)(publisher*, uint32_t))__notify;
    new->subscribe = (int(*)(publisher*, struct _observer*))__subscribe;
    new->unsubscribe = (int(*)(publisher*, struct _observer*))__unsubscribe;

    for(int i = 0; i<MAX_SUBS; i++){
        new->subList[i] = NULL;
    }
    new->subscriberCount = 0;
    return new;
}