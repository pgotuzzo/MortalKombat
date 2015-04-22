#include <SDL2/SDL_image.h>
#include <iostream>
#include "Capa.h"

Capa::Capa() {}

Capa::Capa(SDL_Renderer *renderer, std::string dirPath, Tdimension dimensiones, float velocidad){
    mRenderer = renderer;
    mDimension = dimensiones;
    mVelocidad = velocidad;
    mTexture = VistaUtils::loadTexture(mRenderer, dirPath, VistaUtils::BLANCO);
    if (mTexture != nullptr)
        loguer->loguear("Se carga textura de capa", Log::LOG_DEB);
    else {
        loguer->loguear("Error al cargar la textura de capa", Log::LOG_ERR);
        throw new exception();
    }
}

void Capa::getTexture(SDL_Texture *target, float ancho, float x) {
    int w;
    int h;
    SDL_QueryTexture(mTexture, NULL, NULL, &w, &h);
    VistaUtils::Trect rect;
    rect.w = ancho * ( w / mDimension.w ) ;
    rect.h = h;
    rect.p.x = ( mVelocidad * x ) * ( w / mDimension.w );
    rect.p.y = 0;
    VistaUtils::copyTexture2(mRenderer, mTexture, target, &rect, NULL);
}

void Capa::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    SDL_DestroyTexture(mTexture);
}

Capa::~Capa() {}


