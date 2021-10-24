#ifndef TP2FINAL_RESULTADOSPARCIALES_H
#define TP2FINAL_RESULTADOSPARCIALES_H
#include <list>

class ListaResultadosParciales {
    //std::list<ResultadosParciales*> ptrs_resultados;

public:
    ListaResultadosParciales();
    //push_back();
    ~ListaResultadosParciales();
};

class ResultadosParciales {
    std::list<int> resultados;
public:
    void guardarResultado(int resultado, int cant_filas);
//public:


};

#endif //TP2FINAL_RESULTADOSPARCIALES_H
