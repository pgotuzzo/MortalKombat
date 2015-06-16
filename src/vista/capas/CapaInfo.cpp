#include "CapaInfo.h"

const float porcBarraRelleno = (const float) (162.0/168.0);
const float porcTamBarraPantallaX = 0.35;
const float porcTamBarraPantallaY = 0.05;
const float porcDistBarraPantallaX = 0.05;
const float porcDistBarraPantallaY = 0.04;
const string dirPathVidaRoja = "resources/accesorios/barraVidaRoja.gif";
const string dirPathVidaVerde = "resources/accesorios/barraVidaVerde.gif";

CapaInfo::CapaInfo() {}

/*
*  Crea una capa.
*  renderer : renderer utilizado
*  dirPath : direccion de la imagen de la capa
*  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
*  capa en relacion a su tamaño total de la imagen
*  anchoCapa : ancho total de la capa en unidades.
*/
CapaInfo::CapaInfo(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]) {}

/*
*  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
*  texture : puntero a una textura del tamaño de la pantalla
*/
void CapaInfo::getTexture(Ttexture texture) {}

/*
 * Cambia la posicion de la capa ajustandola a la posicion del escenario
 */
void CapaInfo::update(Tinput input,TInfoExtra infoExtra) {}

void CapaInfo::freeTextures() {}

CapaInfo::~CapaInfo() {}
