#include "pulsadores.h"
#include "casos.h"

static uint16_t EP1 = UP;

void MDE_BOT(void) // Máquina de estado de los botones
{
    switch (EP1)
    {
    case UP: // Estado del pulsador: UP. Si se presiona paso al estado FALL
        if (((PINC >> PC0) & 1) == 0)
        {
            EP1 = FALL;
            tiempo_bot = 20;
        }
        break;
    case FALL: // Estado del pulsador: FALL. Si seguimos presionando y pasan 20ms, se pasa al estado DOWN
        if (((PINC >> PC0) & 1) == 1)
        {
            EP1 = UP;
            tiempo_bot = 0;
        }
        if (((PINC >> PC0) & 1) == 0 && tiempo_bot == 20) // Pulsando el boton aumentamos en 1 el valor a mostrar en el display
        {
            EP1 = DOWN;
            ADCSRA |= (1 << ADSC);  
        }
        break;
    case DOWN: // Estado del pulsador: DOWN. Si se suelta se pasa al estado RAISE
        if (((PINC >> PC0) & 1) == 1)
        {
            EP1 = RAISE;
            tiempo_bot = 20;
        }
        break;
    case RAISE: // Estado del pulsador: RAISE. Si seguimos soltandolo se pasa al estado UP
        if (((PINC >> PC0) & 1) == 0)
        {
            EP1 = DOWN;
            tiempo_bot = 0;
        }
        if (((PINC >> PC0) & 1) == 1 && tiempo_bot == 20)
        {
            EP1 = UP;
        }
        break;

    default:
        EP1 = UP;
    }
}
