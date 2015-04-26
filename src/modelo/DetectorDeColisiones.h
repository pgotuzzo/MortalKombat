#ifndef MORTALKOMBAT_DETECTORDECOLISIONES_H
#define MORTALKOMBAT_DETECTORDECOLISIONES_H

#include "Personaje.h"
#include "../Common.h"
#include "ObjetoColisionable.h"
#include <vector>

using namespace std;

class DetectorDeColisiones {
private:
    bool sonProximos(ObjetoColisionable* primerObjeto,ObjetoColisionable* segundoObjeto,float delta);
public:
    DetectorDeColisiones();
    vector<ObjetoColisionable*> detectorDeProximidad(vector<ObjetoColisionable*> objetos, float delta );
    virtual ~DetectorDeColisiones();

};


#endif //MORTALKOMBAT_DETECTORDECOLISIONES_H
