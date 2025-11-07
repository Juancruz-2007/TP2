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
    extern volatile uint16_t valor_de_puls, valor_de_ADC;
    extern volatile uint32_t valor_en_milivolt;
#ifdef __cplusplus
} // extern "C"
#endif

#endif