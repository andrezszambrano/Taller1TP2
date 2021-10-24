#ifndef TP2FINAL_MANEJAPARTICIONES_H
#define TP2FINAL_MANEJAPARTICIONES_H
#include "ResultadosParciales.h"
#include <array>
#include <list>
#include <stdint.h>
#include <string>
#include <memory>
#include <functional>
#include <map>
#define MAX_COLUMNAS 10

class Fila {
private:
    std::array<uint16_t, MAX_COLUMNAS> nums_fila;
    int cant_columnas;
public:
    Fila();
    Fila(Fila&& otraFila);
    int getColumna(int nro_columna) const;
    void aniadirNumero(uint16_t num);
    ~Fila();
};

class Particion {
private:
    std::list<Fila> filas;
    int cant_filas;
public:
    Particion();
    Particion(std::list<Fila>&& filas, int cant_filas);
    //Recibiendo una lista de particiones por referencia, crea particiones según
    //la cantidad de filas por particiones requerida.
    void operarFilas(std::shared_ptr<ResultadosParciales>&&
                        resultados_parciales, int nro_columna, std::string op);
    Particion(const Particion& otroMF) = delete;
    Particion(Particion&& otraParticion);
   // ejecutarOperacion(int nro_columna, std::string operacion, particiones)
    //void aniadirFila(Fila&& fila);
    ~Particion();
};

class MapaDeFunciones {
private:
    std::map<std::string, std::function<int(std::list<Fila>&, int)>> map;

public:
    MapaDeFunciones();
    int operar(std::list<Fila>& filas, const std::string& op, int nro_columna);
    ~MapaDeFunciones();
};

class InfoParticion {
public:
    std::shared_ptr<ResultadosParciales> resultados_parciales;
    int nro_indice_inicial;
    int nro_indice_final;
    int nro_columna;
    std::string operacion;

public:
    InfoParticion();
    InfoParticion(std::shared_ptr<ResultadosParciales> ptr, int fila_inicial,
                  int fila_final, int nro_columna, int nro_filas_por_particion,
                  const std::string& op);
    InfoParticion(InfoParticion&& otro);
    bool finDeParticiones();
    InfoParticion& operator=(const InfoParticion& otro);
    ~InfoParticion();
};

#endif //TP2FINAL_MANEJAPARTICIONES_H
