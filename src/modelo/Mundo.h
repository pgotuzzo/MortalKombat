#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../parser/config.h"
#include "Personaje.h"
#include "DetectorDeColisiones.h"
#include "../Common.h"

class Mundo {
private:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;
	Personaje* personaje2;
	float anchoPantalla;

public:
	DetectorDeColisiones detector;
	Mundo(config configuracion);

	Personaje* getPersonaje();
	float getAncho();
	float getAlto();
	float getAltoPiso();

	vector<Tcambio> actualizarMundo(vector<Tinput> inputs);

	virtual ~Mundo();

	void verificarDireccionDeLosPersonajes();

	void VerificarSiPjsColisionanaEnElAire();

	void verificarQueNoSeVallaDeLaPantalla();
};

#endif /* SRC_MODELO_MUNDO_H_ */
