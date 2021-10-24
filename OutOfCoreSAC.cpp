#include "OutOfCoreSAC.h"
#include "RecibeInstrucciones.h"
#include <string>
#include <utility>
#include "ThreadSafeQueue.h"
#include "ResultadosParciales.h"
#define ERROR -1
#define EXITO 0
#define SIN_INSTRUCCIONES -1

OutOfCoreSAC::OutOfCoreSAC(const char* path_al_archivo, int nro_columnas,
                            int nro_hilos)
                            :controla_archivo(path_al_archivo, nro_columnas),
                            cant_hilos(nro_hilos) {
}

void OutOfCoreSAC::cargarTodasLasTareas(ThreadSafeQueue& cola,
                 std::list<std::shared_ptr<ResultadosParciales>>& resultados) {
    bool hay_tareas = true;
    while (hay_tareas) {
        Instrucciones instruc;
        int aux = recibirInstruccion(&instruc);
        if (aux == SIN_INSTRUCCIONES) {
            hay_tareas = false;
        } else {
           std::shared_ptr<ResultadosParciales> ptr;
           ResultadosParciales::crear(ptr, instruc.operacion);
           resultados.push_back(ptr);
           for (int fila_inicial = instruc.fila_inicial;
                fila_inicial < instruc.fila_final;
                fila_inicial = fila_inicial + instruc.nro_filas_por_particion) {
               InfoParticion info(ptr, fila_inicial, instruc.fila_final,
                          instruc.nro_columna, instruc.nro_filas_por_particion,
                          instruc.operacion);
               cola.push(std::move(info));
           }
        }
    }
    InfoParticion info(NULL, 0, 0, 0, 0, "hola");
    cola.push(std::move(info));
}

void OutOfCoreSAC::ejecutarTareas(ThreadSafeQueue& cola) {
    bool iterar = true;
    while (iterar) {
        InfoParticion info;
        cola.pop(info);
        if (info.finDeParticiones()) {
            iterar = false;
        } else {
            std::list<Fila> filas;
            this->controla_archivo.cargarFilasSegunInfo(filas, info);
            Particion particion(std::move(filas), filas.size());
            particion.operarFilas(std::move(info.resultados_parciales),
                                  info.nro_columna, info.operacion);
        }
    }
}

void juntarResultadosParcialesYMostrar(
            std::list<std::shared_ptr<ResultadosParciales>>& resultados) {
    std::list<std::shared_ptr<ResultadosParciales>>::iterator it;
    for (it = resultados.begin(); it != resultados.end(); ++it){
        (*it)->terminarOperacion();
        (*it)->imprimirResultado();
    }
}

int OutOfCoreSAC::hacerOperacionEnHiloMain() {
    //Como no se tendrán threads, cargo todas las particiones de una vez
    std::list<std::shared_ptr<ResultadosParciales>> resultados;
    ThreadSafeQueue cola;
    this->cargarTodasLasTareas(cola, resultados);
    this->ejecutarTareas(cola);
    juntarResultadosParcialesYMostrar(resultados);
    return EXITO;
}

int OutOfCoreSAC::hacerOperacion() {
   // if (this->cant_hilos == 0) //solo el hilo main
        return this->hacerOperacionEnHiloMain();
   // return 0;
}

OutOfCoreSAC::~OutOfCoreSAC() {
}
