#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include "../parser/config.h"
#include "Personaje.h"
#include "../Common.h"
#include "DetectorDeColisiones.h"

class Mundo {
private:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;
	Personaje* personaje2;
	float anchoPantalla;

public:
	DetectorDeColisiones colisionador;
	Mundo(config configuracion);

	vector<Personaje*> getPersonajes();
	float getAncho();
	float getAlto();
	float getAltoPiso();

	int loopsReaccionGolpeFuerte;
	vector<Tcambio> actualizarMundo(vector<Tinput> inputs);

	virtual ~Mundo();

	void verificarDireccionDeLosPersonajes();

	void VerificarSiPjsColisionanaEnElAire();

	void verificarQueNoSeVallaDeLaPantalla();

	void verificarColision(bool generaViolencia,Personaje* agresor,Personaje* PJ,ObjetoColisionable* objeto,bool esPoder);

	Tcambio actualizarPJ(Personaje* PJ);

};

#endif /* SRC_MODELO_MUNDO_H_ */