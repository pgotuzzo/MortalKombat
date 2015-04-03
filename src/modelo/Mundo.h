/*
 * Mundo.h
 *
 *  Created on: 3/4/2015
 *      Author: miguel
 */

#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../modelo/Personaje.h"
#include "../parser/config.h"

using namespace configuracion;

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
