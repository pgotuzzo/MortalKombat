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

    VistaUtils::Trect mRect;
    std::array <Sprite, TestadoPersonajeCount> mSprites;
    SDL_Renderer* mRenderer;

    void crearSprites(std::string path);

public:
    PersonajeVista();
    PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, float ancho, float alto, Tdireccion direction);

    void update(Tcambio);
    SDL_Texture* getTexture();
    VistaUtils::Trect getRect();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
