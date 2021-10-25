#ifndef TP2FINAL_OUTOFCORESAC_H
#define TP2FINAL_OUTOFCORESAC_H

#include "ControlaArchivo.h"
#include "ManejaParticiones.h"
#include "ThreadSafeQueue.h"
#include <memory>
#include "ResultadosParciales.h"
#include <list>
#include <string>
#include <thread>

class OutOfCoreSAC {
private:
    const char* path_al_archivo;
    int nro_columnas;
    int cant_hilos;

public:
    //Crea un OutOfCoreSAC recibiendo el path al archivo, el número de columnas
    //que tiene cada fila y la cantidad de hilos con la que se quiere que se
    //hagan las operaciones.
    OutOfCoreSAC(const char* path_al_archivo, int nro_columnas, int nro_hilos);

    //Pide una serie de instrucciones por stdin, y opera acorde. En caso de que
    //el dataset no tenga un formato válido (filas o números entrecortados), o
    //que alguna instrucción no sea válida, se lanza una runtime exception con
    //un mensaje acorde.
    void hacerOperaciones();

    //Libera los recursos del OutOfCoreSAC acorde.
    ~OutOfCoreSAC();

private:
    //Función que carga las particiones según las instrucciones recibidas,
    //ejecuta las tareas y termina juntando todos los resultados. En caso de que
    //el dataset no tenga un formato válido (filas incompletas o números
    //entrecortados), o que alguna instrucción no sea válida, se lanza una
    //runtime exception con un mensaje acorde.
    void hacerOperacionEnHiloMain();

    //Carga todas las tareas recibidas por stdin en una cola thread safe. Por
    //cada tarea, se crea en el heap usando punteros inteligentes compartidos
    //un objeto del tipo ResultadoParcial acorde con la operación requerida por
    //la instrucción recibida cargando dicho puntero a la lista de resultados
    //parciales. En caso de que alguna instrucción leída por stdin sea
    //incorrecta, se lanza una runtime exception con un mensaje acorde.
    void cargarTareasRestantes(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    //Se sacan tareas de la thread safe cola. Por cada tarea, se cargan las
    //filas requeridas, se crea la partición correspondiente, y se opera acorde
    //la información sacada de la cola. El resultado parcial se guarda en el
    //objeto apuntado por el ptr resultados_parciales. En caso de que el dataset
    //no tenga un formato válido (filas incompletas o números entrecortados)
    //void ejecutarTareas(ThreadSafeQueue& cola);

    //Carga las filas dada por info, crea la partición correspondiente y ejecuta
    //la tarea correspondiente. El resultado parcial se guarda en el objeto
    //apuntado por el ptr resultados_parciales. En caso de que el dataset
    //no tenga un formato válido (filas incompletas o números entrecortados)
    //void cargarParticionYEjecutarTarea(InfoParticion& info);

    void hacerOperacionesConNHilos();

    //Se cargan por lo menos N tareas a la thread safe cola, N siendo el número
    //de hilos pedidos.
    void cargarNTareas(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    void crearNHilos(ThreadSafeQueue& cola, std::list<std::thread>& hilos);

    void joinNHilos(std::list<std::thread>& hilos);
};

#endif //TP2FINAL_OUTOFCORESAC_H
