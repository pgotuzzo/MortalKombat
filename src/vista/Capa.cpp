#include <SDL2/SDL_image.h>
#include <iostream>
#include "Capa.h"

Capa::Capa() {}

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*  anchoCapa : ancho total de la capa en unidades.
*/
Capa::Capa(VistaUtils* utils, string dirPath, Trect rectPantalla, float anchoCapa, float anchoEscenario) {
    mUtils= utils;
    mRect = rectPantalla;

    mTexture = mUtils->loadTexture(dirPath);
    mTexture.d.w = anchoCapa;
    mTexture.d.h = mRect.d.h;

    mVelocidadCapa = (mTexture.d.w - rectPantalla.d.w)/(anchoEscenario - rectPantalla.d.w);
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void Capa::getTexture(Ttexture texture) {
    mUtils->copyTexture(mTexture, texture, &mRect, NULL);
}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void Capa::ajustar(float x) {
    mRect.p.x =  x * mVelocidadCapa;
}

void Capa::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    SDL_DestroyTexture(mTexture.t);
    loguer->loguear("Elimina capa", Log::LOG_DEB);
}

Capa::~Capa() {}
