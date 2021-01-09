#ifndef __SOFT_TIMER_
#define __SOFT_TIMER_

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>

typedef void (*softTimerCallback_t)(void);

struct softTimer{
    uint32_t tick_ms;
    uint32_t counter;
    uint32_t interval;
    softTimerCallback_t callback;
};

void softTimer_init(struct softTimer *);
void softTimer_setInterval(struct softTimer *, uint32_t);
void softTimer_setTickMs(struct softTimer *, uint32_t);
void softTimer_resetCounter(struct softTimer *);
void softTimer_setCallback(struct softTimer *, softTimerCallback_t);
void softTimer_tickHandler(struct softTimer *);

#endif