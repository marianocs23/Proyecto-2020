
#ifndef AGREGACION_TIERRA_H
#define AGREGACION_TIERRA_H

#include <iostream>
#include <vector>
#include "Tipos.h"
#include "Objeto.h"

using namespace std;

// Valores constantes
const TipoEntero ALTURA = 21;
const TipoEntero ANCHO  = 21;
const TipoCaracter COLOR ='.';

class Tierra {
protected:
    vector<vector<char>> plano;
    vector<Objeto*> objetos;
public:
    Tierra();
    Tierra(TipoEntero altura, TipoEntero ancho);
    virtual ~Tierra();
    void adicionarObjeto(Objeto* objeto);
    Objeto* removerObjeto(string& nombre);
    void imprimirObjetos();
    TipoEntero getAltura();
    TipoEntero getAncho();
    TipoEntero getCantidadObjectos();
    void dibujarTierra();
    void actualizarTierra();
    bool posicionrepetida(TipoEntero x, TipoEntero y);
    bool compararnombre(string nombre);
    Objeto* buscarrobot(TipoString nombre);
    bool colorRepetido(TipoCaracter color);
};

#endif //AGREGACION_TIERRA_H
