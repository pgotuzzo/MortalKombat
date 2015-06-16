#include "CapaInfoPractice.h"

const int tamBuffer = 10;
const float porcAnchoBoton = 0.05;
const float porcAltoBoton = 0.05;
const float porcPosXBoton = 0.05;
const float porcPosYBoton = 0.05;
const Uint32 tiempoMax = 3000;

const float porcDistComboX = 0.05;
const float porcDistComboY = 18;
const Uint32 tiempoMaxCombo = 2500;


CapaInfoPractice::CapaInfoPractice(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]) {
    mUtils = utils;

    for(int i=0;i<=tamBuffer;i++) {
        Trect rect;
        rect.d.w = dimPantalla.w *porcAnchoBoton;
        rect.d.h = dimPantalla.w *porcAltoBoton;
        rect.p.x = dimPantalla.w *(porcPosXBoton+i*3*porcAnchoBoton/2);
        rect.p.y = dimPantalla.w *porcPosYBoton;
        rectBotones.push_back(rect);
    }

    float posXCombo = dimPantalla.w * porcDistComboX;
    float posYCombo = dimPantalla.w * porcDistComboY;

    //Combo
    combo1 = mUtils->createTextureFromText(FONT_PATH, "", FONT_SIZE);
    combo2 = mUtils->createTextureFromText(FONT_PATH, "", FONT_SIZE);
    rectCombo1.p.x = posXCombo;
    rectCombo1.p.y = posYCombo;
    rectCombo2.p.y = posYCombo;
    combo1Activo = false;
    combo2Activo = false;
}


/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void CapaInfoPractice::getTexture(Ttexture texture) {
    buffer.empty();
    for (int i=0;i<buffer.size() ;i++) {
        TeclaBuffer aux = buffer.front();
        mUtils->copyTexture(aux.textura, texture, NULL, &rectBotones.at(i));
        buffer.pop();
        buffer.push(aux);
    }

    // Combos
    if (combo1Activo) mUtils->copyTexture(combo1, texture, NULL, &rectCombo1);
    if (combo2Activo) mUtils->copyTexture(combo2, texture, NULL, &rectCombo2);

}

Ttexture crearTextDeInputAccion(TinputAccion input, VistaUtils* mUtils) {
    switch (input) {
        case TinputAccion::KEY_PINIA_ALTA: {
            return mUtils->createTextureFromText(FONT_PATH, "PH", FONT_SIZE);
        };
        case TinputAccion::KEY_PINIA_BAJA: {
            return mUtils->createTextureFromText(FONT_PATH, "PL", FONT_SIZE);
        };
        case TinputAccion::KEY_PATADA_ALTA: {
            return mUtils->createTextureFromText(FONT_PATH, "KH", FONT_SIZE);
        };
        case TinputAccion::KEY_PATADA_BAJA: {
            return mUtils->createTextureFromText(FONT_PATH, "KL", FONT_SIZE);
        };
        case TinputAccion::KEY_PROTECCION: {
            return mUtils->createTextureFromText(FONT_PATH, "BL", FONT_SIZE);
        };
        case TinputAccion::KEY_PODER: {
            return mUtils->createTextureFromText(FONT_PATH, "PW", FONT_SIZE);
        };
    }
}

Ttexture crearTextDeInputMovimiento(TinputMovimiento input, VistaUtils* mUtils) {
    switch (input) {
        case TinputMovimiento::KEY_ARRIBA: {
            return mUtils->createTextureFromText(FONT_PATH, "UP", FONT_SIZE);
        };
        case TinputMovimiento::KEY_ABAJO: {
            return mUtils->createTextureFromText(FONT_PATH, "DW", FONT_SIZE);
        };
        case TinputMovimiento::KEY_DERECHA: {
            return mUtils->createTextureFromText(FONT_PATH, "RG", FONT_SIZE);
        };
        case TinputMovimiento::KEY_IZQUIERDA: {
            return mUtils->createTextureFromText(FONT_PATH, "LF", FONT_SIZE);
        };
        case TinputMovimiento::KEY_ARRIBA_DERECHA: {
            return mUtils->createTextureFromText(FONT_PATH, "RG", FONT_SIZE);
        };
        case TinputMovimiento::KEY_ARRIBA_IZQUIERDA: {
            return mUtils->createTextureFromText(FONT_PATH, "LF", FONT_SIZE);
        };
    }
}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void CapaInfoPractice::update(Tinput input,TInfoExtra infoExtra) {

    if (!buffer.empty()) {
        if (SDL_GetTicks()-buffer.front().tiempoInicial >= tiempoMax || buffer.size() >= tamBuffer) {
            SDL_DestroyTexture(buffer.front().textura.t);
            buffer.pop();
        }
    }

    if (input.accion != TinputAccion::KEY_NADA) {
        TeclaBuffer tecla;
        tecla.tiempoInicial = SDL_GetTicks();
        tecla.textura = crearTextDeInputAccion(input.accion,mUtils);
        buffer.push(tecla);
        buffer.size();
    }

    if (!buffer.empty()) {
        if (SDL_GetTicks()-buffer.front().tiempoInicial >= tiempoMax || buffer.size() >= tamBuffer) {
            SDL_DestroyTexture(buffer.front().textura.t);
            buffer.pop();
        }
    }

    if (input.movimiento != TinputMovimiento::KEY_NADA) {
        TeclaBuffer tecla;
        tecla.tiempoInicial = SDL_GetTicks();
        tecla.textura = crearTextDeInputMovimiento(input.movimiento,mUtils);
        buffer.push(tecla);
    }

    if (infoExtra.hayCombo1) {
        mUtils->copyInTextureFromText(FONT_PATH, infoExtra.nombreCombo1, FONT_SIZE,&combo1);
        rectCombo1.d = combo1.d;
        tcombo1 = SDL_GetTicks();
        combo1Activo=true;
    }
    if (infoExtra.hayCombo2) {
        mUtils->copyInTextureFromText(FONT_PATH, infoExtra.nombreCombo2, FONT_SIZE,&combo2);
        rectCombo2.d = combo2.d;
        rectCombo2.p.x = anchoPantalla-rectCombo2.d.w-rectCombo1.p.x;
        tcombo2 = SDL_GetTicks();
        combo2Activo=true;
    }
    if (SDL_GetTicks()-tcombo1 >= tiempoMax && combo1Activo) {
        mUtils->copyInTextureFromText(FONT_PATH, "", FONT_SIZE,&combo1);
        rectCombo1.d.w = 0;
        combo1Activo=false;
    }
    if (SDL_GetTicks()-tcombo2 >= tiempoMax && combo2Activo) {
        mUtils->copyInTextureFromText(FONT_PATH, "", FONT_SIZE,&combo2);
        rectCombo2.d.w = 0;
        combo2Activo=false;
    }
}

void CapaInfoPractice::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    for (int i=0;i<buffer.size() ;i++) {
        SDL_DestroyTexture(buffer.front().textura.t);
        buffer.pop();
    }
    SDL_DestroyTexture(combo1.t);
    SDL_DestroyTexture(combo2.t);
}

CapaInfoPractice::~CapaInfoPractice() {}
