#ifndef TUTORIAL_RECIBEINSTRUCCIONES_H
#define TUTORIAL_RECIBEINSTRUCCIONES_H

#include <string>
typedef struct Instrucciones{
    int fila_inicial;
    int fila_final;
    int nro_filas_por_particion;
    int nro_columna;
    std::string operacion;
}Instrucciones;

void recibirInstruccion(Instrucciones* instruc);

#endif //TUTORIAL_RECIBEINSTRUCCIONES_H
