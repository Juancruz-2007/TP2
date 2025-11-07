#include <Arduino.h>
#include "main.h"

// Variables volátiles (se pueden cambiar en interrupciones) para almacenar los valores leídos.
volatile uint16_t valor_de_puls,valor_de_ADC;// valor_de_ADC: Medición del potenciómetro/sensor. valor_del_Pulsadores: Medición de los pulsadores.
volatile uint32_t valor_en_milivolt; // Variable para almacenar el valor convertido en milivoltios.

// -------- Funcion de inicializacion del conversor A/D --------- //
static inline void initADC0(void)
{
  /* usamos como referencia el valor de AVCC */
  // Configura la referencia de voltaje del ADC a AVCC.
  ADMUX |= (1 << REFS0);

  /* ADC clock prescaler 16MHz/128 = 125KHz */
  // Configura el prescaler a 128 (ADPS2, ADPS1, ADPS0 = 1).
  ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

  /* Habilito las interrupciones del conversor AD con ADIE */
  // Habilita las interrupciones (ADIE) y el modo Auto Trigger (ADATE).
  ADCSRA |= ((1 << ADIE) | (1 << ADATE));

  /* Habillitamos el ADC */
  // Activa el módulo ADC (ADEN).
  ADCSRA |= (1 << ADEN);
}

int main(void)
{
  /* Inicializo el ADC llamando a su funcion*/
  initADC0();
  // Inicializa el Timer 0 (código no visible).
  config_TIMER0();

  /* Configuro las entradas y salidas */
  DDRC &= ~(0x03); // Configuro PC0 y PC1 como entrada (Botones)
  PORTC |= 0x01;   // Habilito el pull-up en PC0
  DDRD |= 0xFC;
  DDRB |= 0x37;
  ADCSRA |= (1 << ADLAR); // Justificación a la izquierda
  ADCSRA |= (1 << ADSC);  // Inicio la primera conversión

  // Habilita las interrupciones globales.

  sei();

  while (1)
  {
    // Reviso el valor de los pulsadores para setear el modo del display
    valor_pulsadores();

    // Reviso el estado de los botones para aumentar o disminuir el valor a mostrar en el display
    MDE_BOT();

    // Reviso el modo y ejecuto la función correspondiente (probablemente manejo del display).
    Casos();
  }

  return (0);
}

// Rutina de Servicio de Interrupción para el vector ADC (ISR).
// Se ejecuta al finalizar cada conversión del ADC.
ISR(ADC_vect)
{
  // Bandera estática para alternar la lectura entre los dos canales ADC (multiplexación por software).
  static bool flag_adc = false;

  // Si flag_adc es false, se está leyendo el canal 0 (potenciómetro/sensor).
  if (flag_adc == false)
  {
    // Almacena el resultado de la conversión anterior (Canal 0).
    valor_de_ADC = ADC; // medicion con el pote

    // Siguiente interrupción leerá el canal 1.
    flag_adc = true;

    // Configura la entrada del ADC al canal 1 (ADC1) para la próxima conversión.
    ADMUX |= (1 << MUX0); // pone el canal 1 del ADC
  }
  // Si flag_adc es true, se está leyendo el canal 1 (pulsadores).
  else
  {
    // Almacena el resultado de la conversión anterior (Canal 1).
    valor_de_puls = ADC; // valor del canal 0

    // Siguiente interrupción leerá el canal 0.
    flag_adc = false;

    // Configura la entrada del ADC al canal 0 (ADC0) para la próxima conversión.
    ADMUX &= ~(1 << MUX0); // guarda valor de tension en los pulsadores en canal 0 del ADC
  }
}