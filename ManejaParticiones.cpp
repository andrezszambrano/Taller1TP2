#include "ManejaParticiones.h"

#define EXITO 0

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


Particion::Particion() {

}

Particion::Particion(std::list<Fila>&& filas)
        :filas(std::move(filas)), cant_filas(filas.size()){

}

Particion::Particion(Particion&& otraParticion)
        :filas(std::move(otraParticion.filas)) {

}

void Particion::operarFilas(std::shared_ptr<ResultadosParciales>&&
                            resultados_parciales, int nro_columna,
                            std::string op) {
    MapaDeFunciones mapa;
    int resultado = mapa.operar(filas, op, nro_columna);
    resultados_parciales->guardarResultado(resultado, this->cant_filas);
}

/*
int Particion::generarParticiones(std::list<Particion>& particiones,
                                  int particiones_por_fila,
                                  std::list<Fila>&& filas) {
   std::list<Fila>::iterator it = filas.begin();
   while (it != filas.end()){
       Particion particion_aux;
       for (int i = 0; i < particiones_por_fila && it != filas.end(); i++){
           particion_aux.aniadirFila(std::move(*it));
           it++;
       }
       particiones.push_back(std::move(particion_aux));
   }
    return EXITO;
}*/

void Particion::aniadirFila(Fila&& fila){
    this->filas.push_back(std::move(fila));
}
Particion::~Particion() {

}

int sum(std::list<Fila>& filas, int nro_columna) {
    int suma = 0;
    for (auto const& fila : filas)
        suma = suma + fila.getColumna(nro_columna);
    return suma;
}

int max(std::list<Fila>& filas, int nro_columna) {
    int max = 0;
    for (auto const& fila : filas) {
        int aux = fila.getColumna(nro_columna);
        if (max < aux)
            max = aux;
    }
    return max;
}

int min(std::list<Fila>& filas, int nro_columna) {
    int min = 0;
    for (auto const& fila : filas) {
        int aux = fila.getColumna(nro_columna);
        if (min > aux)
            min = aux;
    }
    return min;
}

MapaDeFunciones::MapaDeFunciones()
                :map({{"sum", sum}, {"max", max}, {"min", min},
                              {"mean", sum}}) {

}

int MapaDeFunciones::operar(std::list<Fila>& filas, std::string op,
                            int nro_columna) {
    return (this->map[op](filas, nro_columna));
}

MapaDeFunciones::~MapaDeFunciones() {

}
InfoParticion::InfoParticion() {

}

InfoParticion::InfoParticion(std::shared_ptr<ResultadosParciales> ptr,
                             int fila_inicial, int fila_final, int nro_columna,
                             int nro_filas_por_particion, std::string op)
              :resultados_parciales(ptr), nro_indice_inicial(fila_inicial),
               nro_columna(nro_columna), operacion(op){
    if (fila_final < fila_inicial + nro_filas_por_particion)
        this->nro_indice_final = fila_final;
    else
        this->nro_indice_final = fila_inicial + nro_filas_por_particion;
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