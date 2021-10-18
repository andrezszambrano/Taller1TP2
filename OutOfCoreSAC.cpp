#include "OutOfCoreSAC.h"
#include "RecibeInstrucciones.h"
#include <iostream>


OutOfCoreSAC::OutOfCoreSAC(const char* pathAlArchivo, int nro_columnas)
                :archivo(pathAlArchivo, nro_columnas) {
}

void OutOfCoreSAC::hacerOperacion() {
    Instrucciones instruc;
    recibirInstruccion(&instruc);

}

OutOfCoreSAC::~OutOfCoreSAC() {
    std::cout << "Hola Destructor de OOCSAC!";
}
