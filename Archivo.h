#ifndef TP2FINAL_ARCHIVO_H
#define TP2FINAL_ARCHIVO_H
#include <fstream>

class Archivo {

private:
    std::ifstream ptrArchivo;
    int nro_columnas;
public:
    Archivo(const char* pathAlArchivo, int nro_columnas);
    ~Archivo();
};




#endif //TP2FINAL_ARCHIVO_H
