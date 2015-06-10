#ifndef SRC_MODELO_MUNDO_H_
#define SRC_MODELO_MUNDO_H_

#include <SDL2/SDL_stdinc.h>
#include "../parser/config.h"
#include "Personaje.h"
#include "DetectorDeColisiones.h"
#include "SDL2/SDL.h"
#include "../utils/GameUtils.h"
#include "InteligenciaArtificial.h"

class Mundo {
public:
	float anchoEscenario;
	float altoEscenario;
	float altoPiso;
	Personaje* personaje1;
	Personaje* personaje2;
	float anchoPantalla;

	int roundsPJ1, roundsPJ2;
	int tiempoRound;

	Uint32 tiempoInicial;

	InteligenciaArtificial inteligencia;
	DetectorDeColisiones colisionador;
	Mundo(config configuracion,string nombrePjs[2]);

	vector<Tcambio> actualizarMundo(vector<Tinput> inputs,EgameState modoDeJuego);

	virtual ~Mundo();

	void verificarDireccionDeLosPersonajes();

	void verificarGanadorDelRound();

	Tcambio actualizarPJ(Personaje* PJ);

	bool huboGanador();

	string quienGano();

	void validarAlGanador();
};

#endif /* SRC_MODELO_MUNDO_H_ */