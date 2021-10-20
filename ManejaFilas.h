#ifndef TUTORIAL_MANEJAFILAS_H
#define TUTORIAL_MANEJAFILAS_H

#include "Fila.h"
#include <list>
class ManejaFilas {

private:
    std::list<Fila> filas;

public:
    ManejaFilas();
    ManejaFilas(const ManejaFilas& otroMF) = delete;
    ManejaFilas(ManejaFilas&& otroMF);
    void aniadirFila(Fila&& fila);
    ~ManejaFilas();
};



#endif //TUTORIAL_MANEJAFILAS_H
