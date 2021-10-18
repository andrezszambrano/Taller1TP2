#ifndef TUTORIAL_FILA_H
#define TUTORIAL_FILA_H

#include <array>


#define MAX_COLUMNAS 10

class Fila {

private:
    std::array<int, MAX_COLUMNAS> nums;

public:
    Fila();
    ~Fila();
};


#endif //TUTORIAL_FILA_H
