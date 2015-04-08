#ifndef MORTALKOMBAT_CONTROLADOR_H
#define MORTALKOMBAT_CONTROLADOR_H


#include <vector>
#include "../Common.h"

class Controlador {
private:
    Tinput getKeyBoardInput(SDL_Keycode key);

public:
    Controlador();
    std::vector<Tinput> getInputs();
};


#endif //MORTALKOMBAT_CONTROLADOR_H
