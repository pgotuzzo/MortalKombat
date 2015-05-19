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
    void piniaBaja(int loops,Tdireccion direccion);
    void piniaBajaAgachado(int loops,Tdireccion direccion);
    void piniaAlta(int loops,Tdireccion direccion);
    void piniaAltaAgachado(int loops,Tdireccion direccion);
    void piniaSalto(int loops,Tdireccion direccion);
    void patadaBaja(int loops,Tdireccion direccion);
    void patadaBajaAtras(int loops,Tdireccion direccion);
    void patadaAltaAtras(int loops,Tdireccion direccion);
    void patadaAlta(int loops,Tdireccion direccion);
    void patadaSalto(int loops,Tdireccion direccion);
    void patadaSaltoVertical(int loops,Tdireccion direccion);
    void patadaAgachado(int loops,Tdireccion direccion);

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