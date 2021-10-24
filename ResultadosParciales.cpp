#include "ResultadosParciales.h"
#include <iostream>
#include <string>

void ResultadosParciales::crear(std::shared_ptr<ResultadosParciales>& ptr,
                                const std::string& op) {
    if (op == "sum")
        ptr = std::make_shared<ResultadosParcialesSuma>();
    else if (op == "min")
        ptr = std::make_shared<ResultadosParcialesMin>();
    else if (op == "max")
        ptr = std::make_shared<ResultadosParcialesMax>();
    else if (op == "mean")
        ptr = std::make_shared<ResultadosParcialesMean>();
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

void ResultadosParcialesMin::guardarResultado(int resultado, int cant_filas) {
    ResultadosParciales::guardarResultado(resultado, cant_filas);
}

void ResultadosParcialesMin::terminarOperacion() {
    std::list<int>::iterator it;
    int min = resultados.front();
    for (it = resultados.begin(); it != resultados.end(); ++it){
        int aux = *it;
        if (aux < min)
            min = aux;
    }
    this->resultado_final = min;
}

void ResultadosParcialesMin::imprimirResultado() {
    ResultadosParciales::imprimirResultado();
}

void ResultadosParcialesMax::guardarResultado(int resultado, int cant_filas) {
    ResultadosParciales::guardarResultado(resultado, cant_filas);
}

void ResultadosParcialesMax::terminarOperacion() {
    std::list<int>::iterator it;
    int max = resultados.front();
    for (it = resultados.begin(); it != resultados.end(); ++it){
        int aux = *it;
        if (aux > max)
            max = aux;
    }
    this->resultado_final = max;
}

void ResultadosParcialesMax::imprimirResultado() {
    ResultadosParciales::imprimirResultado();
}

ResultadosParcialesMean::ResultadosParcialesMean()
                        :nro_filas(0){
}

void ResultadosParcialesMean::guardarResultado(int resultado, int cant_filas) {
    this->nro_filas = this->nro_filas + cant_filas;
    ResultadosParciales::guardarResultado(resultado, cant_filas);
}

void ResultadosParcialesMean::terminarOperacion() {
    ResultadosParciales::terminarOperacion();
}

void ResultadosParcialesMean::imprimirResultado() {
    std::cout << resultado_final << "/" << this->nro_filas  << std::endl;
}
