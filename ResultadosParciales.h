#ifndef TP2FINAL_RESULTADOSPARCIALES_H
#define TP2FINAL_RESULTADOSPARCIALES_H
#include <list>
#include <memory>

class ListaResultadosParciales {
    //std::list<ResultadosParciales*> ptrs_resultados;

public:
    ListaResultadosParciales();
    //push_back();
    ~ListaResultadosParciales();
};

class ResultadosParciales {

protected:
    std::list<int> resultados;
    int resultado_final;

public:
    static void crear(std::shared_ptr<ResultadosParciales>& ptr,
                        std::string op);
    virtual void guardarResultado(int resultado, int cant_filas);
    virtual void terminarOperacion();
    virtual void imprimirResultado();

};

class ResultadosParcialesSuma: public ResultadosParciales {

public:
    virtual void guardarResultado(int resultado, int cant_filas);
    virtual void terminarOperacion();
    virtual void imprimirResultado();
};

class ResultadosParcialesMin: public ResultadosParciales {

public:
    virtual void guardarResultado(int resultado, int cant_filas);
    virtual void terminarOperacion();
    virtual void imprimirResultado();
};

class ResultadosParcialesMax: public ResultadosParciales {

public:
    virtual void guardarResultado(int resultado, int cant_filas);
    virtual void terminarOperacion();
    virtual void imprimirResultado();
};

class ResultadosParcialesMean: public ResultadosParciales {

private:
    int nro_filas;

public:
    ResultadosParcialesMean();
    virtual void guardarResultado(int resultado, int cant_filas);
    virtual void terminarOperacion();
    virtual void imprimirResultado();
};
#endif //TP2FINAL_RESULTADOSPARCIALES_H
