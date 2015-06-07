#ifndef MORTALKOMBAT_CONTROLADORMOUSE_H
#define MORTALKOMBAT_CONTROLADORMOUSE_H

#include "SDL2/SDL_events.h"
#include "../utils/Common.h"

class ControladorMouse {

public:
    Posicion posicionMouse;

    ControladorMouse();

    TinputGame moverMouse(SDL_Event event);

    bool dentroDeRectangulo(Trect rectangulo);






};


#endif //MORTALKOMBAT_CONTROLADORMOUSE_H
