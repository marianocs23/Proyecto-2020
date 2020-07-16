
#include "tierra.h"
#include "Menu.h"
#include "Objeto.h"
#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

enum class Opciones { Agregar=1, Remover, Mostrar, Buscar, Mover, CambiarNombre, CambiarColor};


void limpiar() {
    cout << "\033[2J\033[0;0H";
}

void esperar() {
    char w;
    do {
         w = input<TipoCaracter>("Presione C y Enter para continuar...");
    }while (toupper(w) != 'C');
}

void Menu::imprimirMenu() {
    limpiar();
    cout << "MENU\n";
    cout << string(4, '-') << "\n\n";
    cout << "1. Agregar un nuevo objeto\n";
    cout << "2. Remover objeto\n";
    cout << "3. Dibujar Mapa\n";
    cout << "4. Buscar objeto\n";
    cout << "5. Mover objeto\n";
    cout << "6. Cambiar nombre\n";
    cout << "7. Cambiar color\n\n";
    cout << "0. Para Salir\n\n";
}

void Menu :: cambiarNombre(){
    TipoString nombre;
    Objeto* e;
    cout << "Ingresar nombre del objeto a cambiar: "; cin >> nombre;
    e=tierra.buscarrobot(nombre);
    if(e->getNombre()== nombre){
        cout << "Ingresa nombre nuevo: "; cin >> nombre;
        while(tierra.compararnombre(nombre)){
            cout << "El nombre " << nombre << " ya existe, ingresar otro:"; cin >>nombre;
        }
        e->nombreN(nombre);
        return;
    }else{
        cout << "No se encontro el objeto: " << nombre;
        return;
    }
}


void Menu::agregarObjeto(){
    string nombre;
    do{
       // auto  nombre = input<TipoString>("Ingrese Nombre : ");
        cout << "Ingrese nombre: "; cin >> nombre;
    }while(tierra.compararnombre(nombre));

    auto color  = input<TipoCaracter>("Ingrese color (Un caracter): ");
    //while(||color == '@')
    TipoEntero x,y;
    bool yala=true;

    do{
        x = input<TipoEntero>("Ingrese posicion X : ");
        y = input<TipoEntero>("Ingrese posicion Y : ");
        while (x < 0 || x >= tierra.getAncho()) {

            cout << "Posicion X Incorrecta, los limites son: 0, "
                 << tierra.getAncho() - 1 << "\n";
            x = input<TipoEntero>("Ingrese posicion X : ");
        }
        while (y < 0 || y >= tierra.getAncho()) {
            cout  << "Posicion Y Incorrecta, los limites son: 0, "
                  << tierra.getAltura() - 1 << "\n";
            y = input<TipoEntero>("Ingrese posicion Y : ");
        }
        yala = tierra.posicionrepetida(x,y);
    }while(yala);

    tierra.adicionarObjeto(new Objeto(nombre, color, x, y));
}

void Menu::agregarObstaculo(int cantidad){
    TipoCaracter color = '@';
    srand(time(NULL));
    for(int i=0; i<cantidad;++i) {
        const TipoString nombre = "Obstaculo" + std::to_string(i);

        auto x = rand() % tierra.getAncho();

        while (x < 0 || x >= tierra.getAncho()) {
            x = rand() % tierra.getAncho();
        }

        TipoEntero y = rand() % tierra.getAltura();

        while (y < 0 || y >= tierra.getAltura()) {

            y = rand() % tierra.getAltura();
        }
        tierra.adicionarObjeto(new Objeto(nombre, color, x, y));
    }
}

void Menu:: RobotBoss(){
    TipoCaracter color = '#';
    srand(time(NULL));
    TipoEntero x,y;
    do{
        x = rand() % tierra.getAncho();
    }while(x==20);
    do{
        y = rand() % tierra.getAltura();
    }while(y==20);

    const TipoString nombre = "RobotBoss";
    tierra.adicionarObjeto(new Objeto(nombre, color, x, y));
    tierra.adicionarObjeto(new Objeto(nombre, color, x+1, y));
    tierra.adicionarObjeto(new Objeto(nombre, color, x, y+1));
    tierra.adicionarObjeto(new Objeto(nombre, color, x+1, y+1));
    /*for(int i=0; i<2;++i) {
        const TipoString nombre = "Obstaculo" + std::to_string(i);

        auto x = rand() % tierra.getAncho();

        while (x < 0 || x >= tierra.getAncho()) {
            x = i;
        }

        TipoEntero y = rand() % tierra.getAltura();

        while (y < 0 || y >= tierra.getAltura()) {

            y = i;
        }
        tierra.adicionarObjeto(new Objeto(nombre, color, x, y));
    }*/


}


void Menu::removerObjeto() {
    auto nombre = input<TipoString>("Ingrese Nombre: ");

    Objeto* obj = tierra.removerObjeto(nombre);
    if (obj == nullptr) {
        cout << "Objeto No existe\n";
    }
    else {
        delete obj;
        cout << "Objeto: " << nombre << " ha sido removido\n";
    }
    esperar();
}
void Menu :: moverob(){
    TipoString nombre;
    TipoEntero posX, posY;
    cout << "Ingrese nombre:"; cin >> nombre;
    Objeto* A=tierra.buscarrobot(nombre);

    cout << endl << "Ingrese nueva coordenada X: "; cin >> posX;
    cout << endl << "Ingrese nueva coordenada Y: "; cin >> posY;

    if(A->getNombre()==nombre){
        while(tierra.posicionrepetida(posX, posY)){
            cout << "No se puede mover ahi" << endl;
            cout << "Ingresar posX: "; cin >> posX;
            cout << endl << "Ingresar posY:"; cin >> posY;
        }

        A->moverse(posX, posY);
    }else{
        cout << "No se encontro el objeto " << nombre << endl;
        return;
    }
}


void Menu::dibujarMapa() {
    limpiar();
    tierra.actualizarTierra();
    tierra.dibujarTierra();
    cout << '\n';
    tierra.imprimirObjetos();
    cout << '\n';
    esperar();
}

void Menu::ejecutar() {
    agregarObstaculo(10);
    RobotBoss();
    do {
        imprimirMenu();
        cin >> opcion;
        seleccionarOpcion();
    } while (opcion != 0);
    cout << "Fin del programa...\n";
}

void Menu:: CambiarColor() {
    TipoString nombre;
    TipoCaracter color;
    Objeto *e;

    cout << "Ingrese nombre del objeto a cambiar color:";
    cin >> nombre;
    e = tierra.buscarrobot(nombre);

    if (e->getNombre() == nombre) {
        cout << "Ingresa color nuevo: ";
        cin >> color;
        while (tierra.colorRepetido(color)) {
            cout << "El color" << color << " ya existe, ingresar otro:";
            cin >> color;
        }
        e->colorN(color);
        return;
    } else {
        cout << "No se encontro el objeto: " << nombre;
        return;
    }
}


    void Menu::seleccionarOpcion() {
        limpiar();
        switch (Opciones(opcion)) {
            case Opciones::Agregar:  // Agregar Objeto
                agregarObjeto();
                break;
            case Opciones::Remover:  // Remover Objeto
                removerObjeto();
                break;
            case Opciones::Mostrar: // Dibujando Tierra
                dibujarMapa();
                break;
            case Opciones::Mover:
                moverob();
                break;
            case Opciones::CambiarNombre:
                cambiarNombre();
                break;
            case Opciones::CambiarColor:
                CambiarColor();
                break;
            case Opciones::Buscar:
                TipoString cualquier;
                cout << "Ingresar nombre del objeto: ";
                cin >> cualquier;
                tierra.buscarrobot(cualquier);
                break;

        }
    }
