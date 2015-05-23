#include "PoderVista.h"

PoderVista::PoderVista(VistaUtils* vu, std::string path, float scales[2]) {
    initialize(vu, path, scales);
}

void PoderVista::initialize(VistaUtils* vu, std::string path, float scales[2]) {
    mUtils = vu;

    mScales[0] = scales[0];
    mScales[1] = scales[1];

    mState = DESACTIVADO;

    mSprites = std::array<Sprite, 2>();
    mSprites[0].initialize(mUtils, path + "/" + PODER_ACTIVADO_PATH + "/", false);
    mSprites[1].initialize(mUtils, path + "/" + PODER_COLISION_PATH + "/", false);
}

void PoderVista::update(TcambioPoder cambio, Tdireccion direccion) {
    if ( (cambio.e == TestadoPoder::ACTIVADO) &&
         (mState == TestadoPoder::DESACTIVADO) ){
        mDirection = direccion;
        mSprites[0].restart();
        mSprites[1].restart();
    }
    mState = cambio.e;
    mRect.p = cambio.p;
    mRect.d = cambio.d;
}

void PoderVista::getTexture(SDL_Texture *ventana, float x) {
    if (mState != TestadoPoder::DESACTIVADO) {
        bool flip = (mDirection != Tdireccion::DERECHA);

        SDL_Texture* texture = (mState == ACTIVADO) ? mSprites[0].getNext() : mSprites[1].getNext();

        /**
         * mRect = Trect que maneja el modelo
         * r = Trect que tiene maneja la vista
         * Observaciones:
         *  - coincide el costado dependiendo de la direccion de los dos rects, pero el y esta centrado.
         *  - r puede tener dimension, y ser mayor o menor en dimension que mRect,
         *      pero siempre va a estar en un costado, y el "y" centrado
         *       _________________________
         *      |r                        |
         *      |          _______________|
         *      |         |mRect          |
         *      |         |               |
         *      |         |               |
         *      |          ---------------|
         *      |                         |
         *       -------------------------
         *
         */

        Trect r;
        r.d = mUtils->getDimension(texture, mScales);
        r.p.y = mRect.p.y + mRect.d.h / 2.0F - r.d.h / 2.0F;
        r.p.x = (mDirection == DERECHA) ?
                mRect.p.x - x + mRect.d.w - r.d.w :
                mRect.p.x - x;

        mUtils->copyTexture(texture, ventana, NULL, &r, &r.d, NULL, flip);
    }
}

void PoderVista::freeTextures() {
    for (int i = 0; i < mSprites.size(); i++){
        mSprites[i].freeTextures();
    }
}
