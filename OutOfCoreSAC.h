#ifndef TP2FINAL_OUTOFCORESAC_H
#define TP2FINAL_OUTOFCORESAC_H

#include "ControlaArchivo.h"
#include "ManejaFilas.h"
#include <list>

class OutOfCoreSAC {

private:
    ControlaArchivo controla_archivo;
    std::list<ManejaFilas> particiones;
    int cant_hilos;

public:

    OutOfCoreSAC(const char* path_al_archivo, int nro_columnas, int nro_hilos);

    void hacerOperacion();

    ~OutOfCoreSAC();

private:
    int cargarFilasDisponibles(std::list<Fila>& filas, int filas_restantes,
                                int max_filas);
    void ejecutarOperacionSobreParticiones(int nro_columna, std::string op,
                                           int cant_particiones);

};


#endif //TP2FINAL_OUTOFCORESAC_H
