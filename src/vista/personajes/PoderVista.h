#ifndef MORTALKOMBAT_PODERVISTAA_H
#define MORTALKOMBAT_PODERVISTAA_H

#include <array>
#include "Sprite.h"
#include "../../utils/PersonajeUtils.h"

class PoderVista {
private:
    VistaUtils* mUtils;
    Trect mRect;
    TestadoPoder mState;
    Tdireccion mDirection;
    array<Sprite, 2> mSprites;

public:
    PoderVista(){};
    PoderVista(VistaUtils* vu, std::string path, float scales[2]);
    void initialize(VistaUtils* vu, std::string path, float scales[2]);

    void update(TcambioPoder cambio, Tdireccion direccion);
    void getTexture(Ttexture ventana, float x);

    void freeTextures();
};

#endif //_MORTALKOMBAT_PODERVISTAA_H_