#ifndef TP2FINAL_ARCHIVO_H
#define TP2FINAL_ARCHIVO_H

#include <fstream>
#include <list>
#include "ManejaFilas.h"
#include "RecibeInstrucciones.h"
class Archivo {

private:
    std::ifstream ptrArchivo;
    int nro_columnas;
public:
    Archivo(const char* pathAlArchivo, int nro_columnas);
    int cargarParticiones(Instrucciones* instrucciones, int nro_particiones,
                        std::list<ManejaFilas>& particiones);
    ~Archivo();
};




#endif //TP2FINAL_ARCHIVO_H
