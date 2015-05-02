#ifndef _MORTALKOMBAT_PERSONAJE_H_
#define _MORTALKOMBAT_PERSONAJE_H_

#include <array>
#include <SDL2/SDL_render.h>
#include "Sprite.h"
#include "../../Common.h"
#include "../VistaUtils.h"

class PersonajeVista {

private:
    TestadoPersonaje mCurrentState;
    Tsentido mTarget;
    Tdireccion mDirection;

    VistaUtils* mUtils;
    SDL_Texture* mTexture;
    Trect mRect;
    std::array <Sprite, TestadoPersonajeCount> mSprites;

    void crearSprites(std::string path);

public:
    PersonajeVista();
    PersonajeVista(VistaUtils* utils, std::string spritesPath, Tdimension dimension, Tdireccion direction);

    void update(Tcambio);
    void getTexture(SDL_Texture* ventana, float x);

    void freeTextures();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
