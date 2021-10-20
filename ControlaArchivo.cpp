#include "ControlaArchivo.h"
#include "Fila.h"
#include <iostream>

#include <stdint.h>
#include <arpa/inet.h>

#define DOS_BYTES 2
#define MAX_COLUMNAS 10


//--------------------CLASE ARCHIVO----------------------------------//
Archivo::Archivo(const char* path_al_archivo)
        :ptrArchivo(path_al_archivo, std::ios::binary) {
        if (!ptrArchivo.is_open()){
            std::cerr << "El archivo no se abrió correctamente";
        }
}

int Archivo::leerNBytes(char* buf, int cant_bytes) {
    this->ptrArchivo.read(buf, cant_bytes);
    return 0;
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

int ControlaArchivo::cargarParticiones(Instrucciones* instrucciones,
                                        int nro_particiones,
                                        std::list<ManejaFilas>& particiones){
    bool  lectura_finalizada = false;
    int cant_particiones = 0;
    while (!lectura_finalizada){
        ManejaFilas particion_aux;
        for (int i = 0; i < instrucciones->nro_filas_por_particion; i++){
            Fila fila_aux;
            for (int j = 0; j < this->nro_columnas; j++){
                uint16_t numBE;
                this->archivo.leerNBytes(reinterpret_cast<char*>(&numBE),
                                         sizeof(numBE));
                uint16_t num = ntohs(numBE);
                fila_aux.aniadirNumero(num);
            }
            particion_aux.aniadirFila(std::move(fila_aux));
        }
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
