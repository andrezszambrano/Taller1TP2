#ifndef TP2FINAL_OUTOFCORESAC_H
#define TP2FINAL_OUTOFCORESAC_H

#include "ControlaArchivo.h"
#include "ManejaParticiones.h"
#include "ThreadSafeQueue.h"
#include <memory>
#include "ResultadosParciales.h"
#include <list>

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
    //Compara el número de filas restantes y la cantidad máxima de filas que se
    //pueden cargar, y se intentan cargar como máximo N filas, N siendo el
    //número menor de estos. Si hay algún error en el formato del dataset se
    //retorna -1. Se retorna la cantidad cargada de filas: un número entre 0 y N
    int cargarFilasDisponibles(std::list<Fila>& filas, int filas_restantes,
                                int max_filas);

    int hacerOperacionEnHiloMain();

    void cargarTodasLasTareas(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    void ejecutarTareas(ThreadSafeQueue& cola);

    void ejecutarOperacionSobreParticiones(int nro_columna, std::string op,
                                           int cant_particiones);

};


#endif //TP2FINAL_OUTOFCORESAC_H
