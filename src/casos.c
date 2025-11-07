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
    Multiplexado(valorAdc >> 2, BINARIO); // Máquina de Estado para el display en modo A
}

void Caso_B(void)
{
    Multiplexado(valorAdc >> 2, DECIMAL); // Máquina de Estado para cada display
}

void Caso_C(void)
{
    Multiplexado(valorAdc, DECIMAL); // Máquina de Estado para cada display
}

void Caso_D(void)
{
    valorMV = ((uint32_t)valorAdc * 4883) / 1000;
    Multiplexado(valorMV, DECIMAL); // Máquina de Estado para cada display
}

void valor_pulsadores(void)
{ // Dependiendo de qué pulsador se presione, se leerá un valor distinto de tensión
    // Dependiendo de ese valor de tensión leído se pondrá el programa en un respectivo modo


    if ((valorPulsadores >= 450) && (valorPulsadores <= 573))
    {
        Estado_Caso = Caso_a;//bot1 binario 8bit
    }
    else if ((valorPulsadores >= 276) && (valorPulsadores <= 359))
    {
        Estado_Caso = Caso_b;//bot2 decimal 8bit
    }
    else if ((valorPulsadores >= 215) && (valorPulsadores <= 270))
    {
        Estado_Caso = Caso_c;//bot3 decimal 10bit
    }
    else if ((valorPulsadores >= 150) && (valorPulsadores <= 203))
    {
        Estado_Caso = Caso_d;//bot4 muestra mili volt
    }
}