#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__
    #include <stdbool.h>
    #include <stdint.h>
    #include <stdlib.h>
    #include "observer.h"
    #define MAX_SUBS 100
    typedef struct __publisher
    {
        void* data;
        //* data to whatever object is using the publisher
        void(*destroy)(struct __publisher*);
        //* destroys publisher
        observer* subList[MAX_SUBS];
        //* list of the theoretical max amount of subscribers 
        uint32_t arraySize;
        //* the literal max amount of subscribers if when defined
        int(*subscribe)(struct __publisher*, observer*);
        //* function to attack subscribers to the publisher
        int(*unsubscribe)(struct __publisher*, observer*);
        //*function that removes the subscriber from publisher
        void(*notifySubs)(struct __publisher*, uint32_t data);
        //* callback function
        int subscriberCount;
        //*how many active subscribers it has

    }publisher;

/*FUNCTION PROTOTYPES*/
    publisher* publisher_create(void* data, uint32_t subSize);

#endif