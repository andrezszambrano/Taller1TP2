#ifndef TUTORIAL_MANEJAFILAS_H
#define TUTORIAL_MANEJAFILAS_H

#include "fila.h"
#include <list>
class ManejaFilas {

private:
    std::list<Fila> filas;

public:
    ManejaFilas();
    ~ManejaFilas();
};



#endif //TUTORIAL_MANEJAFILAS_H
