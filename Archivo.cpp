#include "Archivo.h"
#include "Fila.h"
#include <iostream>

#include <stdint.h>
#include <arpa/inet.h>

#define DOS_BYTES 2
#define MAX_COLUMNAS 10

Archivo::Archivo(const char* path_al_archivo, int nro_columnas)
        :ptrArchivo(path_al_archivo, std::ios::binary),
         nro_columnas(nro_columnas) {
        if (!ptrArchivo.is_open()){
            std::cerr << "El archivo no se abrió correctamente";
        }
}

int Archivo::cargarParticiones(Instrucciones* instrucciones,
                                int nro_particiones,
                                std::list<ManejaFilas>& particiones) {
    bool  lectura_finalizada = false;
    int cant_particiones = 0;
    while (!lectura_finalizada){
        ManejaFilas particion_aux;
        for (int i = 0; i < instrucciones->nro_filas_por_particion; i++){
            Fila fila_aux;
            for (int j = 0; j < this->nro_columnas; j++){
                uint16_t numBE;
                this->ptrArchivo.read(reinterpret_cast<char*>(&numBE),
                                       sizeof(uint16_t));
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

    return 0;

}

Archivo::~Archivo() {
    ptrArchivo.close();
    std::cout << "Hola Destructor de archivo!";
}