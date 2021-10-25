#ifndef TP2FINAL_MANEJAPARTICIONES_H
#define TP2FINAL_MANEJAPARTICIONES_H
#include "ResultadosParciales.h"
#include <array>
#include <list>
#include <stdint.h>
#include <string>
#include <memory>
#include <functional>
#include <map>
#define MAX_COLUMNAS 10

class Fila {
private:
    std::array<uint16_t, MAX_COLUMNAS> nums_fila;
    int cant_columnas;

public:
    //Se reservan los recursos necesarios para la fila, inicializando sus
    //valores.
    Fila();

    //Se inicializan los valores iniciales acorde, y se cede la ownership del
    //vector de números del otraFila a la nueva fila, dejando al primero en un
    //estado inválido.
    Fila(Fila&& otraFila);

    //Devuelve el valor que contiene la fila en la columna dada.
    int getColumna(int nro_columna) const;

    //Añade el número pasado por parámetro, cambiando el estado de la fila
    //acorde.
    void aniadirNumero(uint16_t num);

    //Se destruye la fila liberando sus recursos.
    ~Fila();
};

class Particion {
private:
    std::list<Fila> filas;
    int cant_filas;

public:
    //Inicia una partición seteando sus valores acorde.
    Particion();

    //Se crea una partición recibiendo una lista de filas y la cantidad de filas
    //pasadas.
    Particion(std::list<Fila>&& filas, int cant_filas);

    //Se realiza la operación parcial pedida sobre las filas de la partición y
    //la columna requerida. El resultado se envía al objeto
    //resultados_parciales, que lo almacenará acorde.
    void operarFilas(std::shared_ptr<ResultadosParciales>&&
                        resultados_parciales, int nro_columna,
                        const std::string& op);

    //Se imposibilita la construcción por copia de una partición.
    Particion(const Particion& otroMF) = delete;

    //Se setean los valores acorde, dejando a la otraPartición es un estado
    //válido para ser destruido.
    Particion(Particion&& otraParticion);

    //Se liberan los recursos acorde.
    ~Particion();
};

class MapaDeFunciones {
private:
    std::map<std::string, std::function<int(std::list<Fila>&, int)>> map;

public:
    //Se crea el objeto inicializado.
    MapaDeFunciones();

    //Recibe una referencia a una lista de filas, una referencia a un string
    //con la operación que se quiere realizar, y el número de columna con la
    //cual se quiere.
    int operar(std::list<Fila>& filas, const std::string& op,
               int nro_columna);
    ~MapaDeFunciones();
};

class InfoParticion {
public:
    std::shared_ptr<ResultadosParciales> resultados_parciales;
    int nro_indice_inicial;
    int nro_indice_final;
    int nro_columna;
    std::string operacion;

    //Se crea un objeto inicializado al mínimo.
    InfoParticion();

    //Se crea un objeto, llenando todos sus campos acorde.
    InfoParticion(std::shared_ptr<ResultadosParciales> ptr, int fila_inicial,
                  int fila_final, int nro_columna, int nro_filas_por_particion,
                  const std::string& op);

    //Actualiza el objeto info convirtiendolo en un objeto token, o uno que no
    //tiene información acerca de ninguna instrucción, sino que señala el fin
    //de tareas.
    void static crearToken(InfoParticion& info);

    //Se usan los campos del otro para llenar a la nueva clase y se deja en
    //estado válido para ser destruido. Se crea entonces un nuevo objeto con los
    //campos del otro.
    InfoParticion(InfoParticion&& otro);

    //Devuelve true si es un objeto creado para avisar que ya no hay más por
    //leer. Por otro lado, si es un objeto de instrucciones común, se devuelve
    //false.
    bool finDeParticiones();

    //Se guardan los campos del otro objeto en el objeto de la izquierda de la
    //igualdad.
    InfoParticion& operator=(const InfoParticion& otro);

    //Se libera la memoria acorde.
    ~InfoParticion();
};

#endif //TP2FINAL_MANEJAPARTICIONES_H
