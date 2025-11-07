#ifndef PULSADORES_H
#define PULSADORES_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <Arduino.h>
#include "casos.h"
#include "main.h"
    enum ESTADO_PULSADOR
    {
        UP,
        FALL,
        DOWN,
        RAISE
    };
    void MDE_BOT(void);
#ifdef __cplusplus
} // extern "C"
#endif

#endif