#ifndef MORTALKOMBAT_INTELIGENCIAARTIFICIAL_H
#define MORTALKOMBAT_INTELIGENCIAARTIFICIAL_H

#include "../utils/Common.h"
#include "../utils/PersonajeUtils.h"
#include<ctime>

class InteligenciaArtificial {

public:
    bool proteccion=false;
    int loopEnProtec=0;
    bool sigue=false;
    bool acercandose=false;
    bool pegado=false;
    TinputMovimiento dirPatada(Trect,Trect);
    TinputMovimiento meAcerco(Trect,Trect);
    InteligenciaArtificial();
    virtual ~InteligenciaArtificial();
    Tinput responderDeacuerdoa(TestadoPersonaje,Trect,Trect);

};


#endif //MORTALKOMBAT_INTELIGENCIAARTIFICIAL_H