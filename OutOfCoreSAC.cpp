#include "OutOfCoreSAC.h"
#include "RecibeInstrucciones.h"
#include <iostream>


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


void OutOfCoreSAC::hacerOperacion() {
    Instrucciones instruc;
    recibirInstruccion(&instruc);
    this->controla_archivo.descartarPrimerasNFilas(instruc.fila_inicial);
    int filas_totales_a_cargar = instruc.fila_final - instruc.fila_inicial;
    int max_filas_a_cargar = this->cant_hilos*instruc.nro_filas_por_particion;
    int filas_cargadas = 0;
    bool iterar = true;
    while(iterar){
        std::list<Fila> filas;
        int aux = this->cargarFilasDisponibles(filas, filas_totales_a_cargar -
                                                filas_cargadas,
                                                max_filas_a_cargar) ;
        if (aux == ERROR || aux == 0)
            return ERROR; //Si se leyeron solo 0 filas es que se pidieron más
                            //filas de las que tiene el archivo
        filas_cargadas = aux + filas_cargadas;
        //armarParticiones();
        //ejecutarParticiones();
        if (filas_cargadas == filas_totales_a_cargar)
            iterar = false;
    }
}



OutOfCoreSAC::~OutOfCoreSAC() {
    std::cout << "Hola Destructor de OOCSAC!";
}
