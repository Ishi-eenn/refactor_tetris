#ifndef TIMER_CONFIG_H
#define TIMER_CONFIG_H

#include <time.h>
#include <sys/time.h>

#define Initial_Timer_Value 400000
#define Decrease_Rate_Value 10000

typedef struct {
    suseconds_t initialTimer;
    int decreaseRate;
} TimerInfo;

#endif // TIMER_CONFIG_H
