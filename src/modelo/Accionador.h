#ifndef MORTALKOMBAT_ACCIONADOR_H
#define MORTALKOMBAT_ACCIONADOR_H


#include "../Common.h"
#include "Golpe.h"
#include "Poder.h"

class Accionador {

public:

    Trect rectaDelPj;

    float anchoPantalla;
    float ydelPiso;

    TestadoPersonaje nuevoEstado;
    Tdireccion direcBloqueada;

    Golpe* golpe;
    Poder* poder;

    Accionador();

    ~Accionador();

    void initialize(Trect rectan, float anchoEscenario, float yPiso,Poder* nuevoPoder);

    Trect laAccion(TestadoPersonaje estadoPj,int loops, Posicion pos, Tsentido sentido, Tdireccion direccion);

    //Mocimientos
    void caminar(Tsentido sentido, Tdireccion direccion);
    void saltarVerticualmente(int loops);
    void saltarOblicuamente(int loops, Tsentido sentido, Tdireccion direccion);
    void agachar();


    //GOLPES
    void piniaBaja(int loops);
    void piniaBajaAgachado(int loops);
    void piniaAlta(int loops,Tdireccion direccion);
    void piniaAltaAgachado(int loops);
    void piniaSalto(int loops);
    void patadaBaja(int loops);
    void patadaBajaAtras(int loops);
    void patadaAltaAtras(int loops);
    void patadaAlta(int loops);
    void patadaSalto(int loops);
    void patadaSaltoVertical(int loops);
    void patadaAgachado(int loops);

    Posicion desplazado(float deltaDesplazo, Tdireccion direccion);

    Golpe* getGolpe();

    void subirEnSaltoOblicuo(float deltaMovX, float deltaMovY, Tsentido sentido, Tdireccion direccion);

    void bajarEnSaltoOblicuo(float deltaMovX, float deltaMovY, Tsentido sentido, Tdireccion direccion);

    void activarPoder(Tdireccion direccion);

    void reaccionTrasPiniaAlta(int loops, Tdireccion direccion);

    void reaccionTrasGolpeFuerte(int loops, Tdireccion direccion);

    void reaccionBarrida(int loops, Tdireccion direccion);
};


#endif //MORTALKOMBAT_ACCIONADOR_H