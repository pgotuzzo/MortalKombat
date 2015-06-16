#include "CapaInfoPractice.h"

const int tamBuffer = 10;
const float anchoBoton = 10;
const float altoBoton = 10;
const float posXBoton = 10;
const float posYBoton = 10;
const Uint32 tiempoMax = 3000;

CapaInfoPractice::CapaInfoPractice(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]) {
    mUtils = utils;

    for(int i=0;i<=tamBuffer;i++) {
        Trect rect;
        rect.d.w = anchoBoton;
        rect.d.h = altoBoton;
        rect.p.x = posXBoton+i*3*anchoBoton/2;
        rect.p.y = posYBoton;
        rectBotones.push_back(rect);
    }
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
}

void CapaInfoPractice::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    for (int i=0;i<buffer.size() ;i++) {
        SDL_DestroyTexture(buffer.front().textura.t);
        buffer.pop();
    }
}

CapaInfoPractice::~CapaInfoPractice() {}
