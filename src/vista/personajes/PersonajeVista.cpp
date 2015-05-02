#include "PersonajeVista.h"

PersonajeVista::PersonajeVista() {}

PersonajeVista::PersonajeVista(VistaUtils* utils, std::string spritesPath, Tdimension dimension, Tdireccion direction) {
    mUtils = utils;
    crearSprites(spritesPath);
    mRect.d = dimension;
    mDirection = direction;
    mTexture = mUtils->createTexture(mSprites[0].getDimension());
}

void PersonajeVista::crearSprites(std::string path) {
    mSprites = std::array<Sprite, TestadoPersonajeCount>();
    for (int s = 0; s < TestadoPersonajeCount; s++){
        TestadoPersonaje state = TestadoPersonaje(s);
        std::string spritesPath = path + "/" + TestadoPersonajeToString(state) + "/";

        switch (state){
            case AGACHADO:
            case SALTANDO_VERTICAL:{
                mSprites[s] = Sprite(mUtils, spritesPath, false);
                break;
            };
            default:
                mSprites[s] = Sprite(mUtils, spritesPath, true);
        }
    }
}

void PersonajeVista::update(Tcambio tcambio) {
    mRect.p = tcambio.posicion;
    if (mCurrentState != tcambio.estado){
        mCurrentState = tcambio.estado;
        mSprites[mCurrentState].restart();
    }
    mDirection = tcambio.direccion;
    mTarget = tcambio.sentido;
    mRect.d.h = tcambio.dPJ.h;
}

void PersonajeVista::getTexture(SDL_Texture* ventana, float x) {
    mUtils->cleanTexture(mTexture);
    bool flip = (mDirection != Tdireccion::DERECHA);

    // El "sentido" del personaje es importante SOLO para las acciones de salto oblicuo o caminar
    switch (mCurrentState){
        case SALTANDO_OBLICUO:
        case CAMINANDO:{
            if(mTarget == Tsentido::ADELANTE){
                mSprites[mCurrentState].getNext(mTexture, flip);
            }else{
                mSprites[mCurrentState].getBefore(mTexture, flip);
            }
            break;
        };
        default:
            mSprites[mCurrentState].getNext(mTexture, flip);
    }
    Trect r = mRect;
    r.p.x = mRect.p.x - x;
    mUtils->copyTexture(mTexture, ventana, NULL, &r, &mRect.d, NULL);
}

void PersonajeVista::freeTextures() {
    loguer->loguear("Elimina personaje", Log::LOG_DEB);
    loguer->loguear("Comienza a eliminarse los sprites del personaje", Log::LOG_DEB);
    for (int i = 0; i < mSprites.size(); i++) {
        mSprites[i].freeTextures();
    }
    loguer->loguear("Finaliza la eliminacion de los sprites del personaje", Log::LOG_DEB);
    SDL_DestroyTexture(mTexture);
}