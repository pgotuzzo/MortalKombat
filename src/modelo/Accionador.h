#ifndef MORTALKOMBAT_ACCIONADOR_H
#define MORTALKOMBAT_ACCIONADOR_H


#include "../Common.h"
#include "Golpe.h"

class Accionador {

public:

    Trect rectaDelPj;

    float anchoEsc;
    float ydelPiso;

    TestadoPersonaje nuevoEstado;

    Golpe golpe;

    Accionador();

    ~Accionador();

    void initialize(Trect rectan, float anchoEscenario, float yPiso);

    Trect laAccion(TestadoPersonaje estadoPj,int loops, Posicion pos, Tsentido sentido, Tdireccion direccion);

    //Mocimientos
    void caminar(Tsentido sentido, Tdireccion direccion);
    void saltarVerticualmente(int loops);
    void saltarOblicuamente(int loops, Tsentido sentido, Tdireccion direccion);
    void agachar();


    //GOLPES
    void piniaBaja(int loops);
    void piniaBajaAgachado(int loops);
    void piniaAlta(int loops);
    void piniaAltaAgachado(int loops);
    void piniaSalto(int loops);
    void patadaBaja(int loops);
    void patadaBajaAtras(int loops);
    void patadaAltaAtras(int loops);
    void patadaAlta(int loops);
    void patadaSalto(int loops);
    void patadaSaltoVertical(int loops);
    void patadaAgachado(int loops);
};


#endif //MORTALKOMBAT_ACCIONADOR_H