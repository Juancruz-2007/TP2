#include "casos.h" 

enum Caso Estado_de_Caso = Caso_a;

// Función principal de la Máquina de Estados.
void Casos(void)
{
    switch (Estado_de_Caso) // Reviso el modo y ejecuto la función correspondiente
    {
    case Caso_a:
        Caso_A(); // Llama a la función del Caso A.
        break;
    case Caso_b:
        Caso_B(); // Llama a la función del Caso B.
        break;
    case Caso_c:
        Caso_C(); // Llama a la función del Caso C.
        break;
    case Caso_d:
        Caso_D(); // Llama a la función del Caso D.
        break;
    }
}

// Implementación del Caso A: Muestra 8 bits del valor ADC en Binario.
void Caso_A(void)
{
 Multiplexado(valor_de_ADC >> 2, BINARIO); 
 // Máquina de Estado para el display en modo A
 //((valor_de_ADC >> 2): Desplaza el valor de 10 bits del ADC 2 posiciones a la derecha.)
}

// Implementación del Caso B: Muestra 8 bits del valor ADC en Decimal.
void Caso_B(void)
{
    // Muestra el valor de 8 bits del ADC (valor_de_ADC >> 2) en formato DECIMAL.
    Multiplexado(valor_de_ADC >> 2, DECIMAL); // Máquina de Estado para cada display
}

// Implementación del Caso C: Muestra el valor completo (10 bits) del ADC en Decimal.
void Caso_C(void)
{
    // Muestra el valor completo de 10 bits del ADC (valor_de_ADC) en formato DECIMAL.
    Multiplexado(valor_de_ADC, DECIMAL); // Máquina de Estado para cada display
}

// Implementación del Caso D: Calcula y muestra el valor de la tensión en milivoltios.
void Caso_D(void)
{
    valor_en_milivolt = ((uint32_t)valor_de_ADC * 4883) / 1000;// Realiza la conversión del valor digital (ADC) a milivolts.
    // Si la referencia es 5V (5000mV), la conversión sería: mV = (valor_de_ADC * 5000) / 1024.
    // El factor 4883 / 1000 es una aproximación: 4883/1000 ≈ 4.883, que es la escala de 5000/1024 ≈ 4.8828.
    // Se usa (uint32_t) para forzar la multiplicación a ser de 32 bits y evitar desbordamiento.
    // Muestra el valor calculado en milivoltios en formato DECIMAL.
    Multiplexado(valor_en_milivolt, DECIMAL); // Máquina de Estado para cada display
}

// Función para leer el estado de los pulsadores y cambiar el modo de operación (Estado_de_Caso).
void valor_pulsadores(void)
{ 
    // Botón 1 presionado: Establece el modo a Caso_a (Binario 8 bits).
    if ((valor_de_puls >= 450) && (valor_de_puls <= 573))
    {
        Estado_de_Caso = Caso_a;//bot1 binario 8bit
    }
    // Botón 2 presionado: Establece el modo a Caso_b (Decimal 8 bits).
    else if ((valor_de_puls >= 276) && (valor_de_puls <= 359))
    {
        Estado_de_Caso = Caso_b;//bot2 decimal 8bit
    }
    // Botón 3 presionado: Establece el modo a Caso_c (Decimal 10 bits).
    else if ((valor_de_puls >= 215) && (valor_de_puls <= 270))
    {
        Estado_de_Caso = Caso_c;//bot3 decimal 10bit
    }
    // Botón 4 presionado: Establece el modo a Caso_d (Muestra en milivoltios).
    else if ((valor_de_puls >= 150) && (valor_de_puls <= 203))
    {
        Estado_de_Caso = Caso_d;//bot4 muestra mili volt
    }
}