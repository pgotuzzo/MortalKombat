#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include <SDL2/SDL_stdinc.h>
#include "../parser/config.h"
#include "Personaje.h"
#include "DetectorDeColisiones.h"
#include "SDL2/SDL.h"
#include "../utils/GameUtils.h"

class Mundo {
private:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;
	Personaje* personaje2;
	float anchoPantalla;

	int roundsPJ1, roundsPJ2;
	int tiempoRound;

	Uint32 tiempoInicial;

public:
	DetectorDeColisiones colisionador;
	Mundo(config configuracion);

	vector<Tcambio> actualizarMundo(vector<Tinput> inputs);

	virtual ~Mundo();

	void verificarDireccionDeLosPersonajes();

	void verificarGanadorDelRound();

	Tcambio actualizarPJ(Personaje* PJ);

	bool huboGanador();

	string quienGano();

	void verificarGanador();
};

#endif /* SRC_MODELO_MUNDO_H_ */