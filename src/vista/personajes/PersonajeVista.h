#ifndef _MORTALKOMBAT_PERSONAJE_H_
#define _MORTALKOMBAT_PERSONAJE_H_

#include "../../Constants.h"
#include "Sprite.h"
#include <SDL2/SDL_render.h>
#include <array>

class PersonajeVista {

public:

    static const int STATE_COUNT = 2;

    enum State {
        fighting_stance,
        walking,
        //  TODO - Agregar los posibles estados, hay mas!
    };

    static std::string stateToString(State s);

private:
    State mCurrentState;
    SDL_Rect mRect;

    std::array <Sprite, STATE_COUNT> mSprites;

    SDL_Renderer* mRenderer;

    void crearSprites(std::string path);

public:
    PersonajeVista();
    PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, int ancho, int alto);

    Pos getPosition();
    void setPosition(Pos p);

    State getState();
    void setState(State state);

    SDL_Texture* getTexture();

    SDL_Rect getRect();
};


#endif //_MORTALKOMBAT_PERSONAJE_H_
