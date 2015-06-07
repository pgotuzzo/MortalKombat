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
     * YOLO
     */
    virtual void initialize(vector<Tcapa> capas, string personajes[2]);

    /**
     * PELEA
     */
    virtual void update(vector<Tcambio> changes,Tinput input);

    /**
     * MENU DE SELECCION DE MODOS DE JUEGO
     */
    virtual void update(EmodeSelection selection);

    /**
     * GET CUADRADO DE LOS MODOS DE JUEGO
     */

    virtual vector<Trect> getCuadradoModos();

    /**
     * GET ESCALAS DE PIXELES A LOGICAS
     */

    virtual vector<float> getEscalas();

    /**
     * MENU DE SELECCION DE PERSONAJES
     */
    virtual void update(vector<EtipoPersonaje> players);

    virtual ~Pantalla();
};


#endif //MORTALKOMBAT_PANTALLA_H
