#ifndef MORTALKOMBAT_CONTROLADORMOUSE_H
#define MORTALKOMBAT_CONTROLADORMOUSE_H

#include "SDL2/SDL_events.h"
#include "../Common.h"

class ControladorMouse {

public:
    Posicion posicionMouse;

    ControladorMouse();

    void moverMouse();

    bool dentroDeRectangulo(Trect rectangulo);






};


#endif //MORTALKOMBAT_CONTROLADORMOUSE_H
