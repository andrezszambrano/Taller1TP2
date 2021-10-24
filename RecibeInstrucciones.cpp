#include "RecibeInstrucciones.h"
#include <iostream>

#define SIN_INSTRUCCIONES -1
#define EXITO 0

int recibirInstruccion(Instrucciones* instruc) {
    std::string aux;
    std::getline(std::cin, aux, ' ');
    if (aux.empty())
        return SIN_INSTRUCCIONES;
    instruc->fila_inicial = std::stoi(aux);
    std::getline(std::cin, aux, ' ');
    instruc->fila_final = std::stoi(aux);
    std::getline(std::cin, aux, ' ');
    instruc->nro_filas_por_particion = std::stoi(aux);
    std::getline(std::cin, aux, ' ');
    instruc->nro_columna = std::stoi(aux);
    std::getline(std::cin, instruc->operacion);
    return EXITO;
}
