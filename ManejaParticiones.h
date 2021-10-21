#ifndef TP2FINAL_MANEJAPARTICIONES_H
#define TP2FINAL_MANEJAPARTICIONES_H

#include <array>
#include <list>
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

class Particion {

private:
    std::list<Fila> filas;

public:
    Particion();
    static int generarParticiones(std::list<Particion>& particiones,
                                  std::list<Fila>&& filas);
    Particion(const Particion& otroMF) = delete;
    Particion(Particion&& otraParticion);
    void aniadirFila(Fila&& fila);
    ~Particion();
};


#endif //TP2FINAL_MANEJAPARTICIONES_H
