#ifndef MORTALKOMBAT_CAPAINFOARCADE_H
#define MORTALKOMBAT_CAPAINFOARCADE_H


#include "../VistaUtils.h"

using namespace std;

class CapaInfoArcade :public CapaInfo {
protected:
    VistaUtils* mUtils;
    Ttexture barraVidaCompletaText;
    Ttexture barraVidaParcialText;
    Ttexture mNombre1;
    Ttexture mNombre2;
    Ttexture mTimer;
    float anchoBorde, anchoRelleno,anchoPantalla, distBorde;
    Trect barraVidaCompleta1, barraVidaCompleta2, barraVidaParcialPedazo1,
            barraVidaParcialPedazo2, barraVidaParcialPantalla1, barraVidaParcialPantalla2,
            mNombre1Rect, mNombre2Rect, mTimerRect;

public:
    CapaInfoArcade();
    /*
    *  Crea una capa.
    *  renderer : renderer utilizado
    *  dirPath : direccion de la imagen de la capa
    *  rectPantalla : contiene el tamaño de la pantalla y la posicion inicial de la
    *  capa en relacion a su tamaño total de la imagen
    */
    CapaInfoArcade(VistaUtils* utils, Tdimension dimPantalla, string nombres[2],string timer);


    /*
    *  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
    *  texture : puntero a una textura del tamaño de la pantalla
    */
    void getTexture(Ttexture texture);


    /*
     * Cambia la posicion de la capa ajustandola a la posicion del escenario
     */
    void update(float porcVida1,float porcVida2,Tinput input);

    void freeTextures();

    virtual ~CapaInfoArcade();

    void update(float porcVida1, float porcVida2, Tinput input, string timer);
};



#endif //MORTALKOMBAT_CAPAINFOARCADE_H
