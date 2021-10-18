#include "RecibeInstrucciones.h"
#include <iostream>


void recibirInstruccion(Instrucciones* instruc) {
    std::string aux;
    std::getline(std::cin, aux, ' ');
    instruc->fila_inicial = std::stoi(aux);
    std::getline(std::cin, aux, ' ');
    instruc->fila_final = std::stoi(aux);
    std::getline(std::cin, aux, ' ');
    instruc->nro_filas_por_particion = std::stoi(aux);
    std::getline(std::cin, aux, ' ');
    instruc->nro_columna = std::stoi(aux);
    std::getline(std::cin, instruc->operacion);
}
