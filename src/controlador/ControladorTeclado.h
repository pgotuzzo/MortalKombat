#ifndef MORTALKOMBAT_CONTROLADOR_H
#define MORTALKOMBAT_CONTROLADOR_H


#include <vector>
#include "../Common.h"

class ControladorTeclado {
private:
    Tinput esAnterior1(const Uint8 *state);
    Tinput esAnterior2(const Uint8 *state);
public:
    Tinput inputAnterior1;
    Tinput inputAnterior2;
    ControladorTeclado();
    Tinputs getInputs();
};


#endif //MORTALKOMBAT_CONTROLADOR_H
