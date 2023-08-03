#include "observer.h"

static void _destroy(observer* subscriber)
{
    if(subscriber != NULL){
        free(subscriber);
    }
    subscriber = NULL;
}

observer* observer_create(void* data, void(*trigger)(uint32_t, struct _observer*))
{
    observer* newSubscriber = (observer*)malloc(sizeof(observer));
    newSubscriber->trigger = trigger;
    newSubscriber->data = data;
    return newSubscriber;
}
