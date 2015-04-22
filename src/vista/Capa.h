#ifndef _MORTALKOMBAT_CAPA_H_
#define _MORTALKOMBAT_CAPA_H_

#include <string>
#include <SDL2/SDL_render.h>
#include "../Common.h"
#include "VistaUtils.h"

/**
 * Observacion
 *  Todas las medidas que se tomen en esta clase, son unidades logicas.
 *  No son pixeles necesariamente.
 */
class Capa {
private:
    SDL_Renderer* mRenderer;
    SDL_Texture* mTexture;
    Tdimension mDimension;
    float mVelocidad;

public:

    Capa();

    /**
     *  Crea una capa.
     *  renderer : renderer utilizado
     *  dirPath : direccion de la imagen de la capa
     *  dimensiones : dimensiones de la capa
     *  velocidad: velocidad de dezplazamiento
     */
    Capa(SDL_Renderer* renderer, std::string dirPath, Tdimension dimensiones, float velocidad);

    /**
     * target:  Textura a donde se debe copiar la capa.
     * ancho:   anchura que debe tener la capa.
     * x:   valor en el eje x, donde inicia la capa.
     */
    void getTexture(SDL_Texture *target, float ancho, float x);

    void freeTextures();

    virtual ~Capa();

};


#endif //_MORTALKOMBAT_CAPA_H_
