#ifndef MORTALKOMBAT_PANTALLA_H
#define MORTALKOMBAT_PANTALLA_H


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
    virtual void update(vector<Tcambio> changes) = 0;

    virtual ~Pantalla();
};


#endif //MORTALKOMBAT_PANTALLA_H
