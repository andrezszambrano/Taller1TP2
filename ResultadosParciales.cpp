#include "ResultadosParciales.h"
#include <iostream>
#include <string>

//-------------------CLASE RESULTADOS PARCIALES-------------------------------//

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
    else
        throw std::runtime_error("Error: no existe un objeto que maneje "
                                 "la operación pedida. Las operaciones "
                                 "posibles son 'sum', 'mean', 'min' y 'max'");
}

void ResultadosParciales::guardarResultado(int resultado, int cant_filas) {
    const std::lock_guard<std::mutex> lock(this->mutex);
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

//-------------------CLASE RESULTADOS PARCIALES-------------------------------//

//-------------------CLASE RESULTADOS PARCIALES SUMA--------------------------//

void ResultadosParcialesSuma::guardarResultado(int resultado, int cant_filas) {
    ResultadosParciales::guardarResultado(resultado, cant_filas);
}

void ResultadosParcialesSuma::terminarOperacion() {
    ResultadosParciales::terminarOperacion();
}

void ResultadosParcialesSuma::imprimirResultado() {
    ResultadosParciales::imprimirResultado();
}

//-------------------CLASE RESULTADOS PARCIALES SUMA--------------------------//

//-------------------CLASE RESULTADOS PARCIALES MIN--------------------------//


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

//-------------------CLASE RESULTADOS PARCIALES MIN--------------------------//

//-------------------CLASE RESULTADOS PARCIALES MAX--------------------------//


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

//-------------------CLASE RESULTADOS PARCIALES MAX--------------------------//

//-------------------CLASE RESULTADOS PARCIALES MEAN--------------------------//


ResultadosParcialesMean::ResultadosParcialesMean()
                        :nro_filas(0){
}

void ResultadosParcialesMean::guardarResultado(int resultado, int cant_filas) {
    ResultadosParciales::guardarResultado(resultado, cant_filas);
    const std::lock_guard<std::mutex> lock(this->mutex);
    this->nro_filas = this->nro_filas + cant_filas;
}

void ResultadosParcialesMean::terminarOperacion() {
    ResultadosParciales::terminarOperacion();
}

void ResultadosParcialesMean::imprimirResultado() {
    std::cout << resultado_final << "/" << this->nro_filas  << std::endl;
}

//-------------------CLASE RESULTADOS PARCIALES MEAN--------------------------//

