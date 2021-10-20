#include <iostream>
#include "OutOfCoreSAC.h"


//#define MAX_LINEA 40


int main(int argc, char* argv[]) {
    int nro_columnas = atoi(argv[2]);
    int nro_hilos = atoi(argv[3]);
    OutOfCoreSAC sac(argv[1], nro_columnas, nro_hilos);
    sac.hacerOperacion();

    return 0;
}
