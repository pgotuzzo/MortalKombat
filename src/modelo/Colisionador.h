#ifndef MORTALKOMBAT_DETECTORDECOLISIONES_H
#define MORTALKOMBAT_DETECTORDECOLISIONES_H

#include "Personaje.h"
#include "Golpe.h"
#include "Poder.h"
#include "../Common.h"
#include "ObjetoColisionable.h"
#include <vector>

using namespace std;

class Colisionador {
private:
    bool sonProximos(ObjetoColisionable* primerObjeto,ObjetoColisionable* segundoObjeto,float delta);
public:
    Colisionador();
    vector<ObjetoColisionable*> detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta );
    bool seVan(Personaje* PJ1, Personaje* PJ2, float delta );
    void solucionarColision(Personaje* PJ1, Personaje* PJ2);
    void solucionarColision(Personaje* PJ,Golpe* golpeOponente);
    void solucionarColision(Personaje* PJ, Poder* poderOponente);
    virtual ~Colisionador();

    bool detectarLejania(Personaje *PJ1, Personaje *PJ2, float delta);
};


#endif //MORTALKOMBAT_DETECTORDECOLISIONES_H
