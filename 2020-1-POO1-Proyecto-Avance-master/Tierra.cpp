
#include "Tierra.h"
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

Tierra::Tierra() {
    plano.resize(ALTURA);
    for (auto& item: plano)
        item.resize(ANCHO);
}

Tierra::Tierra(TipoEntero altura, TipoEntero ancho) {
    plano.resize(altura);
    for (auto& item: plano)
        item.resize(ancho);
}

Tierra::~Tierra() {}

void Tierra::adicionarObjeto(Objeto* objeto) {
    objetos.emplace_back(objeto);
}

Objeto* Tierra::removerObjeto(string& nombre) {
    // Buscando objeto
    if (objetos.size() == 0)
      return nullptr;

    auto iter = find_if(begin(objetos), end(objetos),
                        [&nombre](Objeto* obj){ return obj->getNombre() == nombre; });
    if (iter == end(objetos))
      return nullptr;
    // Eliminando objeto
    objetos.erase(iter);
    //-- si encuentra al objeto lo separa del vector, pero no mata al objeto, esto se hara en el menu.
    return *iter;
}

void Tierra::imprimirObjetos() {
    int i = 0;
    for (auto& item: objetos) {
        cout << "* * * * * * [" << i << "] ";
        cout << " Nombre = " << item->getNombre() << " "
             << item->mostrarPosicion()
             << " Color = " << item->getColor() << '\n';
        i++;
    }
}

void Tierra::actualizarTierra() {
    for (auto &row: plano)
        for (auto &cell: row)
            cell = COLOR;

    for (auto& item: objetos)
        plano[item->getPosY()][item->getPosX()]
                = item->getColor();
}

void Tierra::dibujarTierra() {
    cout << '\n';
    cout << setw(3) << ' ';
    for (auto j = 0; j < getAncho(); ++j)
        cout << setw(3) << j;
    cout << '\n';

    for (auto i = 0; i < getAltura(); ++i) {
        cout << setw(3) << i;
        for (auto j = 0; j < getAncho(); ++j) {
            cout << setw(3) << plano[i][j];
        }
        cout << '\n';
    }
}

TipoEntero Tierra::getAltura() {
    return plano.size();
}

TipoEntero Tierra::getAncho(){
    return plano[0].size();
}
bool Tierra::posicionrepetida(TipoEntero x, TipoEntero y){
    for (int i=0; i<objetos.size(); ++i){
        if(objetos[i]->getPosX()==x && objetos[i]->getPosY()==y){
            return true;
        }
    }
    return false;
}

bool Tierra :: colorRepetido(TipoCaracter color){
    for (int i=0; i<objetos.size(); ++i){
        if(objetos[i]->getColor() == color){
            return true;
        }
    }
    return false;
}

bool Tierra:: compararnombre(string nombre){
    for(int i = 0; i < objetos.size(); i++){
        if(objetos.at(i)->getNombre() == nombre){
            return true;
        }
    }
    return false;
}

Objeto* Tierra:: buscarrobot(TipoString nombre){
    Objeto* ubicar = nullptr;
    for(int i = 0 ;i<objetos.size(); ++i){
        if(objetos[i]->getNombre()==nombre){
            ubicar = objetos[i];
            break;
        }
    }
    if(ubicar){
        cout << "( "<<ubicar->getPosX() << ", " << ubicar->getPosY() << " )" << endl;

    }else{
        cout << "No se encontro el objeto: " << nombre << endl;
    }
    return ubicar;
}


