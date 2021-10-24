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

//Lee y almacena las instrucciones obtenidas por stdin. Si se lee una línea
//vacía (no hay más instrucciones), se devuelve -1. Si se leen las instrucciones
//y estas cumplen con 1. start-range < end-range. 2. partition-rows >= 1.
//3. El índice N de columna es válido (0 <= N < nro_columnas). 4. operacion es
//sum, mean, min o max, entonces se devuelve 0. Por otro lado, si alguna de
//estas condiciones no se cumple, se lanza una runtime exception con un mensaje
//de error.
int recibirInstruccion(Instrucciones* instruc, int nro_columnas);

#endif //TUTORIAL_RECIBEINSTRUCCIONES_H
