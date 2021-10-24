#ifndef TP2FINAL_MANEJAPARTICIONES_H
#define TP2FINAL_MANEJAPARTICIONES_H

#include <array>
#include <list>
#include <stdint.h>
#include <string>

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
    Particion(std::list<Fila>&& filas);
    //Recibiendo una lista de particiones por referencia, crea particiones según
    //la cantidad de filas por particiones requerida.
    static int generarParticiones(std::list<Particion>& particiones,
                                  int particiones_por_fila,
                                  std::list<Fila>&& filas);
    Particion(const Particion& otroMF) = delete;
    Particion(Particion&& otraParticion);
   // ejecutarOperacion(int nro_columna, std::string operacion, particiones)
    void aniadirFila(Fila&& fila);
    ~Particion();
};


class InfoParticion {
    int nro_indice_inicial;
    int nro_indice_final;
    int nro_columna;
    std::string operacion;

public:
    InfoParticion();
    InfoParticion(int fila_inicial, int fila_final, int nro_columna,
                  int nro_filas_por_particion, std::string op);
    InfoParticion(InfoParticion&& otro);
    InfoParticion& operator=(const InfoParticion& otro);
    ~InfoParticion();

};

#endif //TP2FINAL_MANEJAPARTICIONES_H
