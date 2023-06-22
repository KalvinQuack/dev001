#ifndef __APPLICATION_H__
#define __APPLICATION_H__
    #ifndef APP_DIGITAL_INPUTS
    #define APP_DIGITAL_INPUTS


        typedef struct __app{
            char* name;
            void (*running)( void );
            void (*config)( void );
            void (*destroy)(struct __observer*);
        }app;

        /* FUNCTION PROTOTYPES*/
        app* app_create(char*, void(*)(void), void(*)(void));

    #endif
#endif 