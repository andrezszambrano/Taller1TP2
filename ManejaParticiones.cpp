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

Fila::~Fila() {

}


Particion::Particion() {

}

Particion::Particion(std::list<Fila>&& filas)
        :filas(std::move(filas)) {

}

Particion::Particion(Particion&& otraParticion)
        :filas(std::move(otraParticion.filas)) {

}



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
}

void Particion::aniadirFila(Fila&& fila){
    this->filas.push_back(std::move(fila));
}
Particion::~Particion() {

}


InfoParticion::InfoParticion() {

}

InfoParticion::InfoParticion(int fila_inicial, int fila_final, int nro_columna,
              int nro_filas_por_particion, std::string op)
              :nro_indice_inicial(fila_inicial),
               nro_columna(nro_columna),
               operacion(op){
    if (fila_final < fila_inicial + nro_filas_por_particion)
        this->nro_indice_final = fila_final;
    else
        this->nro_indice_final = fila_inicial + nro_filas_por_particion;
}

InfoParticion::InfoParticion(InfoParticion&& otro) {
    this->nro_indice_inicial = otro.nro_indice_inicial;
    this->nro_indice_final = otro.nro_indice_final;
    this->nro_columna = otro.nro_columna;
    this->operacion = otro.operacion;
}

InfoParticion& InfoParticion::operator=(const InfoParticion& otro) {
    if (this != &otro) {
        this->nro_indice_inicial = otro.nro_indice_inicial;
        this->nro_indice_final = otro.nro_indice_final;
        this->nro_columna = otro.nro_columna;
        this->operacion = otro.operacion;
    }
    return *this;
}

InfoParticion::~InfoParticion() {

}