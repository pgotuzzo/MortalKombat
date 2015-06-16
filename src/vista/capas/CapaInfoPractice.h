#ifndef MORTALKOMBAT_CAPAINFOPRACTICE_H
#define MORTALKOMBAT_CAPAINFOPRACTICE_H


#include "CapaInfo.h"

class CapaInfoPractice : public CapaInfo{
protected:
    struct TeclaBuffer {
        Ttexture textura;
        Uint32 tiempoInicial;
    };
    Ttexture combo1;
    Ttexture combo2;
    Trect rectCombo1,rectCombo2;
    Uint32 tcombo1, tcombo2;
    bool combo1Activo,combo2Activo;

    VistaUtils* mUtils;
    float anchoBorde, anchoRelleno,anchoPantalla, distBorde;
    vector<Trect> rectBotones;
    queue<TeclaBuffer> buffer;


public:

    CapaInfoPractice(VistaUtils* utils, Tdimension dimPantalla, string nombres[2]);


    CapaInfoPractice();


    /*
    *  Guarda el pedazo de la capa a mostrar en le pedazo de textura pasado por parametro.
    *  texture : puntero a una textura del tamaño de la pantalla
    */
    void getTexture(Ttexture texture);


    /*
     * Cambia la posicion de la capa ajustandola a la posicion del escenario
     */
    void update(Tinput input,TInfoExtra infoExtra);

    ~CapaInfoPractice();

    void freeTextures();


};


#endif //MORTALKOMBAT_CAPAINFOPRACTICE_H
