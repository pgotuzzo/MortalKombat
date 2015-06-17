#ifndef MORTALKOMBAT_PANTALLAMENUPLAYERS_H
#define MORTALKOMBAT_PANTALLAMENUPLAYERS_H


#include <array>
#include "../Pantalla.h"
#include "../../personajes/PersonajeVista.h"

class PantallaMenuPlayers : public Pantalla {
private:
    Ttexture mTextBackground;
    Ttexture mTextSelector[2];
    PersonajeVista mPlayerViews[2];
    Ttexture mTextNames[2];

    Trect mRectSelector[2];
    Trect mRectName[2];

    EtipoPersonaje mPlayers[2];
    string mNames[2];
    bool activateSecondPlayer;

public:
    PantallaMenuPlayers(Tdimension dimPixels, Tdimension dimUl);

    void print();

    void update(array<Posicion, 2> players, array<string, 2> names);
    Posicion getRelativePosition(Posicion p);

    virtual ~PantallaMenuPlayers();
};


#endif //MORTALKOMBAT_PANTALLAMENUPLAYERS_H
