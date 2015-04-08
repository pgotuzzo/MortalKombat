#include <SDL2/SDL_image.h>
#include <iostream>
#include "Capa.h"
#include "VistaUtils.h"

float Capa::distTope = 0;

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*/
Capa::Capa(SDL_Renderer *renderer, std::string dirPath, SDL_Rect rectPantalla) {
    mRenderer = renderer;
    mTexture = VistaUtils::loadTexture(mRenderer, dirPath, VistaUtils::COLORKEY::BLANCO);
//    mTexture = IMG_LoadTexture(mRenderer, dirPath.c_str());
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
void Capa::setValores(float anchoCapa, float altoCapa, float distanciaTope, float relacionCapa) {
    mAnchoCapa = anchoCapa;
    Capa::distTope = distanciaTope;
    mRelacionCapa = relacionCapa;
    SDL_Texture * t = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, mAnchoCapa, altoCapa);
    VistaUtils::copyTexture(mRenderer, mTexture, t);
    mTexture = t;
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void Capa::getTexture(SDL_Texture *texture) {
    VistaUtils::copyTexture(mRenderer, mTexture, texture, &mRect, NULL);
}

float Capa::getPosCapa(float posPersonajeX,float mRelacionCapa,float posCapa, float anchoPantalla,float  anchoCapa, float anchoPersonaje) {
    float topeDerecha = posCapa+anchoPantalla - Capa::distTope;
    float topeIzquierda = posCapa + Capa::distTope;
    float newPos = posCapa;
    if (topeIzquierda > posPersonajeX && posPersonajeX - Capa::distTope >= 0) {
        newPos = posCapa - ((posCapa - (posPersonajeX - Capa::distTope))/mRelacionCapa);
    } else if (posPersonajeX + anchoPersonaje > topeDerecha && posPersonajeX + Capa::distTope+anchoPersonaje <= anchoCapa) {
        float nuevaPosicionEscenario = posPersonajeX + anchoPersonaje + Capa::distTope - anchoPantalla;
        float deltaCrecimiento =  nuevaPosicionEscenario - posCapa;
        newPos = posCapa + deltaCrecimiento / mRelacionCapa;
    }
    return newPos;
}

/*
*  Cambia el trozo de pantalla que se va a mostrar.
*  posPersonaje : posicion actual del personaje
*/
void Capa::cambiar(Posicion posPersonaje, float anchoPersonaje) {
    posX = getPosCapa(posPersonaje.x, mRelacionCapa, posX, mRect.w, mAnchoCapa, anchoPersonaje);
    mRect.x = posX;
//    std::cout << "pos capa"<< posX << std::endl;
}

// TODO - HAY UN PROBLEMA DE REDONDEO QUE HACE QUE PARA CIERTOS VALORES LA CAPA NO SE MUEVA