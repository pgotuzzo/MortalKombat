#include "Personaje.h"

Personaje::Personaje(std::array<Sprite, STATE_COUNT> sprites) {
    mSprites = sprites;
}

Pos Personaje::getPosition() {
    return mPosition;
}

void Personaje::setPosition(Pos p) {
    mPosition = p;
}

Personaje::State Personaje::getState() {
    return mCurrentState;
}

void Personaje::setState(Personaje::State state) {
    mCurrentState = state;
}

// TODO - Implement
SDL_Texture* Personaje::getTexture() {
    return nullptr;
}


std::string Personaje::stateToString(Personaje::State s) {
    switch (s) {
        case fighting_stance: return "fighting_stance";
        case walking: return "walking";
    }
    return NULL;
}
