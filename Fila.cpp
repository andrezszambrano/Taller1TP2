#include "Fila.h"
#include <iostream>

Fila::Fila(): cant_columnas(0) {

}


Fila::Fila(Fila&& otraFila)
            :nums_fila(std::move(otraFila.nums_fila)),
             cant_columnas(otraFila.cant_columnas) {

}

void Fila::aniadirNumero(uint16_t num) {
    this->nums_fila[this->cant_columnas] = num;
    this->cant_columnas++;
}

Fila::~Fila() {

}