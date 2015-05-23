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
    TestadoPersonaje mState;
    Tsentido mTarget;
    Tdireccion mDirection;
    Trect mRect; // Posicion y dimension que tiene el personaje en el modelo.
    PoderVista mPower = PoderVista();

    VistaUtils* mUtils;
    Ttexture mAuxTexture;
    array <Sprite, TestadoPersonajeCount> mSprites;

    void initializeSprites(float scales[2], string path);
    bool greatHit();

public:
    PersonajeVista(){};
    PersonajeVista(VistaUtils* utils, std::string spritesPath, Tdimension dimension, Tdireccion direction);

    Trect getRect();
    bool update(Tcambio);
    void getTexture(Ttexture ventana, float x);

    void freeTextures();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
