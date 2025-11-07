#include "casos.h"

enum Caso Estado_Caso = Caso_a; // Global variable for case state



void Casos(void)
{
    // static enum Caso Estado_Caso = Caso_d; // Moved to global scope
    switch (Estado_Caso) // Reviso el modo y ejecuto la función correspondiente
    {
    case Caso_a:
        Caso_A();
        break;
    case Caso_b:
        Caso_B();
        break;
    case Caso_c:
        Caso_C();
        break;
    case Caso_d:
        Caso_D();
        break;
    }
}
void Caso_A(void)
{
    Multiplexado(valor_de_ADC >> 2, BINARIO); // Máquina de Estado para el display en modo A
}

void Caso_B(void)
{
    Multiplexado(valor_de_ADC >> 2, DECIMAL); // Máquina de Estado para cada display
}

void Caso_C(void)
{
    Multiplexado(valor_de_ADC, DECIMAL); // Máquina de Estado para cada display
}

void Caso_D(void)
{
    valor_en_milivolt = ((uint32_t)valor_de_ADC * 4883) / 1000;
    Multiplexado(valor_en_milivolt, DECIMAL); // Máquina de Estado para cada display
}

void valor_pulsadores(void)
{ // Dependiendo de qué pulsador se presione, se leerá un valor distinto de tensión
    // Dependiendo de ese valor de tensión leído se pondrá el programa en un respectivo modo


    if ((valor_de_puls >= 450) && (valor_de_puls <= 573))
    {
        Estado_Caso = Caso_a;//bot1 binario 8bit
    }
    else if ((valor_de_puls >= 276) && (valor_de_puls <= 359))
    {
        Estado_Caso = Caso_b;//bot2 decimal 8bit
    }
    else if ((valor_de_puls >= 215) && (valor_de_puls <= 270))
    {
        Estado_Caso = Caso_c;//bot3 decimal 10bit
    }
    else if ((valor_de_puls >= 150) && (valor_de_puls <= 203))
    {
        Estado_Caso = Caso_d;//bot4 muestra mili volt
    }
}