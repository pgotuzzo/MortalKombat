#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../parser/config.h"
#include "Personaje.h"

class Mundo {
public:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;

	Mundo(config configur);
	Personaje* getPersonaje();
	float getAncho();
	float getAlto();
	float getAltoPiso();
	Posicion actualizarMundo(int orden);
	virtual ~Mundo();
};

#endif /* SRC_MODELO_MUNDO_H_ */
