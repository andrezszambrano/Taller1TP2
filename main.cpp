#include <iostream>
#include "OutOfCoreSAC.h"

#define ERROR 1
#define EXITO 0


int main(int argc, char* argv[]) {
    int nro_columnas = atoi(argv[2]);
    int nro_hilos = atoi(argv[3]);
    try{
        OutOfCoreSAC sac(argv[1], nro_columnas, nro_hilos);
        sac.hacerOperaciones();
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        return ERROR;
    } catch (...) {
        return ERROR;
    }
    return EXITO;
}
