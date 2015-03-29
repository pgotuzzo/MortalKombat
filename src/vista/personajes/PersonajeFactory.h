#ifndef _MORTALKOMBAT_PERSONAJEFACTORY_H_
#define _MORTALKOMBAT_PERSONAJEFACTORY_H_


#include "../Sprite.h"
#include "Personaje.h"

using namespace std;

class PersonajeFactory {

private:
    static const int PERSONAJES_COUNT = 14;

    static array< array< Sprite, Personaje::STATE_COUNT >, PERSONAJES_COUNT> SPRITES;

    static void createSprites(SDL_Renderer* renderer);
public:

    enum TipoPersonaje{
        liu_kang,
        zub_zero,
        kung_lao,
        johnny_cage,
        reptile,
        shang_tsung,
        kitana,
        jax,
        mileena,
        baraka,
        scorpion,
        raiden,
        kintaro,
        shao_kahn
    };

    static std::string tipoPersonajeToString(TipoPersonaje t);

    static Personaje* getPersonaje(SDL_Renderer* renderer, TipoPersonaje t);

};

#endif //_MORTALKOMBAT_PERSONAJEFACTORY_H_
