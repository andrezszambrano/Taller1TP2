#include "ManejaFilas.h"


ManejaFilas::ManejaFilas() {

}

ManejaFilas::ManejaFilas(ManejaFilas&& otroMF)
                :filas(std::move(otroMF.filas))
            {

}

void ManejaFilas::aniadirFila(Fila&& fila){
    this->filas.push_back(fila);
}
ManejaFilas::~ManejaFilas() {

}