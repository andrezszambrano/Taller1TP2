#include "ControlaArchivo.h"
#include "Fila.h"
#include <iostream>

#include <stdint.h>
#include <arpa/inet.h>

#define DOS_BYTES 2
#define MAX_COLUMNAS 10
#define ERROR -1
#define EXITO 0

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
        if (aux < 1){
            std::cerr << "La cantidad de números totales en el dataset no es"
                         "múltiplo de la cantidad de columnas pedidas.";
            return ERROR;
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
        particion.aniadirFila(std::move(fila_aux));
    }
    return EXITO;
}

int ControlaArchivo::cargarParticiones(Instrucciones* instrucciones,
                                        int nro_particiones,
                                        std::list<ManejaFilas>& particiones){
    bool  lectura_finalizada = false;
    int cant_particiones = 0;
    while (!lectura_finalizada){
        ManejaFilas particion_aux;
        int aux = this->cargarParticion(particion_aux,
                                        instrucciones->nro_filas_por_particion);
        if (aux == ERROR)
            return ERROR;
        particiones.push_back(std::move(particion_aux));
        cant_particiones++;
        if (cant_particiones == nro_particiones){
            lectura_finalizada = true;
        }
    }
    return cant_particiones;
}

ControlaArchivo::~ControlaArchivo(){

}



//-----------------CLASE CONTROLA_ARCHIVO---------------------------//
