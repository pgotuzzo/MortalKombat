#ifndef MORTALKOMBAT_CONTROLADOR_H
#define MORTALKOMBAT_CONTROLADOR_H


#include <vector>
#include "../Common.h"

class Controlador {
public:
    Tinput inputAnterior;
    Controlador();
    Tinput getInputs();
};


#endif //MORTALKOMBAT_CONTROLADOR_H
