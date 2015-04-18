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


    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    VistaUtils::Trect mRect;
    std::array <Sprite, TestadoPersonajeCount> mSprites;

    void crearSprites(std::string path);

public:
    PersonajeVista();
    PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, float ancho, float alto, Tdireccion direction);

    void update(TdatosPersonaje);
    void getTexture(SDL_Texture* ventana, float x);
    VistaUtils::Trect getRect();

    void freeTextures();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
