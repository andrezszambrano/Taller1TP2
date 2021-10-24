#include "ResultadosParciales.h"

ListaResultadosParciales::ListaResultadosParciales() {

}

ListaResultadosParciales::~ListaResultadosParciales() {

}

void ResultadosParciales::guardarResultado(int resultado, int cant_filas) {
    this->resultados.push_back(resultado);
}