#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const int tiempoInicialRound = 99;

/* Constructor de Mundo.
 * Recibe la configuracion que se devuelve del parser.
 * Crea un personaje e inicializa su posicion, altura y ancho.
 * Tambien se inicializa el alto, ancho y yPiso del escenario.

 */
Mundo::Mundo(config configuracion,string nombrePjs[2]) {
	Tescenario escenario = configuracion.getEscenario();
	vector<Tpersonaje> personajes = configuracion.getPersonajes();
	float anchoVentana = configuracion.getVentana().ancho;

	Tpersonaje PJ1 = personajes[0];
	Tpersonaje PJ2 = personajes[1];

	anchoEscenario = escenario.d.w;
	altoEscenario = escenario.d.h;
	altoPiso = escenario.yPiso;

	float pos_x1 = anchoEscenario/2 - anchoVentana/2 + MIN_DISTANCE_FROM_BOUND;
	float pos_x2 = anchoEscenario/2 + anchoVentana/2 - PJ2.d.w - MIN_DISTANCE_FROM_BOUND;
	float pos_y1 = altoEscenario - altoPiso - PJ1.d.h;
	float pos_y2 = altoEscenario - altoPiso - PJ2.d.h;

	Tdireccion direccion1 = PJ1.orientacion;
	Tdireccion direccion2 = PJ2.orientacion;

	Trect rectanguloPj1,rectanguloPj2;
	rectanguloPj1.d = PJ1.d;
	rectanguloPj2.d = PJ2.d;
	rectanguloPj1.p = {pos_x1, pos_y1};
	rectanguloPj2.p = {pos_x2,pos_y2};


	// TODO: Cuando se seleccionan los personajes hay que pasarles los nombres

	personaje1 = new Personaje(nombrePjs[0],direccion1,rectanguloPj1,anchoVentana,configuracion.getCombos());
	personaje2 = new Personaje(nombrePjs[1],direccion2,rectanguloPj2,anchoVentana,configuracion.getCombos());

	colisionador = DetectorDeColisiones(anchoVentana,anchoEscenario);

	anchoPantalla = configuracion.getVentana().ancho;

	roundsPJ1 = roundsPJ2 = 0;

	tiempoRound = tiempoInicialRound;

	tiempoInicial = SDL_GetTicks();

	InteligenciaArtificial inteligencia = InteligenciaArtificial();

}

void Mundo::verificarDireccionDeLosPersonajes() {
	//direccion derecha igual true
	//TODO: ESTO DEBERIA ANDAR AL REVEZ, PERO NO ME ANDA. VER DESPUES
	//osea pidiendo que el estado actual sea diferente de la accion y la reaccion agarre
	// para que haga el cambio de direccion
	if(personaje1->estadoActual == ACC_AGARRE || personaje1->estadoActual == REA_AGARRE) {
		//cout<<"No entro"<<endl;
	}else {
		if (personaje1->rectanguloPj.p.getX() < personaje2->rectanguloPj.p.getX()) {
			personaje1->direccionPj = DERECHA;
			personaje2->direccionPj = IZQUIERDA;

		}
		else if (personaje1->rectanguloPj.p.getX() > personaje2->rectanguloPj.p.getX()) {
			personaje1->direccionPj = IZQUIERDA;
			personaje2->direccionPj = DERECHA;
		}
	}
}

Tcambio Mundo::actualizarPJ(Personaje *PJ) {
	if(personaje1->estadoActual == REA_MAREADO) personaje2->estadoFatality = true;
	if(personaje2->estadoActual == REA_MAREADO) personaje1->estadoFatality = true;

	Tcambio cambio;
	cambio.dPJ = PJ->rectanguloPj.d;
	cambio.posicion = PJ->rectanguloPj.p;
	cambio.direccion = PJ->direccionPj;
	cambio.sentido = PJ->sentidoPj;
	cambio.estado = PJ->estadoActual;

	cambio.vida = PJ->vida;

	cambio.poder.d = PJ->poder->rectanguloPoder.d;
	cambio.poder.p = PJ->poder->rectanguloPoder.p;
	cambio.poder.e = PJ->poder->estado;

	cambio.tiempoRound = tiempoRound;

	if(PJ->comboPoder->puedoRealizarCombo()){
		cambio.hayCombo = true;
		cambio.nombreCombo = PJ->comboPoder->cadenaParaBuffer;
	}

	else if(PJ->comboFatality->puedoRealizarCombo()){
		cambio.hayCombo = true;
		cambio.nombreCombo = PJ->comboFatality->cadenaParaBuffer;
	}

	else if(PJ->comboPoder->puedoRealizarCombo()){
		cambio.hayCombo = true;
		cambio.nombreCombo = PJ->comboFatality2->cadenaParaBuffer;
	}
	else cambio.hayCombo = false;

	return cambio;
}

/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
vector<Tcambio> Mundo::actualizarMundo(vector<Tinput> inputs,EgameState modoDeJuego) {
	vector<Tcambio> c;
	Tcambio cambio1, cambio2;

	verificarGanadorDelRound();
	validarAlGanador();
	Uint32 tiempo = SDL_GetTicks();
	//cout<<tiempoInicial<<"----"<<tiempo<<endl;d
	if(SDL_TICKS_PASSED(tiempo, tiempoInicial + 1000)) {
		tiempoInicial = tiempo;
		tiempoRound--;
	}


	//Verifica y da vuelta la direccion de los personajes si se pasan
	verificarDireccionDeLosPersonajes();


	// Los personajes realizan sus acciones
	personaje1->realizarAccion(inputs[0]);

	if(modoDeJuego == EgameState::MODE_PRACTICE){
		Tinput input;
		input.movimiento = TinputMovimiento::KEY_NADA;
		input.accion = TinputAccion::KEY_NADA;
		personaje2->realizarAccion(input);
		if(personaje2->vida <= 50) personaje2->vida += 50;
		personaje1->estadoFatality = true;
	}

	else if(modoDeJuego == EgameState::MODE_ARCADE){
		Tinput input = inteligencia.responderDeacuerdoa(personaje1->estadoActual,personaje1->rectanguloPj,personaje2->rectanguloPj);
		personaje2->realizarAccion(input);

	}
	else if(modoDeJuego == EgameState::MODE_MULTIPLAYER) personaje2->realizarAccion(inputs[1]);


	// COLISIONES
	colisionador.resolverColisiones(personaje1,personaje2);
	//Se actualizan a los personajes
	cambio1 = actualizarPJ(personaje1);
	cambio2 = actualizarPJ(personaje2);

	c.push_back(cambio1);
	c.push_back(cambio2);
	return c;
}

bool Mundo::huboGanador() {
	return ((personaje1->getResultado() == PERDIO_MATCH) &&  (personaje2->getResultado() == GANO_MATCH)||
			((personaje2->getResultado() == PERDIO_MATCH) &&  (personaje1->getResultado() == GANO_MATCH)));
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libero a los personajes", Log::LOG_DEB);
}

void Mundo::verificarGanadorDelRound() {
	string mensaje;
	mensaje = "Ganador Round N°" + to_string(roundsPJ1 + roundsPJ2) + ": ";
	// Si el tiempo se termino me fijo quien tiene mas vida -------------------------
	if(tiempoRound == 0) {
		if (personaje1->vida > personaje2->vida ) {
			mensaje = mensaje + personaje1->nombre + " ---> Personaje 1";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			if(roundsPJ1 == 1) {
				personaje2->reinicializar(REA_MAREADO);
			}else {
				personaje1->reinicializar(REA_VICTORIA);
				personaje2->reinicializar(REA_DERROTA);
			}
			tiempoRound = tiempoInicialRound;
		}else if(personaje2->vida > personaje1->vida ){
			mensaje = mensaje + personaje2->nombre + " ---> Personaje 2";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			if(roundsPJ2 == 1) {
				personaje1->reinicializar(REA_MAREADO);
			}else{
				personaje2->reinicializar(REA_VICTORIA);
				personaje1->reinicializar(REA_DERROTA);
			}
			tiempoRound = tiempoInicialRound;
		}else{
			loguer->loguear("EMPATARONNNN", Log::LOG_DEB);
			personaje1->reinicializar(REA_VICTORIA);
			personaje2->reinicializar(REA_VICTORIA);
			tiempoRound = tiempoInicialRound;
		};
	}
	//-------------------------------------------------------
	else{
		if (personaje1->vida <= 0) {
			mensaje = mensaje + personaje2->nombre + " ---> Personaje 2";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			if(roundsPJ2 == 1) {
				personaje1->reinicializar(REA_MAREADO);
			}
			else{
				personaje1->reinicializar(REA_DERROTA);
				personaje2->reinicializar(REA_VICTORIA);
			}
			tiempoRound = tiempoInicialRound;

		}else if(personaje2->vida <= 0){
			mensaje = mensaje + personaje2->nombre + " ---> Personaje 1";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			if(roundsPJ1 == 1){
				personaje2->reinicializar(REA_MAREADO);
			}
			else{
				personaje1->reinicializar(REA_VICTORIA);
				personaje2->reinicializar(REA_DERROTA);
			}
			tiempoRound = tiempoInicialRound;
		}
	}
}



void Mundo::validarAlGanador() {
	if (personaje1->getResultado() == PERDIO) {
		roundsPJ2++;
		if(roundsPJ2 == 2 || roundsPJ1 == 2){
			if(roundsPJ2 == 2){
				personaje1->setResultado(PERDIO_MATCH);
				personaje2->setResultado(GANO_MATCH);
			}else{
				personaje1->setResultado(GANO_MATCH);
				personaje2->setResultado(PERDIO_MATCH);
			}
		}else{
			personaje1->setResultado(NADA);
			personaje2->setResultado(NADA);
		}
		tiempoRound = tiempoInicialRound;
	} else if (personaje2->getResultado() == PERDIO) {
		roundsPJ1++;
		if(roundsPJ2 == 2 || roundsPJ1 == 2){
			if(roundsPJ2 == 2){
				personaje1->setResultado(PERDIO_MATCH);
				personaje2->setResultado(GANO_MATCH);
			}else{
				personaje1->setResultado(GANO_MATCH);
				personaje2->setResultado(PERDIO_MATCH);
			}
		}else{
			personaje1->setResultado(NADA);
			personaje2->setResultado(NADA);
		}
		tiempoRound = tiempoInicialRound;
	}
}


string Mundo::quienGano(){
	if(personaje1->getResultado() == GANO_MATCH) {
		roundsPJ1 = 0;
		roundsPJ2 = 0;
		personaje1->setResultado(NADA);
		personaje2->setResultado(NADA);
		return personaje1->nombre;
	}
	if(personaje2->getResultado() == GANO_MATCH) {
		roundsPJ1 = 0;
		roundsPJ2 = 0;
		personaje1->setResultado(NADA);
		personaje2->setResultado(NADA);
		return personaje2->nombre;
	}
}

