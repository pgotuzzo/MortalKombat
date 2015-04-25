#include <SDL2/SDL_image.h>
#include <iostream>
#include "Capa.h"

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*  anchoCapa : ancho total de la capa en unidades.
*/
Capa::Capa(SDL_Renderer *renderer, std::string dirPath, VistaUtils::Trect rectPantalla,float anchoCapa,float anchoEscenario) {
    int wMax = 4000;
    mRenderer = renderer;
    mTexture = VistaUtils::createTexture(mRenderer, wMax, rectPantalla.h, dirPath);

    mRect = rectPantalla;
    float relacionDeDesp = (anchoCapa - mRect.w)/(anchoEscenario - mRect.w);
    mRect.w = wMax * rectPantalla.w / anchoCapa;
    mVelocidadCapa = wMax * relacionDeDesp / anchoCapa ;
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void Capa::getTexture(SDL_Texture *texture) {
    VistaUtils::copyTextureNoScale(mRenderer, mTexture, texture, &mRect, NULL);
}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void Capa::ajustar(float posEscenario) {
    mRect.p.x =  posEscenario * mVelocidadCapa;
}

Capa::Capa() {}

void Capa::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    SDL_DestroyTexture(mTexture);
    loguer->loguear("Elimina capa", Log::LOG_DEB);
}

Capa::~Capa() {}
