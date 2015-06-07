#ifndef MORTALKOMBAT_CAPAINFO_H
#define MORTALKOMBAT_CAPAINFO_H

#include <string>
#include <SDL2/SDL_render.h>
#include "../VistaUtils.h"
#include <queue>

using namespace std;

class CapaInfo {
protected:
public:
    CapaInfo();
    /*
    *  Crea una capa.
    *  renderer : renderer utilizado
    *  dirPath : direccion de la imagen de la capa
    *  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
    *  capa en relacion a su tamaño total de la imagen
    */
    CapaInfo(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]);


    /*
    *  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
    *  texture : puntero a una textura del tamaño de la pantalla
    */
    virtual void getTexture(Ttexture texture)=0;


    /*
     * Cambia la posicion de la capa ajustandola a la posicion del escenario
     */
    virtual void update(float porcVida1,float porcVida2,Tinput input);

    virtual void freeTextures();

    virtual ~CapaInfo();
};


#endif //MORTALKOMBAT_CAPAINFO_H
