#ifndef _MORTALKOMBAT_PERSONAJE_H_
#define _MORTALKOMBAT_PERSONAJE_H_

#include <array>
#include <SDL2/SDL_render.h>
#include "Sprite.h"
#include "../../Common.h"
#include "../VistaUtils.h"
#include "PoderVista.h"

using namespace std;

class PersonajeVista {

private:
    /**
     * Atributos que tendrán correlación con el modelo
     *  a través de setters
     */
    TestadoPersonaje mCurrentState;
    Tsentido mTarget;
    Tdireccion mDirection;
    Trect mCurrentRect; // Posicion y dimension que tiene el personaje en el modelo.
    PoderVista mPoder = PoderVista();

    VistaUtils* mUtils;
    array <Sprite, TestadoPersonajeCount> mSprites;

    /**
     * Almaceno un imagen default del personaje (una imagen del personaje parado sin realizar ningun accion)
     *  y tambien guardo la dimension en unidades logicas que tiene dicha imagen.
     * Cuando quiera usar una imagen del personaje realizando una accion (saltar, pegar, etc). Voy a usar estos
     *  datos para poder calcular la dimension de la imagen en unidades logicas.
     */
    SDL_Texture* mDefaultTexture;
    Tdimension mDefaultTextureDimension;

    float mScales[2];

    void crearSprites(std::string path);

public:
    PersonajeVista(){};
    PersonajeVista(VistaUtils* utils, std::string spritesPath, Tdimension dimension, Tdireccion direction);

    void update(Tcambio);
    void getTexture(SDL_Texture* ventana, float x);

    void freeTextures();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
