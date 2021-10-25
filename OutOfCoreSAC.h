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
    //hagan las operaciones. Si el archivo dado no existe, se lanza una runtime
    //exception con mensaje.
    OutOfCoreSAC(const char* path_al_archivo, int nro_columnas, int nro_hilos);

    //Pide una serie de instrucciones por stdin, y opera acorde. En caso de que
    //el dataset no tenga un formato válido (filas o números entrecortados), o
    //que alguna instrucción no sea válida, se lanza una runtime exception con
    //un mensaje acorde. Si la cantidad de hilos pedida en el constructor es 0,
    //solo se trabaja con el hilo main. Por otro lado, si se piden N hilos, N
    //mayor a 0, se crean N hilos para la ejecución.
    void hacerOperaciones();

    //Libera los recursos del OutOfCoreSAC acorde.
    ~OutOfCoreSAC();

private:
    //Función que carga las particiones según las instrucciones recibidas,
    //ejecuta las tareas y termina juntando todos los resultados. En caso de que
    //el dataset no tenga un formato válido (filas incompletas o números
    //entrecortados), o que alguna instrucción no sea válida, se lanza una
    //runtime exception con un mensaje acorde.
    void hacerOperacionEnHiloMain(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    //Carga todas las tareas recibidas por stdin en una cola thread safe. Por
    //cada tarea, se crea en el heap usando punteros inteligentes compartidos
    //un objeto del tipo ResultadoParcial acorde con la operación requerida por
    //la instrucción recibida cargando dicho puntero a la lista de resultados
    //parciales. En caso de que alguna instrucción leída por stdin sea
    //incorrecta, se lanza una runtime exception con un mensaje acorde.
    void cargarTareasRestantes(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    //Función que hace lo mismo que hacerOperacionEnHiloMain, solo que con N
    //hilos más, N siendo la cantidad de hilos pedidos.
    void hacerOperacionesConNHilos(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    //Se cargan por lo menos N tareas a la thread safe cola, N siendo el número
    //de hilos pedidos.
    void cargarNTareas(ThreadSafeQueue& cola,
                   std::list<std::shared_ptr<ResultadosParciales>>& resultados);

    //Se crean N hilos, almacenandolos en la lista de hilos pasadas por
    //referencia
    void crearNHilos(ThreadSafeQueue& cola, std::list<std::thread>& hilos);

    //Se joinean los N hilos creados previamente con crearNHilos.
    void joinNHilos(std::list<std::thread>& hilos);
};

#endif //TP2FINAL_OUTOFCORESAC_H
