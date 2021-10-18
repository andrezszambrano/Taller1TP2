#ifndef TP2FINAL_OUTOFCORESAC_H
#define TP2FINAL_OUTOFCORESAC_H

#include "Archivo.h"
#include "ManejaFilas.h"
#include <list>

class OutOfCoreSAC {

private:
    Archivo archivo;
    std::list<ManejaFilas> filas;

public:
    OutOfCoreSAC(const char* pathAlArchivo, int nro_columnas);
    void hacerOperacion();
    ~OutOfCoreSAC();
};


#endif //TP2FINAL_OUTOFCORESAC_H
