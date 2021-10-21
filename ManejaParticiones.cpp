#include "ManejaParticiones.h"

#define EXITO 0

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


Particion::Particion() {

}

Particion::Particion(Particion&& otraParticion)
        :filas(std::move(otraParticion.filas)) {

}

int Particion::generarParticiones(std::list<Particion>& particiones,
                                          std::list<Fila>&& filas) {
    return EXITO;
}

void Particion::aniadirFila(Fila&& fila){
    this->filas.push_back(std::move(fila));
}
Particion::~Particion() {

}
