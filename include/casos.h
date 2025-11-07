#ifndef CASOS_H
#define CASOS_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Arduino.h>
#include "main.h"
#include "multiplexado.h"
    void Casos(void);
    void Caso_A(void);
    void Caso_B(void);
    void Caso_C(void);
    void Caso_D(void);
    void valor_pulsadores(void); // Función que lee el valor de los pulsadores y cambia el modo
    enum Caso // Estados para la máquina de estado de los displays
    {
        Caso_a,
        Caso_b,
        Caso_c,
        Caso_d
    };
    

#ifdef __cplusplus
} // extern "C"
#endif

#endif