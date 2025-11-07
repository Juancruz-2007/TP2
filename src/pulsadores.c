#include "pulsadores.h"
#include "casos.h"

static uint16_t pulsadores = SUELTO;

void MDE_BOT(void) // Máquina de estado de los botones
{
    switch (pulsadores)
    {
    case SUELTO: // Estado del pulsador: SUELTO. Si se presiona paso al estado BAJANDO
        if (((PINC >> PC0) & 1) == 0)
        {
            pulsadores = BAJANDO;
            tiempo_bot = 20;
        }
        break;
    case BAJANDO: // Estado del pulsador: BAJANDO. Si seguimos presionando y pasan 20ms, se pasa al estado PULSADO
        if (((PINC >> PC0) & 1) == 1)
        {
            pulsadores = SUELTO;
            tiempo_bot = 0;
        }
        if (((PINC >> PC0) & 1) == 0 && tiempo_bot == 20) // Pulsando el boton aumentamos en 1 el valor a mostrar en el display
        {
            pulsadores = PULSADO;
            ADCSRA |= (1 << ADSC);  
        }
        break;
    case PULSADO: // Estado del pulsador: PULSADO. Si se suelta se pasa al estado SUBIENDO
        if (((PINC >> PC0) & 1) == 1)
        {
            pulsadores = SUBIENDO;
            tiempo_bot = 20;
        }
        break;
    case SUBIENDO: // Estado del pulsador: SUBIENDO. Si seguimos soltandolo se pasa al estado SUELTO
        if (((PINC >> PC0) & 1) == 0)
        {
            pulsadores = PULSADO;
            tiempo_bot = 0;
        }
        if (((PINC >> PC0) & 1) == 1 && tiempo_bot == 20)
        {
            pulsadores = SUELTO;
        }
        break;

    default:
        pulsadores = SUELTO;
    }
}
