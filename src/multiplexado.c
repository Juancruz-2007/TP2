#include "multiplexado.h"
#include "tiempo.h"

// Función que configura los pines de segmento de los puertos B y D para mostrar un dígito.
void encender_los_displays(uint8_t numero)
{
    // Tabla estática de mapeo de 7 segmentos (a, b, c, d, e, f, g).
    static uint16_t vector_display[14] =
        {
            0b11110011, //  a, b, c, d, e, f -> 0
            0b01100000, //  b, c -> 1
            0b10110101, //  a, b, d, e, g -> 2
            0b11110100, //  a, b, c, d, g -> 3
            0b01100110, //  b, c, f, g -> 4
            0b11010110, //  a, c, d, f, g -> 5
            0b11011111, //  a, c, d, e, f, g -> 6
            0b01110000, //  a, b, c -> 7
            0b11111111, //  a, b, c, d, e, f, g -> 8 
            0b11110110, //  a, b, c, d, f, g -> 9

            // Mapeos para el modo BINARIO (Muestra 2 bits por display)
            0b00000000, // BINARIO: 00 
            0b01000000, // BINARIO: 01 
            0b00000001, // BINARIO: 10 
            0b01000001  // BINARIO: 11 
        };
        
    // Configura los 4 bits más significativos de los segmentos en PORTD (bits PD4-PD7).
    // La máscara (0b00001111) 
    PORTD = (PORTD & 0b00001111) | ((~vector_display[numero] & 0b11110000));
    
    // Configura los 4 bits menos significativos de los segmentos en PORTB (bits PB0-PB3).
    // La máscara (0b11110000) 
    PORTB = (PORTB & 0b11110000) | ((~vector_display[numero] & 0b00001111));
}


void Multiplexado(uint16_t valor, uint8_t modo_de_display)
{
    // Variables para almacenar el dígito de cada uno de los 4 displays.
    uint16_t display4 = 0, display3 = 0, display2 = 0, display1 = 0; 
    
    // Variable estática para controlar el tiempo del ciclo de multiplexación.
    static uint64_t time_multiplexado = 0;

    // ----- Separación del valor según el modo -----
    switch (modo_de_display)
    {
    case DECIMAL:
        // Separa el valor en 4 dígitos decimales 
        display1 = (valor / 1000) % 10;
        display2 = (valor / 100) % 10;
        display3 = (valor / 10) % 10;
        display4 = valor % 10;
        break;
        
    case BINARIO:
        // Separa el valor en 4 grupos de 2 bits (8 bits en total).
        // El "+ 10" saltea los valores para decimal, yendo a  (0, 1, 2, 3) a los índices 10, 11, 12, 13 de la tabla.
        display1 = 10 + ((valor & 0b11000000) >> 6); // Bits 7 y 6
        display2 = 10 + ((valor & 0b00110000) >> 4); // Bits 5 y 4
        display3 = 10 + ((valor & 0b00001100) >> 2); // Bits 3 y 2
        display4 = 10 + ((valor & 0b00000011));      // Bits 1 y 0
        break;
    }
    
    // ----- Control de tiempo para el multiplexado -----
    if (get_time() > time_multiplexado)
    {
        static uint8_t cont = 0; // Contador estático para saber qué display está activo.

        //ENCIENDE TODOS LOS DISPLAYS
        PORTD &= ~((1 << PD2) | (1 << PD3));
        PORTB &= ~((1 << PB4) | (1 << PB5));
        
        // PB3 se apaga del .
        PORTB |= (1 << PB3); 

        // Enciende el display activo y muestra el dígito correspondiente.
        switch (cont)
        {
        case 0:
            PORTD |= (1 << PD2);       // Activa el Display 1 (Millares/Bits 7-6)
            encender_los_displays(display1);
            PORTB |= (1 << PB3);       // Asegura que el PB3 esté activo
            break;

        case 1:
            PORTD |= (1 << PD3);       // Activa el Display 2 (Centenas/Bits 5-4)
            encender_los_displays(display2);
            PORTB |= (1 << PB3);       // Asegura que el PB3 esté activo
            break;

        case 2:
            PORTB |= (1 << PB4);       // Activa el Display 3 (Decenas/Bits 3-2)
            encender_los_displays(display3);
            PORTB |= (1 << PB3);       // Asegura que el PB3 esté activo
            break;

        case 3:
            PORTB |= (1 << PB5);       // Activa el Display 4 (Unidades/Bits 1-0)
            encender_los_displays(display4);
            PORTB |= (1 << PB3);       // Asegura que el PB3 esté activo
            break;
        }
        
        // Incrementa el contador y lo reinicia (0 -> 1 -> 2 -> 3 -> 0).
        if (cont++ >= 3)
            cont = 0;

        // Establece el próximo tiempo de actualización (ejecución cada 5ms).
        time_multiplexado = get_time() + 5; 
    }
}