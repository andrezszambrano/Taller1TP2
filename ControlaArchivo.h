#ifndef TP2FINAL_ARCHIVO_H
#define TP2FINAL_ARCHIVO_H

#include <fstream>
#include <list>
#include "ManejaParticiones.h"
#include "RecibeInstrucciones.h"

class Archivo {
private:
    FILE* ptr_archivo;

public:
    Archivo();

    Archivo(const Archivo& otro_archivo) = delete;

    //Archivo(Archivo&& otro_archivo);

    Archivo& operator=(const Archivo& otro_archivo);

    //Crea un archivo con su puntero al archivo dado por el path. En caso de que
    //el archivo no exista se imprime en stderr y se lanza una excepción.
    explicit Archivo(const char* path_al_archivo);

    //Se leen hasta cant_bytes del archivo, almacenandolos en el buffer. Se
    //retorna la cantidad de bytes leidos: si dicha cantidad es menor a
    //cant_bytes, se terminó el archivo.
    int leerNBytes(char* buf, int cant_bytes);

    //Setea el offset que tiene el puntero al archivo respecto al comienzo del
    //archivo.
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
    //run time excepción con mensaje.
    ControlaArchivo(const char* pathAlArchivo, int nro_columnas);

    //Carga la lista de filas recibidas por referencia según la información
    //recibida. Si hay algún error en el formato del dataset (filas incompletas
    //o números de un byte) se lanza una runtime exception con un mensaje.
    void cargarFilasSegunInfo(std::list<Fila>& filas,
                                              const InfoParticion& info);
    int getNroColumnas();
    //Se liberan los recursos acorde.
    ~ControlaArchivo();

private:
    //Carga una fila según el número de columnas requerido. Si en la primera
    //iteración se intenta leer el archivo y se cargan 0 bytes, significa que
    //el archivo ya terminó y se retorna 1. Si en alguna otra iteración se
    //cargan 0 bytes, el archivo terminó, sin embargo la fila no está cargada
    //correctamente, lo cual significa que el número dado de columnas no es
    //correcto para el dataset, por lo tanto se lanza una runtime exception con
    //mensaje explicativo. Si en vez de cargar 2 bytes para un número solo se
    // carga 1 byte, significa que terminó el archivo leyendo un número de solo
    // 1 byte, por lo que también se lanza una runtime exception con otro
    // mensaje. En caso de éxito se retorna 0.
    int cargarFila(Fila& fila);

    //Se cargan hasta cant_filas_a_cargar filas en la lista de filas recibida
    //por referencia. En caso de error en el dataset (filas incompletas o
    //números de un byte) se lanza una runtime exception con mensaje de error.
    void cargarHastaNFilas(std::list<Fila>& filas, int cant_filas_a_cargar);
};


#endif //TP2FINAL_ARCHIVO_H
