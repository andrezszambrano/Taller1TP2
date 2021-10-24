#include "RecibeInstrucciones.h"
#include <iostream>

#define SIN_INSTRUCCIONES -1
#define EXITO 0

void checkInstrucciones(Instrucciones* instruc, int nro_columnas) {
    if (instruc->fila_inicial >= instruc->fila_final)
        throw std::runtime_error("Error: fila inicial de instrucción debe ser "
                                 "menor estricto a la fila final.");
    if (instruc->nro_filas_por_particion < 1)
        throw std::runtime_error("Error: el número de filas por partición debe "
                                 "ser mayor o igual a uno.");
    if (instruc->nro_columna > nro_columnas - 1 || instruc->nro_columna < 0)
        throw std::runtime_error("Error: el número de columna no es válido. "
                                 "Recuerde que los índices de las columnas "
                                 "comienzan desde el cero.");
    std::string op = instruc->operacion;
    if (op != "sum" && op != "mean" && op != "max" && op != "min")
        throw std::runtime_error("Error: las operaciones posibles son 'sum', "
                                 "'mean', 'max', 'min'.");
    //No se puede chequear acá si el número de columna es correcto.
}

int recibirInstruccion(Instrucciones* instruc, int nro_columnas) {
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
    checkInstrucciones(instruc, nro_columnas);
    return EXITO;
}
