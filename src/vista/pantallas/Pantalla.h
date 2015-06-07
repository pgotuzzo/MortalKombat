#ifndef MORTALKOMBAT_PANTALLA_H
#define MORTALKOMBAT_PANTALLA_H


#include "../../utils/GameUtils.h"
#include "../VistaUtils.h"

class Pantalla {
protected:
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    VistaUtils* mUtils;

    Tdimension mDimension;

public:
    Pantalla(Tdimension dimPixels, Tdimension dimUl);
    virtual void print() = 0;

    /**
     * PELEA
     */
    virtual void update(vector<Tcambio> changes,Tinput input);

    /**
     * MENU DE SELECCION DE MODOS DE JUEGO
     */
    virtual void update(EmodeSelection selection);

    /**
     * MENU DE SELECCION DE PERSONAJES
     * TODO - Mas de lo mismo
     */


    virtual ~Pantalla();
};


#endif //MORTALKOMBAT_PANTALLA_H
