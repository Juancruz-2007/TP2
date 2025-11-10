#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C"
{
#endif
/* Si compilo desde un archivo Cpp, me compila lo siguiente en C */
    // Este bloque es importante cuando trabajamos con C++.
    // Si el código que incluye este archivo se compila como C++,
    // extern "C" asegura que las funciones declaradas aquí se traten como C puro.
    // Esto evita errores de enlace en proyectos que mezclan C y C++.


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