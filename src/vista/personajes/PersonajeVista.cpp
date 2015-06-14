#include "PersonajeVista.h"

const std::string DEFAULT_SPRITE = "personaje" + SPRITES_FORMAT;

PersonajeVista::PersonajeVista(VistaUtils* utils, std::string spritesPath, Tdimension dimension, Tdireccion direction) {
    mUtils = utils;
    mDirection = direction;

    float scales[2];

    mAuxTexture = mUtils->loadTexture(spritesPath + "/" + DEFAULT_SPRITE);
    mAuxTexture.d = dimension;
    mUtils->getScales(mAuxTexture, scales);

    mPower.initialize(mUtils, spritesPath, scales);
    initializeSprites(scales, spritesPath);
}

void PersonajeVista::initializeSprites(float scales[2], string path) {
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
            case REA_FAT_LEVANTA:
            case REA_FAT_FUEGO:
            case REA_FAT_ARCADE:
            case FAT_LEVANTA:
            case FAT_ARCADE:
            case REA_FAT_BRUTALITY_SUBZERO:
            case REA_GOLPE_ALTO:{
                mSprites[s] = Sprite(mUtils, spritesPath, scales, false);
                break;
            };
            case MOV_SALTANDO_OBLICUO:{
                mSprites[s] = Sprite(mUtils, spritesPath, scales, true);
                mSprites[s].disable(0);
                break;
            }
            default:
                mSprites[s] = Sprite(mUtils, spritesPath, scales, true);
        }
    }
}

bool PersonajeVista::greatHit() {
    return mState == REA_GOLPE_FUERTE;
}

Trect PersonajeVista::getRect() {
    return mRect;
}

/**
 * Actualiza el estado del personaje y devuelve un booleano en caso de
 *  necesitar que la pantalla vibre.
 *
 * @return  true --> vibrar
 */
bool PersonajeVista::update(Tcambio tcambio) {
    mRect.p = tcambio.posicion;
    mRect.d = tcambio.dPJ;
    if (mState != tcambio.estado){
        mState = tcambio.estado;
        mSprites[mState].restart();
    }
    mDirection = tcambio.direccion;
    mTarget = tcambio.sentido;

    mPower.update(tcambio.poder, mDirection);
    return greatHit();
};

void PersonajeVista::getTexture(Ttexture ventana, float x) {
    Ttexture texture;
    bool flip = (mDirection != Tdireccion::DERECHA);

    // El "sentido" del personaje es importante SOLO para las acciones de salto oblicuo o caminar
    switch (mState){
        case MOV_SALTANDO_OBLICUO:
        case MOV_CAMINANDO:{
            if(mTarget == Tsentido::ADELANTE){
                texture = mSprites[mState].getNext();
            }else{
                texture = mSprites[mState].getBefore();
            }
            break;
        };
        default:
            texture = mSprites[mState].getNext();
    }

    /**
     * mRect = Trect que maneja el modelo
     * r = Trect que tiene maneja la vista
     * Observaciones:
     *  - coincide el piso, de los dos rects, pero el x esta centrado.
     *  - r puede tener dimension, y ser mayor o menor en dimension que mRect,
     *      pero siempre va a estar el piso a la misma altura, y el x centrado
     *       _________________________
     *      |r                        |
     *      |                         |
     *      |     _______________     |
     *      |    |mRect          |    |
     *      |    |               |    |
     *      |    |               |    |
     *       -------------------------
     *
     */

    Trect r;
    r.d = texture.d;
    r.p.y = mRect.p.y + mRect.d.h - r.d.h;
    r.p.x = mRect.p.x - x + mRect.d.w / 2.0F - r.d.w / 2.0F;

    mUtils->copyTexture(texture, ventana, NULL, &r, flip);

    // Imprimo el poder
    mPower.getTexture(ventana, x);
}

void PersonajeVista::freeTextures() {
    loguer->loguear("Elimina personaje", Log::LOG_DEB);
    loguer->loguear("Comienza a eliminarse los sprites del personaje", Log::LOG_DEB);
    for (int i = 0; i < mSprites.size(); i++) {
        mSprites[i].freeTextures();
    }
    // TODO: FRAN ESTA LINEA TIRA SEGMENTATION FAULT AL ENTRAR A LA SELECCION DE PERSONAJES
    // TODO: FRAN ESTA LINEA TIRA SEGMENTATION FAULT AL ENTRAR A LA SELECCION DE PERSONAJES
    //SDL_DestroyTexture(mAuxTexture.t);
    loguer->loguear("Finaliza la eliminacion de los sprites del personaje", Log::LOG_DEB);
    mPower.freeTextures();
}

