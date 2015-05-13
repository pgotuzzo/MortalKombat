#include <array>
#include "../../Common.h"
#include "Sprite.h"

#ifndef MORTALKOMBAT_PODERVISTAA_H
#define MORTALKOMBAT_PODERVISTAA_H

class PoderVista {
private:
    VistaUtils* mUtils;
    Trect mRect;
    TestadoPoder mState;
    Tdireccion mDirection;
    array<Sprite, 2> mSprites;
    float mScales[2];

public:
    PoderVista(){};
    PoderVista(VistaUtils* vu, std::string path, float scales[2]);
    void initialize(VistaUtils* vu, std::string path, float scales[2]);

    void update(TcambioPoder cambio, Tdireccion direccion);
    void getTexture(SDL_Texture* ventana, float x);

    void freeTextures();
};

#endif //_MORTALKOMBAT_PODERVISTAA_H_