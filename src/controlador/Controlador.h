#ifndef MORTALKOMBAT_CONTROLADOR_H
#define MORTALKOMBAT_CONTROLADOR_H


#include <vector>
#include "../Common.h"

class Controlador {
private:
    TinputPersonaje esAnterior(const Uint8 *state);
public:
    TinputPersonaje inputAnterior;
    Controlador();
    TinputPersonaje getInputs();
};


#endif //MORTALKOMBAT_CONTROLADOR_H
