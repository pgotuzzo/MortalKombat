#ifndef MORTALKOMBAT_CONTROLADOR_H
#define MORTALKOMBAT_CONTROLADOR_H


#include "../Common.h"

class Controlador {
public:

    const Uint8* keyWord;
    Controlador();
    Tinput getEvent();
};


#endif //MORTALKOMBAT_CONTROLADOR_H
