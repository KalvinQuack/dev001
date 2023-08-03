#ifndef __OBSERVER_H__
#define __OBSERVER_H__
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>

    typedef struct _observer
    {

        void* data; 
        //*contains data to whatever struct that is currently using it
        void(*destroy)(struct _observer);
        //*destroys the observer 
        void(*trigger)(uint32_t, struct _observer*);
        //* callback function 
    }observer;

    /*FUNCTION PROTOTYPES*/
    observer* observer_create(void* data, void(*trigger)(uint32_t, struct _observer*));

#endif