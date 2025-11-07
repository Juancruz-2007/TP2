#ifndef MULTIPLEXADO_H
#define MULTIPLEXADO_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Arduino.h>
#include "tiempo.h"
#include "main.h"
#include "casos.h"

#define DECIMAL 10
#define BINARIO 2

void encender_los_displays(uint8_t); // Enciende los cada display
void Multiplexado(uint16_t, uint8_t ); // manda los datos a los displays
    
    
#ifdef __cplusplus
} // extern "C"
#endif

#endif