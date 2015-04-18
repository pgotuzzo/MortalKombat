#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../parser/config.h"
#include "Personaje.h"
#include "../Common.h"

class Mundo {
private:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;

public:
	Mundo(config configuracion);

	Personaje* getPersonaje();
	float getAncho();
	float getAlto();
	float getAltoPiso();

	Tcambios actualizarMundo(Tcambios c,Tinputs inputs);

	virtual ~Mundo();
};

#endif /* SRC_MODELO_MUNDO_H_ */
