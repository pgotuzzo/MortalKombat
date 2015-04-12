#include <SDL2/SDL_image.h>
#include <iostream>
#include "Capa.h"

float Capa::distTope = 0;
float Capa::mAnchoPersonaje = 0;
float Capa::mAnchoPantalla = 0;
float Capa::mAnchoEscenario = 0;
float Capa::posEscenario = 0;


/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*/
Capa::Capa(SDL_Renderer *renderer, std::string dirPath, VistaUtils::Trect rectPantalla) {
    mRenderer = renderer;
    mTexture = VistaUtils::loadTexture(mRenderer, dirPath, VistaUtils::COLORKEY::BLANCO);
    mRect = rectPantalla;
}

/*
*  Setea los valores de la capa y genera su textura.
*  anchoCapa : ancho total de la capa en unidades.
*  distTope : distancia limite en relacion al borde de la pantalla para que se empiecen
*  a mover las capas.
 */
void Capa::setValores(float anchoCapa, float altoCapa) {
    mRelacionCapa = (Capa::mAnchoEscenario - Capa::mAnchoPantalla)/(anchoCapa - Capa::mAnchoPantalla);
    SDL_Texture * t = VistaUtils::createTexture(mRenderer, anchoCapa, altoCapa);
    VistaUtils::copyTexture(mRenderer, mTexture, t);
    mTexture = t;
}

/*
*  Setea los valores de clase.
*  distanciaTope : distancia tope desde los bordes para que la capa se mueva.
*  anchoPersonaje : ancho del personaje.
*  anchoEscenario : ancho del escenario.
*  anchoPantalla : ancho de la pantalla.
 */
void Capa::setStatics(float distanciaTope, float anchoPersonaje, float anchoEscenario, float anchoPantalla) {
    Capa::mAnchoPantalla = anchoPantalla;
    Capa::distTope = distanciaTope;
    Capa::mAnchoPersonaje = anchoPersonaje;
    Capa::mAnchoEscenario = anchoEscenario;
    Capa::posEscenario = (anchoPantalla-anchoEscenario)/2;
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void Capa::getTexture(SDL_Texture *texture) {
    VistaUtils::copyTexture(mRenderer, mTexture, texture, &mRect, NULL);
}

/*
 * Cambia la posicion del escenario segun donde se encuentra el personaje.
 * posPersonajeX: posicion x del personaje.
 */
void Capa::cambiarEscenario(float posPersonajeX) {
    float topeDerecha = posEscenario + mAnchoPantalla - Capa::distTope;
    float topeIzquierda = posEscenario + Capa::distTope;
    if (topeIzquierda > posPersonajeX && posPersonajeX - Capa::distTope> 0) {
        posEscenario = posPersonajeX - Capa::distTope;
    } else if (posPersonajeX + mAnchoPersonaje > topeDerecha && posPersonajeX + mAnchoPersonaje + Capa::distTope < mAnchoEscenario) {
        posEscenario = posPersonajeX + mAnchoPersonaje + Capa::distTope - mAnchoPantalla;
    }
}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void Capa::ajustar() {
    mRect.p.x = posEscenario / mRelacionCapa;
}

/*
 * Devuelve la posicion de la pantalla en el escenario.
 */
float Capa::getPosPantalla() {
    return posEscenario;
}

Capa::Capa() {}

void Capa::freeTextures() {
    SDL_DestroyTexture(mTexture);
}

Capa::~Capa() {}
