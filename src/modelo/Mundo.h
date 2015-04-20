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
	float anchoVentana;
	Personaje* personaje1;
	Personaje* personaje2;

	void actualizarPersonaje(Tcambio* c, Personaje* personaje);
	bool verificarDireccion(Posicion posPJ1, Posicion posPJ2);

public:
	Mundo(config configuracion);

	Personaje* getPersonaje();
	float getAncho();
	float getAlto();
	float getAltoPiso();

	Tcambio actualizarMundo(Tcambio c,Tinput input1, Tinput input2);

	virtual ~Mundo();
};

#endif /* SRC_MODELO_MUNDO_H_ */
