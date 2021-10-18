#include <iostream>
#include "OutOfCoreSAC.h"

//#define MAX_LINEA 40

int main(int argc, char* argv[]) {
    int nro_columnas = atoi(argv[2]);
    OutOfCoreSAC sac(argv[1], nro_columnas);
    sac.hacerOperacion();

    return 0;
}
