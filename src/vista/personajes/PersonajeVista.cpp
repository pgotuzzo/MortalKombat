#include "PersonajeVista.h"

PersonajeVista::PersonajeVista(SDL_Renderer* renderer, std::string spritesPath, float ancho, float alto, Tdireccion direction) {
    mRenderer = renderer;
    crearSprites(spritesPath);
    mRect.w = ancho;
    mRect.h = alto;
    mDirection = direction;
    mTexture = VistaUtils::createTexture(mRenderer, ancho, alto);
}

void PersonajeVista::crearSprites(std::string path) {
    mSprites = std::array<Sprite, TestadoPersonajeCount>();
    for (int s = 0; s < TestadoPersonajeCount; s++){

        TestadoPersonaje state = TestadoPersonaje(s);
        std::string spritesPath = path + "/" + TestadoPersonajeToString(state) + "/";

        switch (s){
            case AGACHADO:
            case SALTANDO_VERTICAL:{
                mSprites[s] = Sprite(mRenderer, spritesPath, false);
                break;
            };
            default:
                mSprites[s] = Sprite(mRenderer, spritesPath, true);
        }
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

void PersonajeVista::getTexture(SDL_Texture* ventana, float x) {
    VistaUtils::cleanTexture(mRenderer, mTexture);
    bool flip = (mDirection != Tdireccion::DERECHA);
    if(mTarget == Tsentido::ADELANTE) {
        mSprites[mCurrentState].getNext(mTexture, flip);
    }else{
        mSprites[mCurrentState].getBefore(mTexture, flip);
    }
    VistaUtils::Trect r = mRect;
    r.p.x = mRect.p.x - x;
    VistaUtils::copyTexture(mRenderer, mTexture, ventana, NULL, &r);
}

VistaUtils::Trect PersonajeVista::getRect() {
    return mRect;
}

PersonajeVista::PersonajeVista() {}


void PersonajeVista::freeTextures() {
    for (Sprite s : mSprites)
        s.freeTextures();
    SDL_DestroyTexture(mTexture);
}

PersonajeVista::~PersonajeVista() {}

