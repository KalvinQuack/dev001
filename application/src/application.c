/*
    This is the development main for LOR Mobile Controls Project Phoenix
    THIS IS NOT FOR PRODUCTION USE

    Version: V.01
*/
#include <stdint.h>
#include <stdbool.h>
#include "application.h"

__destroy(app* me){
    if(me != NULL){
        free(me);
        me = NULL;
    }
}

app* app_create(char* appName, void(*config_file)(void), void(*running_file)(void)){
    app* me = (app*)malloc(sizeof(*me));

    me->name = appName;
    me->destroy = __destroy;
    me->config = config_file;
    me->running = running_file;

    return me;
}