#include <iostream>
#include "OutOfCoreSAC.h"
#include "ManejaParticiones.h"
//#define MAX_LINEA 40
#define ERROR 1
#define EXITO 0
#define ARCHIVO_INEXISTENTE -2
int main(int argc, char* argv[]) {
    int nro_columnas = atoi(argv[2]);
    int nro_hilos = atoi(argv[3]);
    /*std::list<Fila> filas;
    ControlaArchivo controla(argv[1], nro_columnas);
    controla.cargarHastaNFilas(filas, 2);
    MapaDeFunciones mapa;
    std::string s("sum");
    int aux = mapa.operar(filas, s, 2);
    std::cout<<aux;*/
    try{
        OutOfCoreSAC sac(argv[1], nro_columnas, nro_hilos);
        sac.hacerOperacion();
    } catch (const std::runtime_error& error){
        std::cerr << error.what() << std::endl;
        return ERROR;
    } catch (...){
        return ERROR;
    }
    return EXITO;
}
