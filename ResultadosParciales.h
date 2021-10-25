#ifndef TP2FINAL_RESULTADOSPARCIALES_H
#define TP2FINAL_RESULTADOSPARCIALES_H
#include <list>
#include <memory>
#include <string>

class ResultadosParciales {
protected:
    std::list<int> resultados;
    int resultado_final;

public:
    //Crea un shared_pointer que apunta al heap a un objeto que pertenece a una
    //clase descendiente de ResultadosParciales, según sea el string pasado por
    //parámetro.
    static void crear(std::shared_ptr<ResultadosParciales>& ptr,
                        const std::string& op);

    //Guarda el resultado parcial obtenido correspondientemente.
    virtual void guardarResultado(int resultado, int cant_filas);

    //Se juntan los resultados finales acorde a la operación que le corresponde.
    virtual void terminarOperacion();

    //Se imprime el resultado final acorde.
    virtual void imprimirResultado();
};

class ResultadosParcialesSuma: public ResultadosParciales {
public:
    virtual void guardarResultado(int resultado, int cant_filas) override;
    virtual void terminarOperacion() override;
    virtual void imprimirResultado() override;
};

class ResultadosParcialesMin: public ResultadosParciales {
public:
    virtual void guardarResultado(int resultado, int cant_filas) override;
    virtual void terminarOperacion() override;
    virtual void imprimirResultado() override;
};

class ResultadosParcialesMax: public ResultadosParciales {
public:
    virtual void guardarResultado(int resultado, int cant_filas) override;
    virtual void terminarOperacion() override;
    virtual void imprimirResultado() override;
};

class ResultadosParcialesMean: public ResultadosParciales {
private:
    int nro_filas;

public:
    ResultadosParcialesMean();
    virtual void guardarResultado(int resultado, int cant_filas) override;
    virtual void terminarOperacion() override;
    virtual void imprimirResultado() override;
};

#endif //TP2FINAL_RESULTADOSPARCIALES_H
