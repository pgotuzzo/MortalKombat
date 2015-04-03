#include <iostream>
#include <SDL2/SDL.h>
#include "vista/Pantalla.h"

using namespace std;

const string WALLPAPER_PATH = "/home/pablo/Projects/MortalKombat/resources/img/test_wallpaper.jpeg";
const string SPRITES_PATH_POSTA = "/home/pablo/Projects/MortalKombat/resources/sprites/zub_zero";
const string CAPA1 = "/home/pablo/Projects/MortalKombat/resources/capas/capa1.jpeg";
const string CAPA2 = "/home/pablo/Projects/MortalKombat/resources/capas/capa2.jpeg";

int main() {
    Pantalla::Dimensiones dimensiones;
    dimensiones.altoPantalla = 600;
    dimensiones.altoPx = 678;
    dimensiones.anchoEscenario = 1500;
    dimensiones.anchoPantalla = 800;
    dimensiones.anchoPx = 1024;
    dimensiones.distTope = 100;
    vector<string> dirPaths;
    vector<float> anchosCapas;
    dirPaths.push_back(CAPA1);
    dirPaths.push_back(CAPA2);
    anchosCapas.push_back(1000);
    anchosCapas.push_back(1500);
    Pantalla pantalla = Pantalla(dirPaths,anchosCapas,dimensiones,0);


    Pos p;
    p.x = 750;
    p.y = 400;
    PersonajeVista::State state = PersonajeVista::State::walking;
    for (int i = 0; i < 100; i++){
        cout << "Ciclo " << i << endl;

        if (p.x>0)
            p.x = p.x - 10;

        pantalla.update(p,state);
        pantalla.dibujar();
        SDL_Delay(100);
    }
    for (int i = 0; i < 200; i++){
        cout << "Ciclo " << i << endl;

        if (p.x<1500-50)
            p.x = p.x + 10;

        pantalla.update(p,state);
        pantalla.dibujar();
        SDL_Delay(50);
    }

    cout << "Termino." << endl;

    return 0;
}