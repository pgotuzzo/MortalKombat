#ifndef _MORTALKOMBAT_CAPA_H_
#define _MORTALKOMBAT_CAPA_H_

#include <string>
#include <SDL2/SDL_render.h>
#include "../Common.h"
#include "VistaUtils.h"

class Capa {
private:
    VistaUtils* mUtils;
    Ttexture mTexture;
    float mVelocidadCapa;
    Trect mRect;

public:
    Capa();
    /*
    *  Crea una capa.
    *  renderer : renderer utilizado
    *  dirPath : direccion de la imagen de la capa
    *  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
    *  capa en relacion a su tamaño total de la imagen
    */
    Capa(VistaUtils* utils, std::string dirPath, Trect rectPantalla, float anchoCapa, float anchoEscenario);


    /*
    *  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
    *  texture : puntero a una textura del tamaño de la pantalla
    */
    void getTexture(Ttexture texture);


    /*
     * Cambia la posicion de la capa ajustandola a la posicion del escenario
     */
    void ajustar(float posEscenario);

    void freeTextures();

    virtual ~Capa();
};


#endif //_MORTALKOMBAT_CAPA_H_
