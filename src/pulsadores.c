#include "pulsadores.h" 
#include "casos.h"      

static uint16_t botones = SUELTO; // Variable estática que almacena el estado actual del boton

void MDE_BOT(void) // Máquina de estado de los botones
{
    switch (botones) 
    {
    case SUELTO: 
        // Comprueba si el pin del pulsador (PC0 en el registro PINC) está en estado BAJO (0), lo que indica una pulsación.
        if (BOT_A0 == 0) 
        {
            botones = BAJANDO; 
            time_bot = 20;      // Inicializa el contador del temporizador de antirrebote a 20.
        }
        break;
    
    case BAJANDO: 
        // Comprueba si el pulsador ha sido SOLTADO antes de que transcurran los 20ms.
        if (BOT_A0 == 1) 
        {
            botones = SUELTO;  // Si se soltó, vuelve inmediatamente al estado SUELTO y resetea el temporizador.
            time_bot = 0;
        }
        // Comprueba si el pulsador sigue presionado (0) Y el temporizador ha llegado a 20 (lo que implica que han pasado 20ms sin que se suelte).
        if (BOT_A0 == 0 && time_bot == 20) // Pulsando el boton aumentamos en 1 el valor a mostrar en el display
        {
            botones = PULSADO; 
            // Inicia la conversión del Conversor Analógico-Digital (ADC) al escribir un '1' en el bit ADSC (ADC Start Conversion) del registro ADCSRA.
            ADCSRA |= (1 << ADSC); 
        }
        break;
    
    case PULSADO: 
        // Comprueba si el pin del pulsador está en estado ALTO (1), lo que indica que se ha soltado.
        if (BOT_A0== 1)
        {
            botones = SUBIENDO; 
            time_bot = 20;       // Inicializa el contador del temporizador de antirrebote a 20.
        }
        break;
    
    case SUBIENDO:
        // Comprueba si el pulsador ha sido VUELTO A PRESIONAR antes de que transcurran los 20ms.
        if (BOT_A0 == 0)
        {
            botones = PULSADO; // Si se volvió a presionar, vuelve inmediatamente al estado PULSADO y resetea el temporizador.
            time_bot = 0;
        }
        // Comprueba si el pulsador sigue suelto (1) Y el temporizador ha llegado a 20 
        if (BOT_A0 == 1 && time_bot == 20)
        {
            botones = SUELTO;
        }
        break;

    default: 
        botones = SUELTO; // Se resetea el estado de la máquina a SUELTO.
    }
}