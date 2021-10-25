#include "ManejaParticiones.h"
#include <utility>
#include <algorithm>
#include <numeric>
#define EXITO 0

//--------------------CLASE FILA----------------------------------//
Fila::Fila(): cant_columnas(0) {
}

Fila::Fila(Fila&& otraFila)
        :nums_fila(std::move(otraFila.nums_fila)),
         cant_columnas(otraFila.cant_columnas) {
}

void Fila::aniadirNumero(uint16_t num) {
    this->nums_fila[this->cant_columnas] = num;
    this->cant_columnas++;
}

int Fila::getColumna(int nro_columna) const{
    return this->nums_fila[nro_columna];
}

Fila::~Fila() {
}

//--------------------CLASE FILA----------------------------------//

//--------------------CLASE PARTICION----------------------------------//

Particion::Particion()
            :cant_filas(0) {
}

Particion::Particion(std::list<Fila>&& filas, int cant_filas)
        :filas(std::move(filas)), cant_filas(cant_filas){
}

Particion::Particion(Particion&& otraParticion)
        :filas(std::move(otraParticion.filas)),
         cant_filas(otraParticion.cant_filas) {
}

void Particion::operarFilas(std::shared_ptr<ResultadosParciales>&&
                            resultados_parciales, int nro_columna,
                            const std::string& op) {
    MapaDeFunciones mapa;
    int resultado = mapa.operar(this->filas, op, nro_columna);
    resultados_parciales->guardarResultado(resultado, this->cant_filas);
}

Particion::~Particion() {
}

//--------------------CLASE PARTICION----------------------------------//

//-------------------CLASE MAPA DE FUNCIONES----------------------------------//

int sum(const std::list<Fila>& filas, int nro_columna) {
    std::list<Fila>::const_iterator it;
    int suma = 0;
    for (it = filas.begin(); it != filas.end(); ++it){
        suma = suma + it->getColumna(nro_columna);
    }
    return suma;
}

int max(const std::list<Fila>& filas, int nro_columna) {
    std::list<Fila>::const_iterator it;
    int max = filas.front().getColumna(nro_columna);
    for (it = filas.begin(); it != filas.end(); ++it){
        int aux = it->getColumna(nro_columna);
        if (aux > max)
            max = aux;
    }
    return max;
}

int min(const std::list<Fila>& filas, int nro_columna) {
    std::list<Fila>::const_iterator it;
    int min = filas.front().getColumna(nro_columna);
    for (it = filas.begin(); it != filas.end(); ++it){
        int aux = it->getColumna(nro_columna);
        if (aux < min)
            min = aux;
    }
    return min;
}

MapaDeFunciones::MapaDeFunciones()
                :map({{"sum", sum}, {"max", max}, {"min", min},
                              {"mean", sum}}) {
}

int MapaDeFunciones::operar(std::list<Fila>& filas, const std::string& op,
                            int nro_columna) {
    return (this->map[op](filas, nro_columna));
}

MapaDeFunciones::~MapaDeFunciones() {
}

//-------------------CLASE MAPA DE FUNCIONES----------------------------------//

//-------------------CLASE INFO PARTICION----------------------------------//
InfoParticion::InfoParticion()
                :resultados_parciales(NULL), nro_indice_inicial(0),
                nro_indice_final(0), nro_columna(0) {
}

InfoParticion::InfoParticion(std::shared_ptr<ResultadosParciales> ptr,
                             int fila_inicial, int fila_final, int nro_columna,
                             int nro_filas_por_particion, const std::string& op)
              :resultados_parciales(ptr), nro_indice_inicial(fila_inicial),
               nro_columna(nro_columna), operacion(op){
    if (fila_final < fila_inicial + nro_filas_por_particion)
        this->nro_indice_final = fila_final;
    else
        this->nro_indice_final = fila_inicial + nro_filas_por_particion;
}

void InfoParticion::crearToken(InfoParticion& info) {
    info.nro_indice_inicial = 0;
    info.nro_indice_final = 0;
    info.nro_columna = 0;
}

InfoParticion::InfoParticion(InfoParticion&& otro) {
    this->resultados_parciales = otro.resultados_parciales;
    otro.resultados_parciales = NULL;
    this->nro_indice_inicial = otro.nro_indice_inicial;
    this->nro_indice_final = otro.nro_indice_final;
    this->nro_columna = otro.nro_columna;
    this->operacion = otro.operacion;
}

bool InfoParticion::finDeParticiones() {
    if (this->nro_indice_inicial == 0 && this->nro_indice_final == 0
        && this->nro_columna == 0)
        return true;
    return false;
}
InfoParticion& InfoParticion::operator=(const InfoParticion& otro) {
    if (this != &otro) {
        this->resultados_parciales = otro.resultados_parciales;
        this->nro_indice_inicial = otro.nro_indice_inicial;
        this->nro_indice_final = otro.nro_indice_final;
        this->nro_columna = otro.nro_columna;
        this->operacion = otro.operacion;
    }
    return *this;
}

InfoParticion::~InfoParticion() {
}

//-------------------CLASE INFO PARTICION----------------------------------//
