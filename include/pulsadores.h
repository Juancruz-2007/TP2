#ifndef PULSADORES_H
#define PULSADORES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Arduino.h>
#include "casos.h"
#include "main.h"
#define BOT_A0 ((PINC>>PC0)&1)

    enum ESTADO_PULSADOR
    {
        SUELTO,
        BAJANDO,
        PULSADO,
        SUBIENDO
    };
    void MDE_BOT(void);
#ifdef __cplusplus
} // extern "C"
#endif

#endif