#include "PersonajeVista.h"

PersonajeVista::PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, float ancho, float alto, Tdireccion direction) {
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

//        TODO - Agregar logica
        mSprites[s] = Sprite(mRenderer, spritesPath, true);
    }
}

void PersonajeVista::update(Tcambio tcambio) {
    mRect.p.x = tcambio.posicion.x;
    mRect.p.y = tcambio.posicion.y;
    mCurrentState = tcambio.estado;
    mDirection = tcambio.direccion;
    mTarget = tcambio.sentido;
    mRect.h = tcambio.alturaPJ;
}

SDL_Texture* PersonajeVista::getTexture() {
    SDL_Texture* texture = VistaUtils::createTexture(mRenderer, mRect.w, mRect.h);
    bool flip = (mDirection != Tdireccion::DERECHA);
    if(mTarget == Tsentido::ADELANTE) {
        mSprites[mCurrentState].getNext(texture, flip);
    }else{
        mSprites[mCurrentState].getBefore(texture, flip);
    }
    return texture;
}

VistaUtils::Trect PersonajeVista::getRect() {
    return mRect;
}

PersonajeVista::PersonajeVista() {}



