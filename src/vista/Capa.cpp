#include <SDL2/SDL_image.h>
#include "Capa.h"
#include "../Posicion.h"

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*/
Capa::Capa(SDL_Renderer *renderer, std::string dirPath, SDL_Rect rectPantalla) {
    mRenderer = renderer;
    mTexture = IMG_LoadTexture(mRenderer, dirPath.c_str());
    mRect = rectPantalla;
    posX = mRect.x;
}

/*
*  Setea los valores de la capa.
*  anchoCapa : ancho total de la capa en unidades
*  distTope : distancia limite en relacion al borde de la pantalla para que se empiecen
*  a mover las capas
*  relacionCapa : relacion de tamaño entre la capa con respecto al escenario
 */
void Capa::setValores(float anchoCapa, float distTope, float relacionCapa) {
    mAnchoCapa = anchoCapa;
    topeIzquierda = distTope;
    topeDerecha = mRect.w-distTope;
    mRelacionCapa = relacionCapa;
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void Capa::getTexture(SDL_Texture *texture) {
    SDL_Texture *originalTarget = SDL_GetRenderTarget(mRenderer);
    SDL_SetRenderTarget(mRenderer, texture);
    SDL_RenderCopy(mRenderer, mTexture, &mRect, NULL);
    SDL_SetRenderTarget(mRenderer, originalTarget);
}
/*
*  Cambia el trozo de pantalla que se va a mostrar.
*  posPersonaje : posicion actual del personaje
*/
void Capa::cambiar(Posicion posPersonaje) {
    if (topeIzquierda < posPersonaje.get_x() && posPersonaje.get_x() > 0) {
        posX = posX - ((posX - (posPersonaje.get_x() - topeIzquierda))/mRelacionCapa);
        mRect.x = posX;
    } else if (posPersonaje.get_x() < topeDerecha && posPersonaje.get_x() < mAnchoCapa) {
        posX = posX + (((posPersonaje.get_x() + topeIzquierda - mRect.w)- posX)/mRelacionCapa);
        mRect.x = posX;
    }
}
