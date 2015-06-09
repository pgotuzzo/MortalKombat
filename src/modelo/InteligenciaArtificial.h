#ifndef MORTALKOMBAT_INTELIGENCIAARTIFICIAL_H
#define MORTALKOMBAT_INTELIGENCIAARTIFICIAL_H

#include "../utils/Common.h"
#include "../utils/PersonajeUtils.h"
#include<ctime>

class InteligenciaArtificial {

public:
    bool proteccion=false;
    int loopEnProtec=0;
    InteligenciaArtificial();
    virtual ~InteligenciaArtificial();
    Tinput responderDeacuerdoa(TestadoPersonaje,Trect,Trect);

};


#endif //MORTALKOMBAT_INTELIGENCIAARTIFICIAL_H
