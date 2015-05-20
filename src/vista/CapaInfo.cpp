#include "CapaInfo.h"

const float porcBarraRelleno = 162.0/168.0;
const float porcTamBarraPantallaX = 0.35;
const float porcTamBarraPantallaY = 0.05;
const float porcDistBarraPantallaX = 0.05;
const float porcDistBarraPantallaY = 0.04;
const string dirPathVidaRoja = "resources/accesorios/barraVidaRoja.gif";
const string dirPathVidaVerde = "resources/accesorios/barraVidaVerde.gif";

const string FONT_PATH = "resources/font/mortalkombat2.ttf";
const int FONT_SIZE = 18;

CapaInfo::CapaInfo() {}

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*  anchoCapa : ancho total de la capa en unidades.
*/
CapaInfo::CapaInfo(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]) {
    mUtils= utils;

    // Barras de vida
    float anchoBarra = dimPantalla.w*porcTamBarraPantallaX;
    float altoBarra = dimPantalla.h*porcTamBarraPantallaY;
    barraVidaCompleta1.d = Tdimension(anchoBarra, altoBarra);
    barraVidaCompleta2.d = Tdimension(anchoBarra, altoBarra);

    float posX1 = dimPantalla.w*porcDistBarraPantallaX;
    float posX2 = dimPantalla.w-anchoBarra-posX1;
    float posY = dimPantalla.h*porcDistBarraPantallaY;
    barraVidaCompleta1.p = Posicion(posX1,posY);
    barraVidaCompleta2.p = Posicion(posX2,posY);

    barraVidaParcialPantalla1 = barraVidaCompleta1;
    barraVidaParcialPantalla2 = barraVidaCompleta2;

    barraVidaParcialPedazo1.p.x = 0;
    barraVidaParcialPedazo1.p.y = 0;
    barraVidaParcialPedazo1.d.w = anchoBarra;
    barraVidaParcialPedazo1.d.h = altoBarra;
    barraVidaParcialPedazo2 = barraVidaParcialPedazo1;

    anchoRelleno = anchoBarra*porcBarraRelleno;
    anchoBorde = (anchoBarra-anchoRelleno)/2;

    barraVidaCompletaText = mUtils->loadTexture(dirPathVidaRoja);
    barraVidaParcialText = mUtils->loadTexture(dirPathVidaVerde);

    anchoPantalla = dimPantalla.w;
    distBorde = posX1;

    // Nombres
    mNombre1 = mUtils->createTexture(FONT_PATH, nombres[0], FONT_SIZE);
    mNombre2 = mUtils->createTexture(FONT_PATH, nombres[1], FONT_SIZE);

    mNombre1Rect.d = mUtils->getDimension(mNombre1);
    mNombre1Rect.p.x = barraVidaCompleta1.p.x + 0;
    mNombre1Rect.p.y = barraVidaCompleta1.p.y + barraVidaCompleta1.d.h;

    mNombre2Rect.d = mUtils->getDimension(mNombre2);
    mNombre2Rect.p.x = barraVidaCompleta2.p.x + barraVidaCompleta2.d.w - mNombre2Rect.d.w;
    mNombre2Rect.p.y = barraVidaCompleta2.p.y + barraVidaCompleta2.d.h;
}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void CapaInfo::getTexture(SDL_Texture *texture) {
    // Barras de vida
    mUtils->copyTexture(barraVidaCompletaText, texture, NULL, &barraVidaCompleta1, &barraVidaCompleta1.d, NULL);
    mUtils->copyTexture(barraVidaCompletaText, texture, NULL, &barraVidaCompleta2, &barraVidaCompleta1.d, NULL);
    mUtils->copyTexture(barraVidaParcialText, texture, &barraVidaParcialPedazo1, &barraVidaParcialPantalla1, &barraVidaCompleta1.d, NULL);
    mUtils->copyTexture(barraVidaParcialText, texture, &barraVidaParcialPedazo2, &barraVidaParcialPantalla2, &barraVidaCompleta1.d, NULL);

    // Nombres
    mUtils->copyTexture(mNombre1, texture, NULL, &mNombre1Rect, NULL, NULL);
    mUtils->copyTexture(mNombre2, texture, NULL, &mNombre2Rect, NULL, NULL);
}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void CapaInfo::update(float porcVida1,float porcVida2) {
    barraVidaParcialPedazo1.d.w = anchoBorde+anchoRelleno*porcVida1;
    barraVidaParcialPedazo2.d.w = anchoBorde+anchoRelleno*porcVida2;
    barraVidaParcialPantalla1.d.w = barraVidaParcialPedazo1.d.w;
    barraVidaParcialPantalla2.d.w = barraVidaParcialPedazo2.d.w;
    barraVidaParcialPedazo2.p.x = barraVidaCompleta1.d.w-barraVidaParcialPedazo2.d.w;
    barraVidaParcialPantalla2.p.x = anchoPantalla-barraVidaParcialPedazo2.d.w-distBorde;
}

void CapaInfo::freeTextures() {
    loguer->loguear("Elimina capa", Log::LOG_DEB);
    SDL_DestroyTexture(barraVidaCompletaText);
    SDL_DestroyTexture(barraVidaParcialText);
    SDL_DestroyTexture(mNombre1);
    SDL_DestroyTexture(mNombre2);
    loguer->loguear("Elimina capa", Log::LOG_DEB);
}

CapaInfo::~CapaInfo() {}
