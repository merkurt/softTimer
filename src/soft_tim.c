#include "soft_tim.h"

void softTimer_init(struct softTimer *tim){
    tim->tick_ms = 0;
    tim->counter = 0;
    tim->interval = 0;
    tim->callback = NULL;
}

void softTimer_setInterval(struct softTimer *tim, uint32_t interval){
    tim->interval = interval;
}

void softTimer_setTickMs(struct softTimer *tim, uint32_t tick_ms){
    tim->tick_ms = tick_ms;
}

void softTimer_resetCounter(struct softTimer *tim){
    tim->counter = 0;
}

void softTimer_setCallback(struct softTimer *tim, softTimerCallback_t cb){
    tim->callback = cb;
}

void softTimer_tickHandler(struct softTimer *tim){
    tim->counter += tim->tick_ms;
    if(tim->counter == tim->interval){
        if(tim->callback != NULL){
            tim->callback();
        }
        softTimer_resetCounter(tim);
    }
}
