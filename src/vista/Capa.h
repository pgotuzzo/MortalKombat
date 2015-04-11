#ifndef _MORTALKOMBAT_CAPA_H_
#define _MORTALKOMBAT_CAPA_H_

#include <string>
#include <SDL2/SDL_render.h>
#include "../Common.h"
#include "VistaUtils.h"

class Capa {
private:
    SDL_Renderer* mRenderer;
    SDL_Texture * mTexture;
    float posX, mAnchoCapa,mRelacionCapa;
    static float distTope;
    VistaUtils::Trect mRect;

public:
    Capa();
    Capa(SDL_Renderer *renderer, std::string dirPath, VistaUtils::Trect rectPantalla);
    void setValores(float anchoCapa, float altoCapa, float distanciaTope, float relacionCapa);
    void getTexture(SDL_Texture *texture);
    void cambiar(Posicion posPersonaje, float anchoPersonaje);
    static float getPosCapa(float posPersonajeX, float mRelacionCapa, float posCapa, float anchoPantalla, float  anchoCapa, float anchoPersonaje);
};


#endif //_MORTALKOMBAT_CAPA_H_
