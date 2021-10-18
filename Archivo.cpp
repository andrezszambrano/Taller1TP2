#include "Archivo.h"
#include <iostream>
#include <fstream>

Archivo::Archivo(const char* pathAlArchivo, int nro_columnas)
        :ptrArchivo(pathAlArchivo, std::ios::binary),
         nro_columnas(nro_columnas) {
        if (!ptrArchivo.is_open()){
            std::cerr << "El archivo no se abrió correctamente";
        }
}

Archivo::~Archivo() {
    ptrArchivo.close();
    std::cout << "Hola Destructor de archivo!";
}