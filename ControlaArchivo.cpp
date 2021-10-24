#include "ControlaArchivo.h"
#include "ManejaParticiones.h"
#include <iostream>

#include <stdint.h>
#include <arpa/inet.h>
#include <cstdio>
#define ARCHIVO_INEXISTENTE -2
#define DOS_BYTES 2
#define UN_BYTE 1
#define CERO_BYTES 0
#define MAX_COLUMNAS 10
#define ERROR -1
#define EXITO 0
#define FIN_DEL_ARCHIVO 1
#define PARTICION_PARCIAL_VALIDA 2
#define PARTICION_INVALIDA 3
//--------------------CLASE ARCHIVO----------------------------------//
Archivo::Archivo(const char* path_al_archivo) {
    this->ptrArchivo = fopen(path_al_archivo, "rb");
    if (!ptrArchivo)
           throw std::runtime_error("El archivo no existe.");
}

int Archivo::leerNBytes(char* buf, int cant_bytes) {
    int leidos = fread(buf, 1, cant_bytes, this->ptrArchivo);
    return leidos;
}

int Archivo::setearOffset(int offset) {
    return std::fseek(this->ptrArchivo, offset, SEEK_SET);
}

Archivo::~Archivo() {
    fclose(this->ptrArchivo);
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
        if (aux == UN_BYTE){
            std::cerr << "Cada número debe estar compuesto por dos bytes."
                         "Revise su dataset.";
            return ERROR;
        } else if (aux == CERO_BYTES && i > 0){
            std::cerr << "La cantidad de números totales en el dataset no es"
                         "múltiplo de la cantidad de columnas pedidas.";
            return ERROR;
        } else if (aux == CERO_BYTES){
            return FIN_DEL_ARCHIVO;
        }
        uint16_t num = ntohs(numBE);
        fila.aniadirNumero(num);
    }
    return EXITO;
}
/*
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
*/
int ControlaArchivo::descartarPrimerasNFilas(int cant_filas_a_descartar) {
    std::list<Fila> filas_a_descartar;
    int aux = this->cargarHastaNFilas(filas_a_descartar,
                                      cant_filas_a_descartar);
    if (aux == ERROR){
        return ERROR;
    } else if (aux < cant_filas_a_descartar){
        std::cerr << "Se pidieron descartar más filas de las que hay en el"
                     "dataset. Revise las instrucciones que puso.";
        return ERROR;
    } else{
        return EXITO;
    }

    /*for (int i = 0; i < cant_filas_a_descartar; i++){
        for (int j = 0; j < this->nro_columnas; j++){
                char aux[2];
                this->archivo.leerNBytes(aux, DOS_BYTES*sizeof(uint8_t));
            }
        }*/
}

int ControlaArchivo::cargarFilasSegunInfo(std::list<Fila>& filas,
                                          InfoParticion& info) {
    int offset_inicial = info.nro_indice_inicial*this->nro_columnas*DOS_BYTES;
    this->archivo.setearOffset(offset_inicial);
    return cargarHastaNFilas(filas, info.nro_indice_final -
                                        info.nro_indice_inicial);
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

ControlaArchivo::~ControlaArchivo(){

}


//-----------------CLASE CONTROLA_ARCHIVO---------------------------//
