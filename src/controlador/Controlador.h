#ifndef MORTALKOMBAT_CONTROLADOR_H
#define MORTALKOMBAT_CONTROLADOR_H


#include <vector>
#include "../Common.h"

class Controlador {
private:
    Tinput esAnterior(const Uint8 *state);
public:
    Tinput inputAnterior;
    Controlador();
    Tinput getInputs();
};


#endif //MORTALKOMBAT_CONTROLADOR_H
