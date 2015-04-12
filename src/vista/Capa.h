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
    float mRelacionCapa;
    VistaUtils::Trect mRect;
    static float distTope;
    static float mAnchoPersonaje;
    static float mAnchoEscenario;
    static float posEscenario;
    static float mAnchoPantalla;

public:
    Capa();
    /*
    *  Crea una capa.
    *  renderer : renderer utilizado
    *  dirPath : direccion de la imagen de la capa
    *  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
    *  capa en relacion a su tamaño total de la imagen
    */
    Capa(SDL_Renderer *renderer, std::string dirPath, VistaUtils::Trect rectPantalla);

    /*
    *  Setea los valores de la capa y genera su textura.
    *  anchoCapa : ancho total de la capa en unidades
    *  distTope : distancia limite en relacion al borde de la pantalla para que se empiecen
    *  a mover las capas
     */
    void setValores(float anchoCapa, float altoCapa);


    /*
    *  Setea los valores de clase.
    *  distanciaTope : distancia tope desde los bordes para que la capa se mueva.
    *  anchoPersonaje : ancho del personaje.
    *  anchoEscenario : ancho del escenario.
    *  anchoPantalla : ancho de la pantalla.
     */
    static void setStatics(float distanciaTope, float anchoPersonaje, float anchoEscenario, float anchoPantalla);

    /*
    *  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
    *  texture : puntero a una textura del tamaño de la pantalla
    */
    void getTexture(SDL_Texture *texture);

    /*
     * Cambia la posicion del escenario segun donde se encuentra el personaje.
	 * posPersonajeX: posicion x del personaje.
	 */
	static void cambiarEscenario(float posPersonajeX);


    /*
     * Cambia la posicion de la capa ajustandola a la posicion del escenario
     */
    void ajustar();


    /*
     * Devuelve la posicion de la pantalla en el escenario.
     */
    static float getPosPantalla();
};


#endif //_MORTALKOMBAT_CAPA_H_
