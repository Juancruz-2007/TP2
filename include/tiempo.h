#ifndef TIEMPO_H
#define TIEMPO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Arduino.h>
    extern volatile uint64_t time_bot, tiempo, time_total;
    void config_TIMER0(void);

uint64_t get_time();

#ifdef __cplusplus
} // extern "C"
#endif

#endif