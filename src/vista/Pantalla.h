#ifndef _MORTALKOMBAT_PANTALLA_H_
#define _MORTALKOMBAT_PANTALLA_H_

#include <SDL2/SDL_render.h>
#include <vector>
#include "Capa.h"
#include "personajes/PersonajeVista.h"

using namespace std;

class Pantalla {
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    vector<Capa> capas;
    PersonajeVista personaje;
    int zIndex;
    float altoPantalla,anchoPantalla;

    float distTope;
    float mAnchoPersonaje;
    float mAnchoEscenario;
    float posEscenario;

    /*
     * Se inicia la ventana y el renderer.
     */
    void Inicializar(int anchoPx,int altoPx);

public:
    /*
     * Crea una pantalla.
     * capas : formato de cada capa.
     * ventana : formato de ventana.
     * escenario : formato del escenario.
     * personaje : formato del personaje.
     */
    Pantalla(vector<Tcapa> capas, Tventana ventana, Tescenario escenario, Tpersonaje personaje);

    /*
     * Dibuja todos los objetos en pantalla.
     */
    void dibujar();

    /*
     * Actualiza todos los objetos de pantalla.
     * change : contiene los cambios a realizar.
     */
    void update(Tcambio change);

    virtual ~Pantalla();
};


#endif //_MORTALKOMBAT_PANTALLA_H_
