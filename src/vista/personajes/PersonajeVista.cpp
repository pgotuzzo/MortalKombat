#include "PersonajeVista.h"

PersonajeVista::PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, int ancho, int alto) {
    mRenderer = renderer;
    crearSprites(spritesPath);
    mRect.w = ancho;
    mRect.h = alto;
}

std::string PersonajeVista::stateToString(PersonajeVista::State s) {
    switch (s) {
        case fighting_stance: return "fighting_stance";
        case walking: return "walking";
    }
    return NULL;
}

void PersonajeVista::crearSprites(std::string path) {
    mSprites = std::array<Sprite, PersonajeVista::STATE_COUNT>();
    for (int s = 0; s < PersonajeVista::STATE_COUNT; s++){

        PersonajeVista::State state = PersonajeVista::State(s);
        std::string spritesPath = path + "/" + PersonajeVista::stateToString(state) + "/";

        mSprites[s] = Sprite(mRenderer, spritesPath, true);
    }
}

Pos PersonajeVista::getPosition() {
    return Pos{mRect.x, mRect.y};
};

void PersonajeVista::setPosition(Pos p) {
    mRect.x = p.x;
    mRect.y = p.y;
}

PersonajeVista::State PersonajeVista::getState() {
    return mCurrentState;
}

void PersonajeVista::setState(PersonajeVista::State state) {
    mCurrentState = state;
}

// TODO - Falta implementar la logica
SDL_Texture* PersonajeVista::getTexture() {
    SDL_Texture* texture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, mRect.w, mRect.h);
    mSprites[mCurrentState].getNext(texture);
    return texture;
}

SDL_Rect PersonajeVista::getRect() {
    return mRect;
}

PersonajeVista::PersonajeVista() {}
