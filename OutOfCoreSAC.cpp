#include "OutOfCoreSAC.h"
#include "RecibeInstrucciones.h"
#include <string>
#include <utility>
#include <thread>
#include "ThreadSafeQueue.h"
#include "ResultadosParciales.h"
#define ERROR -1
#define EXITO 0
#define SIN_INSTRUCCIONES -1

OutOfCoreSAC::OutOfCoreSAC(const char* path_al_archivo, int nro_columnas,
                            int nro_hilos)
                            :path_al_archivo(path_al_archivo),
                             nro_columnas(nro_columnas),
                             cant_hilos(nro_hilos) {
    if (FILE *file = fopen(this->path_al_archivo, "r"))
        fclose(file);
    else
        throw std::runtime_error("Error: el archivo no existe.");
}

void generarYCargarToken(ThreadSafeQueue& cola) {
    InfoParticion info;
    InfoParticion::crearToken(info);
    cola.push(std::move(info));
}

void generarYCargarNTokens(ThreadSafeQueue& cola, int cant_hilos) {
    for (int i = 0; i < cant_hilos; i++)
        generarYCargarToken(cola);
}

int cargarPunteroAResultadoParcialYCargarInfoParticiones(ThreadSafeQueue& cola,
                std::list<std::shared_ptr<ResultadosParciales>>& resultados,
                const Instrucciones& instruc) {
    std::shared_ptr<ResultadosParciales> ptr;
    ResultadosParciales::crear(ptr, instruc.operacion);
    resultados.push_back(ptr);
    int contador_tareas = 0;
    for (int fila_inicial = instruc.fila_inicial;
         fila_inicial < instruc.fila_final;
         fila_inicial = fila_inicial + instruc.nro_filas_por_particion) {
        InfoParticion info(ptr, fila_inicial, instruc.fila_final,
                           instruc.nro_columna, instruc.nro_filas_por_particion,
                           instruc.operacion);
        cola.push(std::move(info));
        contador_tareas++;
    }
    return contador_tareas;
}

void OutOfCoreSAC::cargarTareasRestantes(ThreadSafeQueue& cola,
                 std::list<std::shared_ptr<ResultadosParciales>>& resultados) {
    bool hay_tareas = true;
    while (hay_tareas) {
        Instrucciones instruc;
        int aux = recibirInstruccion(&instruc, this->nro_columnas);
        if (aux == SIN_INSTRUCCIONES)
            hay_tareas = false;
        else
            cargarPunteroAResultadoParcialYCargarInfoParticiones(cola,
                                                                 resultados,
                                                                 instruc);
    }
}

void cargarParticionYEjecutarTarea(InfoParticion& info,
                                           ControlaArchivo& controla_archivo) {
    std::list<Fila> filas;
    controla_archivo.cargarFilasSegunInfo(filas, info);
    Particion particion(std::move(filas), filas.size());
    particion.operarFilas(std::move(info.resultados_parciales),
                          info.nro_columna, info.operacion);
}

void ejecutarTareas(ThreadSafeQueue& cola, const char* path_al_archivo,
                     int nro_columnas) {
    ControlaArchivo controlaArchivo(path_al_archivo, nro_columnas);
    bool iterar = true;
    while (iterar) {
        InfoParticion info;
        cola.pop(info);
        if (info.finDeParticiones())
            iterar = false;
        else
            cargarParticionYEjecutarTarea(info, controlaArchivo);
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

void OutOfCoreSAC::hacerOperacionEnHiloMain() {
    //Como no se tendrán threads, cargo todas las particiones de una vez
    std::list<std::shared_ptr<ResultadosParciales>> resultados;
    ThreadSafeQueue cola;
    this->cargarTareasRestantes(cola, resultados);
    generarYCargarToken(cola);
    ejecutarTareas(cola, this->path_al_archivo, this->nro_columnas);
    juntarResultadosParcialesYMostrar(resultados);
}

void OutOfCoreSAC::cargarNTareas(ThreadSafeQueue& cola,
                  std::list<std::shared_ptr<ResultadosParciales>>& resultados) {
    int contador_tareas = 0;
    bool hay_tareas = true;
    while (hay_tareas && (contador_tareas < this->cant_hilos)) {
        Instrucciones instruc;
        int aux = recibirInstruccion(&instruc, this->nro_columnas);
        if (aux == SIN_INSTRUCCIONES)
            hay_tareas = false;
        else
            contador_tareas = contador_tareas +
                    cargarPunteroAResultadoParcialYCargarInfoParticiones(cola,
                                                                  resultados,
                                                                     instruc);
    }
}

void OutOfCoreSAC::crearNHilos(ThreadSafeQueue& cola,
                               std::list<std::thread>& hilos) {
    for (int i = 0; i < this->cant_hilos; i++) {
        std::thread hilo(ejecutarTareas, std::ref(cola), this->path_al_archivo,
                          this->nro_columnas);
        hilos.push_back(std::move(hilo));
    }
}

void OutOfCoreSAC::joinNHilos(std::list<std::thread>& hilos) {
    for (auto& hilo : hilos) {
        if (hilo.joinable())
            hilo.join();
    }
}

void OutOfCoreSAC::hacerOperacionesConNHilos() {
    std::list<std::thread> hilos;
    ThreadSafeQueue cola;
    std::list<std::shared_ptr<ResultadosParciales>> resultados;
    this->cargarNTareas(cola, resultados);
    this->crearNHilos(cola, hilos);
    this->cargarTareasRestantes(cola, resultados);
    generarYCargarNTokens(cola, this->cant_hilos);
    this->joinNHilos(hilos);
    juntarResultadosParcialesYMostrar(resultados);
}

void OutOfCoreSAC::hacerOperaciones() {
    if (this->cant_hilos == 0) //solo el hilo main
        this->hacerOperacionEnHiloMain();
    else
        this->hacerOperacionesConNHilos();
}

OutOfCoreSAC::~OutOfCoreSAC() {
}
