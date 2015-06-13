#include "CapaInfo.h"
#include "CapaInfoArcade.h"
#include "SDL2/SDL.h"

const float porcBarraRelleno = (const float) (162.0/168.0);
const float porcTamBarraPantallaX = 0.35;
const float porcTamBarraPantallaY = 0.05;
const float porcDistBarraPantallaX = 0.05;
const float porcDistBarraPantallaY = 0.04;

const float posYCombo = 18;
const Uint32 tiempoMax = 2500;

const float ajusteYTimer = -2;
const float ajusteXTimer = -5;

const string dirPathVidaRoja = "resources/accesorios/barraVidaRoja.gif";
const string dirPathVidaVerde = "resources/accesorios/barraVidaVerde.gif";

const string FONT_PATH = "resources/font/mortalkombat2.ttf";
const int FONT_SIZE = 18;
const int FONT_SIZE_FOR_TIMER = 40;


CapaInfoArcade::CapaInfoArcade() {}

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*  anchoCapa : ancho total de la capa en unidades.
*/
CapaInfoArcade::CapaInfoArcade(VistaUtils* utils, Tdimension dimPantalla, string nombres[2],string timer) {
    mUtils = utils;

    // Barras de vida
    float anchoBarra = dimPantalla.w * porcTamBarraPantallaX;
    float altoBarra = dimPantalla.h * porcTamBarraPantallaY;

    barraVidaCompletaText = mUtils->loadTexture(dirPathVidaRoja);
    barraVidaCompletaText.d = Tdimension(anchoBarra, altoBarra);

    barraVidaParcialText = mUtils->loadTexture(dirPathVidaVerde);
    barraVidaParcialText.d = Tdimension(anchoBarra, altoBarra);

    barraVidaCompleta1.d = Tdimension(anchoBarra, altoBarra);
    barraVidaCompleta2.d = Tdimension(anchoBarra, altoBarra);

    float posX1 = dimPantalla.w * porcDistBarraPantallaX;
    float posX2 = dimPantalla.w - anchoBarra - posX1;
    float posY = dimPantalla.h * porcDistBarraPantallaY;
    barraVidaCompleta1.p = Posicion(posX1, posY);
    barraVidaCompleta2.p = Posicion(posX2, posY);

    barraVidaParcialPantalla1 = barraVidaCompleta1;
    barraVidaParcialPantalla2 = barraVidaCompleta2;

    barraVidaParcialPedazo1.p.x = 0;
    barraVidaParcialPedazo1.p.y = 0;
    barraVidaParcialPedazo1.d.w = anchoBarra;
    barraVidaParcialPedazo1.d.h = altoBarra;
    barraVidaParcialPedazo2 = barraVidaParcialPedazo1;

    anchoRelleno = anchoBarra * porcBarraRelleno;
    anchoBorde = (anchoBarra - anchoRelleno) / 2;

    anchoPantalla = dimPantalla.w;
    distBorde = posX1;

    // Nombres
    mNombre1 = mUtils->createTextureFromText(FONT_PATH, nombres[0], FONT_SIZE);
    mNombre2 = mUtils->createTextureFromText(FONT_PATH, nombres[1], FONT_SIZE);

    mNombre1Rect.d = mNombre1.d;
    mNombre1Rect.p.x = barraVidaCompleta1.p.x + 0;
    mNombre1Rect.p.y = barraVidaCompleta1.p.y + barraVidaCompleta1.d.h;

    mNombre2Rect.d = mNombre2.d;
    mNombre2Rect.p.x = barraVidaCompleta2.p.x + barraVidaCompleta2.d.w - mNombre2Rect.d.w;
    mNombre2Rect.p.y = barraVidaCompleta2.p.y + barraVidaCompleta2.d.h;

    // Timer
    mTimer = mUtils->createTextureFromText(FONT_PATH, timer, FONT_SIZE_FOR_TIMER);

    mTimerRect.d = mTimer.d;
    mTimerRect.p.x = dimPantalla.w / 2 + ajusteXTimer;
    mTimerRect.p.y = barraVidaCompleta1.p.y + ajusteYTimer;

    //Combo
    combo1 = mUtils->createTextureFromText(FONT_PATH, "", FONT_SIZE);
    combo2 = mUtils->createTextureFromText(FONT_PATH, "", FONT_SIZE);
    rectCombo1.p.x = posX1;
    rectCombo1.p.y = posYCombo;
    rectCombo2.p.y = posYCombo;
    combo1Activo = false;
    combo2Activo = false;
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void CapaInfoArcade::getTexture(Ttexture texture) {
    // Barras de vida
    mUtils->copyTexture(barraVidaCompletaText, texture, NULL, &barraVidaCompleta1);
    mUtils->copyTexture(barraVidaCompletaText, texture, NULL, &barraVidaCompleta2);
    mUtils->copyTexture(barraVidaParcialText, texture, &barraVidaParcialPedazo1, &barraVidaParcialPantalla1);
    mUtils->copyTexture(barraVidaParcialText, texture, &barraVidaParcialPedazo2, &barraVidaParcialPantalla2);

    // Nombres
    mUtils->copyTexture(mNombre1, texture, NULL, &mNombre1Rect);
    mUtils->copyTexture(mNombre2, texture, NULL, &mNombre2Rect);

    // Combos
    if (combo1Activo) mUtils->copyTexture(combo1, texture, NULL, &rectCombo1);
    if (combo2Activo) mUtils->copyTexture(combo2, texture, NULL, &rectCombo2);

    //Timer
    mUtils->copyTexture(mTimer, texture, NULL, &mTimerRect);
}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void CapaInfoArcade::update(Tinput input,TInfoExtra infoExtra) {
    barraVidaParcialPedazo1.d.w = anchoBorde + anchoRelleno * infoExtra.porcVida1;
    barraVidaParcialPedazo2.d.w = anchoBorde + anchoRelleno * infoExtra.porcVida2;
    barraVidaParcialPantalla1.d.w = barraVidaParcialPedazo1.d.w;
    barraVidaParcialPantalla2.d.w = barraVidaParcialPedazo2.d.w;
    barraVidaParcialPedazo2.p.x = barraVidaCompleta1.d.w - barraVidaParcialPedazo2.d.w;
    barraVidaParcialPantalla2.p.x = anchoPantalla - barraVidaParcialPedazo2.d.w - distBorde;

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

    SDL_DestroyTexture(mTimer.t);
    mTimer = mUtils->createTextureFromText(FONT_PATH, infoExtra.timer, FONT_SIZE_FOR_TIMER);
}

void CapaInfoArcade::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    SDL_DestroyTexture(barraVidaCompletaText.t);
    SDL_DestroyTexture(barraVidaParcialText.t);
    SDL_DestroyTexture(mNombre1.t);
    SDL_DestroyTexture(mNombre2.t);
    SDL_DestroyTexture(combo1.t);
    SDL_DestroyTexture(combo2.t);
    SDL_DestroyTexture(mTimer.t);
    loguer->loguear("Elimina capa", Log::LOG_DEB);
}

CapaInfoArcade::~CapaInfoArcade() {}