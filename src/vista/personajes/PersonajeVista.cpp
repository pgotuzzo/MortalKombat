#include "PersonajeVista.h"

const std::string DEFAULT_SPRITE = "personaje" + SPRITES_FORMAT;

PersonajeVista::PersonajeVista(VistaUtils* utils, std::string spritesPath, Tdimension dimension, Tdireccion direction) {
    mUtils = utils;
    crearSprites(spritesPath);
    mDirection = direction;

    mDefaultTextureDimension = dimension;
    mDefaultTexture = mUtils->loadTexture(spritesPath + "/" + DEFAULT_SPRITE);

    mUtils->getScales(mDefaultTexture, &dimension, mScales);

    mPoder.initialize(mUtils, spritesPath, mScales);
}

void PersonajeVista::crearSprites(string path) {
    mSprites = std::array<Sprite, TestadoPersonajeCount>();
    for (int s = 0; s < TestadoPersonajeCount; s++){
        TestadoPersonaje state = TestadoPersonaje(s);
        string spritesPath = path + "/" + TestadoPersonajeToString(state) + "/";

        switch (state){
            case MOV_AGACHADO:
            case MOV_SALTANDO_VERTICAL:
            case ACC_PINIA_ALTA_AGACHADO:
            case ACC_PINIA_SALTO:
            case ACC_PATADA_SALTO_VERTICAL:
            case ACC_PATADA_SALTO:
            case ACC_PROTECCION:
            case ACC_PROTECCION_AGACHADO:
            case ACC_PODER:
            case REA_GOLPE_FUERTE:
            case REA_PATADA_BARRIDA:
            case REA_GOLPE_ALTO:{
                mSprites[s] = Sprite(mUtils, spritesPath, false);
                break;
            };
            case MOV_SALTANDO_OBLICUO:{
                mSprites[s] = Sprite(mUtils, spritesPath, true);
                mSprites[s].disable(0);
                break;
            }
            default:
                mSprites[s] = Sprite(mUtils, spritesPath, true);
        }
    }
}

void PersonajeVista::update(Tcambio tcambio) {
    mCurrentRect.p = tcambio.posicion;
    mCurrentRect.d = tcambio.dPJ;
    if (mCurrentState != tcambio.estado){
        mCurrentState = tcambio.estado;
        mSprites[mCurrentState].restart();
    }
    mDirection = tcambio.direccion;
    mTarget = tcambio.sentido;
};

void PersonajeVista::getTexture(SDL_Texture* ventana, float x) {
    SDL_Texture* texture;
    bool flip = (mDirection != Tdireccion::DERECHA);

    // El "sentido" del personaje es importante SOLO para las acciones de salto oblicuo o caminar
    switch (mCurrentState){
        case MOV_SALTANDO_OBLICUO:
        case MOV_CAMINANDO:{
            if(mTarget == Tsentido::ADELANTE){
                texture = mSprites[mCurrentState].getNext();
            }else{
                texture = mSprites[mCurrentState].getBefore();
            }
            break;
        };
        default:
            texture = mSprites[mCurrentState].getNext();
    }

    // Calculo la dimension de la textura comparandola con la textura por defecto
//    Tdimension d = mUtils->getDimension(mDefaultTexture, &mDefaultTextureDimension, texture);

    /**
     * mCurrentRect = Trect que maneja el modelo
     * r = Trect que tiene maneja la vista
     * Observaciones:
     *  - coincide el piso, de los dos rects, pero el x esta centrado.
     *  - r puede tener dimension, y ser mayor o menor en dimension que mCurrentRect,
     *      pero siempre va a estar el piso a la misma altura, y el x centrado
     *       _________________________
     *      |r                        |
     *      |                         |
     *      |     _______________     |
     *      |    |mCurrentRect   |    |
     *      |    |               |    |
     *      |    |               |    |
     *       -------------------------
     *
     */

//    Trect r;
//    r.d = d;
//    r.p.y = mCurrentRect.p.y + mCurrentRect.d.h - r.d.h;
//    r.p.x = mCurrentRect.p.x - x + mCurrentRect.d.w / 2.0F - r.d.w / 2.0F;

    Trect r;
    r.d = mUtils->getDimension(texture, mScales);
    r.p.y = mCurrentRect.p.y + mCurrentRect.d.h - r.d.h;
    r.p.x = mCurrentRect.p.x - x + mCurrentRect.d.w / 2.0F - r.d.w / 2.0F;

    mUtils->copyTexture(texture, ventana, NULL, &r, &r.d, NULL, flip);

    // Imprimo el poder
//    mPoder.getTexture(ventana, x);
}

void PersonajeVista::freeTextures() {
    loguer->loguear("Elimina personaje", Log::LOG_DEB);
    loguer->loguear("Comienza a eliminarse los sprites del personaje", Log::LOG_DEB);
    for (int i = 0; i < mSprites.size(); i++) {
        mSprites[i].freeTextures();
    }
    loguer->loguear("Finaliza la eliminacion de los sprites del personaje", Log::LOG_DEB);
    SDL_DestroyTexture(mDefaultTexture);
}