#include "ControlaArchivo.h"
#include "Fila.h"
#include <iostream>

#include <stdint.h>
#include <arpa/inet.h>

#define DOS_BYTES 2
#define MAX_COLUMNAS 10
#define ERROR -1
#define EXITO 0
#define FIN_DEL_ARCHIVO 1
#define PARTICION_PARCIAL_VALIDA 2
#define PARTICION_INVALIDA 3
//--------------------CLASE ARCHIVO----------------------------------//
Archivo::Archivo(const char* path_al_archivo)
        :ptrArchivo(path_al_archivo, std::ios::binary) {
        if (!ptrArchivo.is_open()){
            std::cerr << "El archivo no se abrió correctamente";
        }
}

int Archivo::leerNBytes(char* buf, int cant_bytes) {
    this->ptrArchivo.read(buf, cant_bytes);
    int leidos;
    if (this->ptrArchivo.eof()){
        leidos = 0;
    } else {
        leidos = this->ptrArchivo.gcount();
    }
    return leidos;
}

Archivo::~Archivo() {
    ptrArchivo.close();
    std::cout << "Hola Destructor de archivo!";
}
//--------------------CLASE ARCHIVO----------------------------------//

//-----------------CLASE CONTROLA_ARCHIVO---------------------------//

ControlaArchivo::ControlaArchivo(const char* pathAlArchivo, int nro_columnas)
                :archivo(pathAlArchivo), nro_columnas(nro_columnas) {

}

int ControlaArchivo::cargarFila(Fila& fila) {
    for (int i = 0; i < this->nro_columnas; i++){
        uint16_t numBE;
        int aux = this->archivo.leerNBytes(reinterpret_cast<char*>
                                           (&numBE),
                                           sizeof(numBE));
        if (aux < 1 && i > 0){
            std::cerr << "La cantidad de números totales en el dataset no es"
                         "múltiplo de la cantidad de columnas pedidas.";
            return ERROR;
        } else if (aux < 1){
            return FIN_DEL_ARCHIVO;
        }
        uint16_t num = ntohs(numBE);
        fila.aniadirNumero(num);
    }
    return EXITO;
}

int ControlaArchivo::cargarParticion(ManejaFilas& particion,
                                      int nro_filas_por_particion) {
    for (int i = 0; i < nro_filas_por_particion; i++){
        Fila fila_aux;
        int aux = this->cargarFila(fila_aux);
        if (aux == ERROR)
            return ERROR;
        else if (aux == FIN_DEL_ARCHIVO && i == 0)
            return PARTICION_INVALIDA; //Particion no va a tener ninguna fila
        else if (aux == FIN_DEL_ARCHIVO)
            return PARTICION_PARCIAL_VALIDA; //Particion va a tener al menos
            //una fila
        particion.aniadirFila(std::move(fila_aux));
    }
    return EXITO;
}

void ControlaArchivo::descartarPrimerasNFilas(int cant_filas_a_descartar) {
        for (int i = 0; i < cant_filas_a_descartar; i++){
            for (int j = 0; j < this->nro_columnas; j++){
                char aux[2];
                this->archivo.leerNBytes(aux, DOS_BYTES*sizeof(uint8_t));
            }
        }
}

int ControlaArchivo::cargarHastaNFilas(std::list<Fila>& filas,
                                   int cant_filas_a_cargar) {
    int filas_cargadas = 0;
    while (filas_cargadas < cant_filas_a_cargar){
        Fila fila_aux;
        int aux = this->cargarFila(fila_aux);
        if (aux == ERROR)
            return ERROR;
        else if (aux == FIN_DEL_ARCHIVO)
            return filas_cargadas;
        filas.push_back(std::move(fila_aux));
        filas_cargadas++;
    }
    return filas_cargadas;
}
/*
int ControlaArchivo::cargarParticiones(Instrucciones* instrucciones,
                                        int nro_particiones,
                                        std::list<ManejaFilas>& particiones){
    this->descartarPrimerasNFilas(instrucciones->fila_inicial);
    int filas_por_cargar = instrucciones->fila_final -
                           instrucciones->fila_inicial;
    std::list<Fila> filas_aux;
    this->cargarNFilas(filas_aux, filas_por_cargar);
    bool  lectura_finalizada = false;
    int cant_particiones = 0;
    while (!lectura_finalizada){
        ManejaFilas particion_aux;
        int aux = this->cargarParticion(particion_aux,
                                        instrucciones->nro_filas_por_particion);
        if (aux == ERROR)
            return ERROR;
        if (aux == EXITO || aux == PARTICION_PARCIAL_VALIDA){
            particiones.push_back(std::move(particion_aux));
            cant_particiones++;
        }
        if (cant_particiones == nro_particiones ||
            aux == PARTICION_PARCIAL_VALIDA || aux == PARTICION_INVALIDA){
            lectura_finalizada = true;
        }
    }
    return cant_particiones;
}*/

ControlaArchivo::~ControlaArchivo(){

}



//-----------------CLASE CONTROLA_ARCHIVO---------------------------//
