#ifndef _MORTALKOMBAT_PERSONAJE_H_
#define _MORTALKOMBAT_PERSONAJE_H_

#include "../../Constants.h"
#include "../Sprite.h"
#include <SDL2/SDL_render.h>
#include <array>

class Personaje {

public:

    static const int STATE_COUNT = 2;

    enum State {
        fighting_stance,
        walking,
        //  TODO - Agregar los posibles estados, hay mas!
    };

    static std::string stateToString(State s);

private:
    Pos mPosition;
    State mCurrentState;

    std::array <Sprite, STATE_COUNT> mSprites;

public:
    Personaje(std::array<Sprite, STATE_COUNT> sprites);

    Pos getPosition();
    void setPosition(Pos p);

    State getState();
    void setState(State state);

    SDL_Texture* getTexture();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
