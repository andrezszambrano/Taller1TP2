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

void OutOfCoreSAC::hacerOperacion() {
    Instrucciones instruc;
    recibirInstruccion(&instruc);
    int cant_particiones = this->controla_archivo.cargarParticiones(&instruc,
                                                           this->cant_hilos,
                                                           (this->particiones));
    this->ejecutarOperacionSobreParticiones(instruc.nro_columna,
                                           instruc.operacion, cant_particiones);
}



OutOfCoreSAC::~OutOfCoreSAC() {
    std::cout << "Hola Destructor de OOCSAC!";
}
