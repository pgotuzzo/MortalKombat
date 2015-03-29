#ifndef _MORTALKOMBAT_CAPA_H_
#define _MORTALKOMBAT_CAPA_H_

#include <string>
#include <SDL2/SDL_render.h>
#include "../Posicion.h"

class Capa {
private:
    SDL_Renderer* mRenderer;
    SDL_Texture * mTexture;
    float posX, mAnchoCapa,topeIzquierda,topeDerecha,mRelacionCapa;
    SDL_Rect mRect;

public:
    Capa(SDL_Renderer *renderer, std::string dirPath);
    void setValores(float anchoCapa, float distTope, float relacionCapa);
    void getTexture(SDL_Texture *texture);
    void cambiar(Posicion posPersonaje);
};


#endif //_MORTALKOMBAT_CAPA_H_
