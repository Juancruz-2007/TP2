#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <util/delay.h>
#include "multiplexado.h"
#include "tiempo.h"
#include "pulsadores.h"
    extern volatile uint16_t valorPulsadores, valorAdc;
    extern volatile uint32_t valorMV;
#ifdef __cplusplus
} // extern "C"
#endif

#endif