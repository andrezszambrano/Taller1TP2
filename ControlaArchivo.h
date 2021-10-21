#ifndef TP2FINAL_ARCHIVO_H
#define TP2FINAL_ARCHIVO_H

#include <fstream>
#include <list>
#include "ManejaFilas.h"
#include "RecibeInstrucciones.h"

class Archivo {

private:
    std::ifstream ptrArchivo;
public:
    Archivo(const char* pathAlArchivo);
    int leerNBytes(char* buf, int cant_bytes);
    ~Archivo();
};

class ControlaArchivo {

private:
    Archivo archivo;
    int nro_columnas;
public:
    ControlaArchivo(const char* pathAlArchivo, int nro_columnas);
    void descartarPrimerasNFilas(int cant_filas_a_descartar);
    int cargarHastaNFilas(std::list<Fila>& filas, int cant_filas_a_cargar);
    ~ControlaArchivo();

private:
    int cargarParticion(ManejaFilas& particion, int nro_filas_por_particion);
    int cargarFila(Fila& fila);
};


#endif //TP2FINAL_ARCHIVO_H
