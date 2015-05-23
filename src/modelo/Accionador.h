#ifndef MORTALKOMBAT_ACCIONADOR_H
#define MORTALKOMBAT_ACCIONADOR_H


#include "../Common.h"
#include "Golpe.h"
#include "Poder.h"

class Accionador {

public:

    float alturaPj;
    Trect rectaDelPj;

    float anchoPantalla;
    float ydelPiso;

    TestadoPersonaje estAct;
    TestadoPersonaje estAnt;

    Tdireccion direcBloqueada;

    Golpe* golpe;
    Poder* poder;

    Accionador();

    ~Accionador();

    void initialize(Trect rectan, float anchoEscenario, float yPiso,Poder* nuevoPoder,Golpe* nuevoGolpe);

    Trect laAccion(TestadoPersonaje estadoPj,int loops, Posicion pos, Tsentido sentido, Tdireccion direccion);

    //Mocimientos
    void caminar(Tsentido sentido, Tdireccion direccion);
    void saltarVerticualmente(int loops);
    void saltarOblicuamente(int loops, Tsentido sentido, Tdireccion direccion);
    void subirEnSaltoOblicuo(float deltaMovX, float deltaMovY, Tsentido sentido);
    void bajarEnSaltoOblicuo(float deltaMovX, float deltaMovY, Tsentido sentido);
    void agachar();
    void ponerseDePie();

    //GOLPES
    void piniaBaja(int loops,Tdireccion direccion);
    void piniaBajaAgachado(int loops,Tdireccion direccion);
    void piniaAlta(int loops,Tdireccion direccion);
    void piniaAltaAgachado(int loops,Tdireccion direccion);
    void patadaBaja(int loops,Tdireccion direccion);
    void patadaBajaAtras(int loops,Tdireccion direccion);
    void patadaAltaAtras(int loops,Tdireccion direccion);
    void patadaAlta(int loops,Tdireccion direccion);
    void golpeSaltoVertical(int loops,Tdireccion direccion);
    void golpeSaltoOblicuo(int loops, Tdireccion direccion);
    void patadaAgachado(int loops,Tdireccion direccion);
    //PODER
    void activarPoder(Tdireccion direccion);
    Golpe* getGolpe();


    //REACCIONES
    void reaccionTrasPiniaAlta(int loops, Tdireccion direccion);
    void reaccionTrasGolpeFuerte(int loops, Tdireccion direccion);
    void reaccionBarrida(int loops, Tdireccion direccion);

    //Colisiones
    Posicion desplazado(float deltaDesplazo, Tdireccion direccion);
    Trect setPosicionPersonaje(Posicion posicion);

    void ajustarPiso();
};


#endif //MORTALKOMBAT_ACCIONADOR_H