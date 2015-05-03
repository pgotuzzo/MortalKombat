

#ifndef MORTALKOMBAT_CREADORDEGOLPES_H
#define MORTALKOMBAT_CREADORDEGOLPES_H

# include "../Common.h"
# include "Golpe.h"

class CreadorDeGolpes{

public:
    Golpe* golpe;

    CreadorDeGolpes();

    void crearGolpe(TestadoPersonaje tipoDeGolpe, Posicion posPJ, float anchoPJ, float altoPJ, bool direccion);

    Golpe* getGolpe();

    virtual ~CreadorDeGolpes();
};


#endif //MORTALKOMBAT_CREADORDEGOLPES_H
