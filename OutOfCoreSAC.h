#ifndef TP2FINAL_OUTOFCORESAC_H
#define TP2FINAL_OUTOFCORESAC_H

#include "ControlaArchivo.h"
#include "ManejaParticiones.h"
#include "ThreadSafeQueue.h"
#include <memory>
#include "ResultadosParciales.h"
#include <list>
#include <string>

class OutOfCoreSAC {
private:
    ControlaArchivo controla_archivo;
    int cant_hilos;

public:
    //Crea un OutOfCoreSAC recibiendo el path al archivo, el número de columnas
    //que tiene cada fila y la cantidad de hilos con la que se quiere que se
    //hagan las operaciones.
    OutOfCoreSAC(const char* path_al_archivo, int nro_columnas, int nro_hilos);

    //Pide una serie de instrucciones por stdin, y opera acorde. En caso de que
    //el dataset no tenga un formato válido (filas o números entrecortados), se
    //retorna -1 y se imprime en stderr. Si se pide leer más filas de las que
    //están disponibles en el dataset se devuelve también -1 y se imprime en
    //stderr. Si se piden leer a partir de x fila, y solo hay w filas (x > w)
    //se retorna -1 y se imprime en stderr. En caso de éxito se retorna 0.
    int hacerOperacion();

    //Libera los recursos del OutOfCoreSAC acorde.
    ~OutOfCoreSAC();

private:

    int hacerOperacionEnHiloMain();

    void cargarTodasLasTareas(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    void ejecutarTareas(ThreadSafeQueue& cola);
};


#endif //TP2FINAL_OUTOFCORESAC_H
