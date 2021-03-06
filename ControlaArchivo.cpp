#include "ControlaArchivo.h"
#include "ManejaParticiones.h"
#include <iostream>
#include <utility>
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
    this->ptr_archivo = fopen(path_al_archivo, "rb");
    if (!ptr_archivo)
           throw std::runtime_error("Error: el archivo no existe.");
}

Archivo::Archivo(Archivo&& otro_archivo) {
    this->ptr_archivo = otro_archivo.ptr_archivo;
    otro_archivo.ptr_archivo = nullptr;
}

Archivo& Archivo::operator=(const Archivo& otro_archivo) { //CppLink se quejaba
    if (this != &otro_archivo) {                            //si no estaba
        this->ptr_archivo = otro_archivo.ptr_archivo;       //esta función
    }
    return *this;
}

int Archivo::leerNBytes(char* buf, int cant_bytes) {
    return fread(buf, 1, cant_bytes, this->ptr_archivo);
}

int Archivo::setearOffset(int offset) {
    return std::fseek(this->ptr_archivo, offset, SEEK_SET);
}

Archivo::~Archivo() {
    if (ptr_archivo)
        fclose(this->ptr_archivo);
}

//--------------------CLASE ARCHIVO----------------------------------//

//-----------------CLASE CONTROLA_ARCHIVO---------------------------//

ControlaArchivo::ControlaArchivo(const char* path_al_archivo, int nro_columnas)
                :archivo(path_al_archivo), nro_columnas(nro_columnas),
                 path_al_archivo(path_al_archivo) {
}

ControlaArchivo::ControlaArchivo(ControlaArchivo&& otroControlador)
                :archivo(std::move(otroControlador.archivo)),
                 nro_columnas(otroControlador.nro_columnas),
                 path_al_archivo(otroControlador.path_al_archivo) {
}

int ControlaArchivo::cargarFila(Fila& fila) {
    for (int i = 0; i < this->nro_columnas; i++){
        uint16_t numBE;
        int aux = this->archivo.leerNBytes(reinterpret_cast<char*>
                                           (&numBE),
                                           sizeof(numBE));
        if (aux == UN_BYTE)
            throw std::runtime_error("Error: cada número debe estar compuesto "
                                     "por dos bytes. Revise su dataset.");
        else if (aux == CERO_BYTES && i > 0)
            throw std::runtime_error("Error: La cantidad de números totales en "
                                     "el dataset no es múltiplo de la cantidad "
                                     "de columnas pedidas.");
        else if (aux == CERO_BYTES)
            return FIN_DEL_ARCHIVO;
        uint16_t num = ntohs(numBE);
        fila.aniadirNumero(num);
    }
    return EXITO;
}

void ControlaArchivo::cargarFilasSegunInfo(std::list<Fila>& filas,
                                          const InfoParticion& info) {
    int offset_inicial = info.nro_indice_inicial*this->nro_columnas*DOS_BYTES;
    this->archivo.setearOffset(offset_inicial);
    cargarHastaNFilas(filas, info.nro_indice_final -
                                        info.nro_indice_inicial);
}

void ControlaArchivo::cargarHastaNFilas(std::list<Fila>& filas,
                                   int cant_filas_a_cargar) {
    int filas_cargadas = 0;
    while (filas_cargadas < cant_filas_a_cargar){
        Fila fila_aux;
        int aux = this->cargarFila(fila_aux);
        if (aux == FIN_DEL_ARCHIVO)
            return;
        filas.push_back(std::move(fila_aux));
        filas_cargadas++;
    }
}

ControlaArchivo::~ControlaArchivo(){
}


//-----------------CLASE CONTROLA_ARCHIVO---------------------------//
