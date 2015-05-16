#ifndef _MORTALKOMBAT_PANTALLA_H_
#define _MORTALKOMBAT_PANTALLA_H_

#include <SDL2/SDL_render.h>
#include <vector>
#include "Capa.h"
#include "CapaInfo.h"
#include "personajes/PersonajeVista.h"

using namespace std;

class Pantalla {
private:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    VistaUtils* mUtils;
    vector<Capa> mCapas;
    vector<PersonajeVista> mPersonajes;
    int zIndex;
    Tdimension mDimension;
    CapaInfo capaInfo;

    float distTope;
    float mAnchoPersonaje;
    float mAnchoEscenario;
    float posEscenario;

    void InicializarSdl(Tdimension d);
    void InicializarPersonajes(vector<Tpersonaje> personajes);
    void InicializarCapas(vector<Tcapa> capas, string personajes[2]);

    bool vibroADerecha;
    int contador;

public:
    /*
     * Crea una pantalla.
     * capas : formato de cada capa.
     * ventana : formato de ventana.
     * escenario : formato del escenario.
     * personaje : formato del personaje.
     */
    Pantalla(vector<Tcapa> capas, Tventana ventana, Tescenario escenario, vector<Tpersonaje> personajes);

    /*
     * Dibuja todos los objetos en pantalla.
     */
    void dibujar();

    /*
     * Actualiza todos los objetos de pantalla.
     * change : contiene los cambios a realizar.
     */
    void update(vector<Tcambio> changes);

    virtual ~Pantalla();
};


#endif //_MORTALKOMBAT_PANTALLA_H_
