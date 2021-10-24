#include "OutOfCoreSAC.h"
#include "RecibeInstrucciones.h"
#include <iostream>
#include "ThreadSafeQueue.h"
#define ERROR -1
#define EXITO 0
#define SIN_INSTRUCCIONES -1
OutOfCoreSAC::OutOfCoreSAC(const char* path_al_archivo, int nro_columnas,
                            int nro_hilos)
                            :controla_archivo(path_al_archivo, nro_columnas),
                            cant_hilos(nro_hilos) {

}

void OutOfCoreSAC::ejecutarOperacionSobreParticiones(int nro_columna,
                                                      std::string op,
                                                      int cant_particiones) {

}

int OutOfCoreSAC::cargarFilasDisponibles(std::list<Fila>& filas,
                                         int filas_restantes, int max_filas) {
    int filas_a_cargar;
    if (filas_restantes > max_filas)
       filas_a_cargar = max_filas;
    else
        filas_a_cargar = filas_restantes;
    return this->controla_archivo.cargarHastaNFilas(filas, filas_a_cargar);
}

void OutOfCoreSAC::cargarTodasLasTareas(ThreadSafeQueue& cola) {
    bool hay_tareas = true;
    while (hay_tareas) {
        Instrucciones instruc;
        int aux = recibirInstruccion(&instruc);
        if (aux == SIN_INSTRUCCIONES) {
            hay_tareas = false;
        } else {
           for (int fila_inicial = instruc.fila_inicial;
                fila_inicial < instruc.fila_final;
                fila_inicial = fila_inicial + instruc.nro_filas_por_particion) {
               InfoParticion info(fila_inicial, instruc.fila_final,
                          instruc.nro_columna, instruc.nro_filas_por_particion,
                          instruc.operacion);
               cola.push(std::move(info));
           }
        }
    }
}

int OutOfCoreSAC::hacerOperacionEnHiloMain() {
    //Como no se tendrán threads, cargo todas las particiones de una vez
    ThreadSafeQueue cola;
    this->cargarTodasLasTareas(cola);
    return EXITO;
}


int OutOfCoreSAC::hacerOperacion() {
    if (this->cant_hilos == 0) //solo el hilo main
        return this->hacerOperacionEnHiloMain();
    return 0;
}

/*
int OutOfCoreSAC::hacerOperacion() {
    Instrucciones instruc;
    recibirInstruccion(&instruc);
    {
        int aux = this->controla_archivo.descartarPrimerasNFilas(
                                                        instruc.fila_inicial);
        if (aux == ERROR)
            return ERROR;
    }
    bool iterar = true;
    while (iterar) {
        std::list<Fila> filas;
        int aux = this->controla_archivo.cargarHastaNFilas(filas,
                                               instruc.nro_filas_por_particion);
        if (aux == ERROR) {
            return ERROR;
        } else if (aux == 0) {
            iterar = false;
        } else {
            Particion particion;
            for (auto &&fila : filas)
                particion.aniadirFila(std::move(fila));

        }

    }

    int max_filas_a_cargar = this->cant_hilos*instruc.nro_filas_por_particion;
    int filas_cargadas = 0;
    bool iterar = true;
    while (iterar) {
        std::list <Fila> filas;
        int aux = this->cargarFilasDisponibles(filas, filas_totales_a_cargar -
                                                      filas_cargadas,
                                               max_filas_a_cargar);
        if (aux == ERROR || aux == 0)
            return ERROR; //Si se leyeron solo 0 filas es que se pidieron más
        //filas de las que tiene el archivo
        filas_cargadas = aux + filas_cargadas;
        std::list <Particion> particiones;
        aux = Particion::generarParticiones(particiones,
                                            instruc.nro_filas_por_particion,
                                            std::move(filas));
        //ejecutarParticiones();
        if (filas_cargadas == filas_totales_a_cargar)
            iterar = false;
    }
    return EXITO;
}*/



OutOfCoreSAC::~OutOfCoreSAC() {
    std::cout << "Hola Destructor de OOCSAC!";
}
