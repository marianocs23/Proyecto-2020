#include "Tierra.h"
#include "Objeto.h"


Objeto::Objeto(): color{}, posX{}, posY{}  {}

Objeto::Objeto(const TipoString& nombre, TipoCaracter color,
               TipoEntero posX, TipoEntero posY):
                                                 nombre{nombre}, color{color},
                                                 posX{posX}, posY{posY} {}

Objeto::~Objeto() {}

void Objeto::setNombre(const TipoString& nombre) { this->nombre = nombre; }

void Objeto::moverse(TipoEntero x, TipoEntero y) {
    this->posX=x;
    this->posY=y;

} //--  por implementar

TipoString   Objeto::getNombre() { return nombre; }
TipoEntero   Objeto::getPosX()   { return posX; }
TipoEntero   Objeto::getPosY()   { return posY; }
TipoCaracter Objeto::getColor()  { return color; }

TipoString Objeto::mostrarPosicion() {
    return "X = " + to_string(posX) + " Y = " + to_string(posY);
}

void Objeto :: nombreN(TipoString nombre){
    this->nombre = nombre;
}

void Objeto :: colorN(TipoCaracter color){
    this->color = color;
}


