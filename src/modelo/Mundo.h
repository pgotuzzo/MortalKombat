#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../parser/config.h"
#include "Personaje.h"
#include "../Common.h"
#include "Colisionador.h"

class Mundo {
private:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;
	Personaje* personaje2;
	float anchoPantalla;

public:
	Colisionador colisionador;
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

	void verificarColision(bool generaViolencia, Personaje* PJ, ObjetoColisionable* objeto,bool esPoder);

	Tcambio actualizarPJ(Personaje* PJ);

};

#endif /* SRC_MODELO_MUNDO_H_ */
