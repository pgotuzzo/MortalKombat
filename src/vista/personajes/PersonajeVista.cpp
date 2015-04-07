#include "PersonajeVista.h"

PersonajeVista::PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, int ancho, int alto, Tdireccion direction) {
    mRenderer = renderer;
    crearSprites(spritesPath);
    mRect.w = ancho;
    mRect.h = alto;
    mDirection = direction;
}

void PersonajeVista::crearSprites(std::string path) {
    mSprites = std::array<Sprite, TestadoPersonajeCount>();
    for (int s = 0; s < TestadoPersonajeCount; s++){

        TestadoPersonaje state = TestadoPersonaje(s);
        std::string spritesPath = path + "/" + TestadoPersonajeToString(state) + "/";

        mSprites[s] = Sprite(mRenderer, spritesPath, true);
    }
}

void PersonajeVista::update(Tcambio tcambio) {
    mRect.x = (int) tcambio.posicion.x;
    mRect.y = (int) tcambio.posicion.y;
    mCurrentState = tcambio.estado;
    mDirection = tcambio.direccion;
    mTarget = tcambio.sentido;
}

SDL_Texture* PersonajeVista::getTexture() {
    SDL_Texture* texture = SDL_CreateTexture(mRenderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_TARGET, mRect.w, mRect.h);
    bool flip = (mDirection != Tdireccion::DERECHA);
    if(mTarget == Tsentido::ADELANTE) {
        mSprites[mCurrentState].getNext(texture, flip);
    }else{
        mSprites[mCurrentState].getBefore(texture, flip);
    }
    return texture;
}

SDL_Rect PersonajeVista::getRect() {
    return mRect;
}

PersonajeVista::PersonajeVista() {}



