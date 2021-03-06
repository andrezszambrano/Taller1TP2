#ifndef TP2FINAL_RESULTADOSPARCIALES_H
#define TP2FINAL_RESULTADOSPARCIALES_H
#include <list>
#include <memory>
#include <string>
#include <mutex>

class ResultadosParciales {
protected:
    std::list<int> resultados;
    int resultado_final;
    std::mutex mutex;

public:
    //Crea un shared_pointer que apunta al heap a un objeto que pertenece a una
    //clase descendiente de ResultadosParciales, según sea el string pasado por
    //parámetro. Si la pasada operación pasada como string es incorrecta (es
    //distinta a 'sum', 'mean', 'min' y 'max'), se lanza una runtime exception
    //con un mensaje descriptivo.
    static void crear(std::shared_ptr<ResultadosParciales>& ptr,
                        const std::string& op);

    //Guarda los parámetros recibidos correspondientemente. Se usa un mutex
    //para asegurar un guardado óptimo en situaciones donde hay varios hilos
    //que pretenden guardar un resultado parcial.
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
