#include "tiempo.h"
volatile uint64_t time_bot = 0, tiempo = 0, time_total = 0;

void config_TIMER0(void)
{
    TCCR0A = (1 << WGM01);  // Activa el bit CTC (clear timer on compare match)                        // del TCCR0A (timer counter/control register)
    OCR0A = 62;             // valor de comparacion de int cada 1ms
    TCCR0B = (1 << CS02);   // divido por 256 y generar interrupciones cada 1 ms
    TIMSK0 = (1 << OCIE0A); // Habilita las interrupciones entimer compare
}

ISR(TIMER0_COMPA_vect)
{
    if (time_bot > 0)
    {
        time_bot--;
    }

    time_total++;
}

uint64_t get_time()
{
    return time_total;
}