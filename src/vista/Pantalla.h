#ifndef _MORTALKOMBAT_PANTALLA_H_
#define _MORTALKOMBAT_PANTALLA_H_

#include <SDL2/SDL_render.h>
#include <vector>
#include "Capa.h"
#include "personajes/PersonajeVista.h"

using namespace std;

class Pantalla {
public:
    struct Dimensiones {
        float anchoPantalla, altoPantalla, anchoEscenario, distTope;
        int anchoPx,altoPx;
    };

private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    vector<Capa> capas;
    Dimensiones mDimensiones;
    PersonajeVista personaje;
    int zIndex;
    float posPantalla;
    void Inicializar(Dimensiones dimensiones);

public:
    Pantalla(vector<string> dirPaths, vector<float> anchosCapas, Dimensiones dimensiones, int zInd);
    void dibujar();
    void update(Pos p, PersonajeVista::State state);
};


#endif //_MORTALKOMBAT_PANTALLA_H_
