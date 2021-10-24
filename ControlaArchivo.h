#ifndef TP2FINAL_ARCHIVO_H
#define TP2FINAL_ARCHIVO_H

#include <fstream>
#include <list>
#include "ManejaParticiones.h"
#include "RecibeInstrucciones.h"

class Archivo {

private:
    FILE* ptrArchivo;

public:
    //Crea un archivo con su puntero al archivo dado por el path. En caso de que
    //el archivo no exista se imprime en stderr y se lanza una excepción.
    Archivo(const char* pathAlArchivo);

    //Se leen hasta cant_bytes del archivo, almacenandolos en el buffer. Se
    //retorna la cantidad de bytes leidos: si el archivo ya había tenía el flag
    //EOF se avisa por stderr y se retorna 0, o si al intentar leer se activa
    //dicho flag, se retorna 0, en otro caso se retorna la cantidad de bytes
    //leidos.
    int leerNBytes(char* buf, int cant_bytes);

    int setearOffset(int offset);

    //Se destruye el archivo liberando sus recursos acorde.
    ~Archivo();
};

class ControlaArchivo {

private:
    Archivo archivo;
    int nro_columnas;

public:
    //Crea un ControlaArchivo reservando todos sus recursos, recibiendo el path
    //al archivo que se quiere abrir y la cantidad de columnas que tiene cada
    //fila. En caso de que no se pueda abrir el archivo, se retorna una
    // excepción.
    ControlaArchivo(const char* pathAlArchivo, int nro_columnas);

    //Descarta las primeras N filas. Si el formato del dataset no es correcto
    //(tiene filas incompletas o números de un byte), o si el dataset no tiene
    //la cantidad de filas que se quieren descartar, se retorna -1 y se imprime
    //en stderr. en otro caso se retorna 0.
    int descartarPrimerasNFilas(int cant_filas_a_descartar);

    //Se cargan hasta cant_filas_a_cargar filas en la lista de filas recibida
    //por referencia. En caso de error en el dataset (filas incompletas o
    //números de un byte) se retorna error y se imprime en stderr. En otro caso
    //se retorna la cantidad de filas que se pudieron cargar, un número entre 0
    //y cant_filas_a_cargar.
    int cargarHastaNFilas(std::list<Fila>& filas, int cant_filas_a_cargar);

    int cargarFilasSegunInfo(std::list<Fila>& filas,
                                              InfoParticion& info);

    //Se liberan los recursos acorde.
    ~ControlaArchivo();

private:
    int cargarParticion(Particion& particion, int nro_filas_por_particion);

    //Carga una fila según el número de columnas requerido. Si en la primera
    //iteración se intenta leer el archivo y se cargan 0 bytes, significa que
    //el archivo ya terminó y se retorna 1. Si en alguna otra iteración se
    //cargan 0 bytes, el archivo terminó, sin embargo la fila no está cargada
    //correctamente, lo cual significa que el número dado de columnas no es
    //correcto para el dataset, por lo tanto se imprime en stderr y se retorna
    //-1. Si en vez de cargar 2 bytes para un número solo se carga 1 byte,
    //significa que terminó el archivo leyendo un número de solo 1 byte, por lo
    //que se imprime en stderr y se retorna -1. En caso de éxito se retorna 0.
    int cargarFila(Fila& fila);
};


#endif //TP2FINAL_ARCHIVO_H
