#ifndef MORTALKOMBAT_CONTROLADORTEXTO_H
#define MORTALKOMBAT_CONTROLADORTEXTO_H

#include "../utils/Common.h"
#include "SDL2/SDL_events.h"

using namespace std;

class ControladorTexto {

public:
    string caracter;

    Tletras generarCaracter(SDL_Event &e);

};


#endif //MORTALKOMBAT_CONTROLADORTEXTO_H
