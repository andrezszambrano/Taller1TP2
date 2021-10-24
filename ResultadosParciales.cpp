#include "ResultadosParciales.h"
#include <iostream>
ListaResultadosParciales::ListaResultadosParciales() {

}

ListaResultadosParciales::~ListaResultadosParciales() {

}


void ResultadosParciales::crear(std::shared_ptr<ResultadosParciales>& ptr,
                                std::string op) {
    if (op == "sum")
        ptr = std::make_shared<ResultadosParcialesSuma>();
}

void ResultadosParciales::guardarResultado(int resultado, int cant_filas) {
    this->resultados.push_back(resultado);
}

void ResultadosParciales::terminarOperacion() {
    std::list<int>::iterator it;
    int suma = 0;
    for (it = resultados.begin(); it != resultados.end(); ++it){
        suma = suma + *it;
    }
    this->resultado_final = suma;
}

void ResultadosParciales::imprimirResultado() {
    std::cout << resultado_final << std::endl;
}

void ResultadosParcialesSuma::guardarResultado(int resultado, int cant_filas) {
    ResultadosParciales::guardarResultado(resultado, cant_filas);
}

void ResultadosParcialesSuma::terminarOperacion() {
    ResultadosParciales::terminarOperacion();
}

void ResultadosParcialesSuma::imprimirResultado() {
    ResultadosParciales::imprimirResultado();
}
