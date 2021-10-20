#ifndef TUTORIAL_FILA_H
#define TUTORIAL_FILA_H

#include <array>
#include <stdint.h>

#define MAX_COLUMNAS 10

class Fila {

private:
    std::array<uint16_t, MAX_COLUMNAS> nums_fila;
    int cant_columnas;
public:
    Fila();
    Fila(Fila&& otraFila);
    void aniadirNumero(uint16_t num);
    ~Fila();
};


#endif //TUTORIAL_FILA_H
