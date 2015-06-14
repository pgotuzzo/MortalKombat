#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const int tiempoInicialRound = 99;
const int tiempoDeFatality = 20;

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
	if(personaje1->estadoActual == REA_MAREADO) {
		personaje1->vida = 1;
		personaje2->estadoFatality = true;
	}
	if(personaje2->estadoActual == REA_MAREADO) {
		personaje2->vida = 1;
		personaje1->estadoFatality = true;
	}

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
	if(colisionador.detectarColision(personaje1,personaje2)){
		personaje1->colisionando = true;
		personaje2->colisionando = true;
	}else {
		personaje1->colisionando = false;
		personaje2->colisionando = false;
	}
	vector<Tcambio> c;
	Tcambio cambio1, cambio2;

	verificarGanadorDelRound();
	terminoLaPelea();
	Uint32 tiempo = SDL_GetTicks();
	//cout<<tiempoInicial<<"----"<<tiempo<<endl;d
	if(SDL_TICKS_PASSED(tiempo, tiempoInicial + 1000)) {
		tiempoInicial = tiempo;
		tiempoRound--;
	}

	if(inputs[0].game == TinputGame::KEY_REDUCCION_VIDA){
		personaje1->vida -= 5;
	}
	if(inputs[1].game == TinputGame::KEY_REDUCCION_VIDA){
		personaje2->vida -= 5;
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
		if(tiempoRound <= 50) tiempoRound += 50;
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
	detectarRealiaccionesDeFatalities();

	cambio1 = actualizarPJ(personaje1);
	cambio2 = actualizarPJ(personaje2);

	c.push_back(cambio1);
	c.push_back(cambio2);
	return c;
}


void Mundo::verificarGanadorCuandoSeAcabaElTiempo() {
	if (personaje1->vida > personaje2->vida) {
		if (roundsPJ1 == 1) {
			personaje2->reinicializar(REA_MAREADO);
			personaje2->vida = 1;
			tiempoRound = tiempoDeFatality;
		} else {
			personaje1->reinicializar(REA_VICTORIA);
			personaje2->reinicializar(REA_DERROTA);
			personaje1->vida = 100;
			personaje2->vida = 100;
			tiempoRound = tiempoInicialRound;
		}
		roundsPJ1++;
	} else if (personaje2->vida > personaje1->vida) {
		if (roundsPJ2 == 1) {
			personaje1->reinicializar(REA_MAREADO);
			personaje1->vida = 1;
			tiempoRound = tiempoDeFatality;
		} else {
			personaje2->reinicializar(REA_VICTORIA);
			personaje1->reinicializar(REA_DERROTA);
			personaje1->vida = 100;
			personaje2->vida = 100;
			tiempoRound = tiempoInicialRound;
		}
		roundsPJ2++;
	} else {
		if (roundsPJ2 == 1 && roundsPJ1 == 0) {
			personaje1->estadoActual = REA_MAREADO;
			tiempoRound = tiempoDeFatality;
		} else if (roundsPJ1 == 1 && roundsPJ2 == 0) {
			personaje2->estadoActual = REA_MAREADO;
			tiempoRound = tiempoDeFatality;
		} else if (roundsPJ1 == 1 && roundsPJ2 == 1) {
			personaje1->estadoActual = REA_MAREADO;
			personaje2->estadoActual = REA_MAREADO;
			tiempoRound = tiempoDeFatality;
		} else if (roundsPJ1 == 0 && roundsPJ2 == 0) {
			personaje1->estadoActual = REA_VICTORIA;
			personaje2->estadoActual = REA_VICTORIA;
			tiempoRound = tiempoInicialRound;
		}
		roundsPJ1++;
		roundsPJ2++;
	}
}

void Mundo::verificarSiTerminoElRound() {
	if (personaje1->vida == 0) {
		if(roundsPJ2 == 1) {
			personaje1->reinicializar(REA_MAREADO);
			personaje1->vida = 1;
			roundsPJ2++;
			tiempoRound = tiempoDeFatality;
		}
		else{
			personaje1->reinicializar(REA_DERROTA);
			personaje2->reinicializar(REA_VICTORIA);
			roundsPJ2++;
			personaje1->vida = 100;
			personaje2->vida = 100;
			tiempoRound = tiempoInicialRound;
		}
	}else if(personaje2->vida == 0) {
		if (roundsPJ1 == 1) {
			personaje2->reinicializar(REA_MAREADO);
			personaje2->vida = 1;
			roundsPJ1++;
			tiempoRound = tiempoDeFatality;
		}
		else {
			personaje1->reinicializar(REA_VICTORIA);
			personaje2->reinicializar(REA_DERROTA);
			roundsPJ1++;
			personaje1->vida = 100;
			personaje2->vida = 100;
			tiempoRound = tiempoInicialRound;
		}
	}
}

void Mundo::verificarGanadorDelRound() {
	// Si el tiempo se termino me fijo quien tiene mas vida
	if(tiempoRound == 0) {
		verificarGanadorCuandoSeAcabaElTiempo();
	} else if(!personaje1->estadoFatality || !personaje2->estadoFatality){
		verificarSiTerminoElRound();
		}
}

void Mundo::terminoLaPelea(){
	if(roundsPJ1 == 2 && !personaje1->estadoFatality && roundsPJ2 <=1) {
		personaje1->llevarACabo.resultado = GANO;
		personaje2->llevarACabo.resultado = PERDIO;
	}else if((roundsPJ2 == 2 && !personaje1->estadoFatality && roundsPJ1 <=1)){
		personaje1->llevarACabo.resultado = PERDIO;
		personaje2->llevarACabo.resultado = GANO;
	}else if((roundsPJ1 == 2) &&(roundsPJ2 == 2)){
		personaje1->llevarACabo.resultado = EMPATO;
		personaje2->llevarACabo.resultado = EMPATO;
	}else if(personaje1->estadoActual != REA_MAREADO && personaje1->estadoAnterior == REA_MAREADO){
		personaje1->llevarACabo.resultado = PERDIO;
		personaje2->llevarACabo.resultado = GANO;
	}else if(personaje2->estadoActual != REA_MAREADO && personaje2->estadoAnterior == REA_MAREADO){
		personaje1->llevarACabo.resultado = GANO;
		personaje2->llevarACabo.resultado = PERDIO;
	}
}

bool Mundo::huboGanador(){
	if((personaje1->llevarACabo.resultado == GANO)&&
	    personaje1->estadoActual != REA_VICTORIA && personaje1->estadoAnterior == REA_VICTORIA){
		return true;
	}else if((personaje2->llevarACabo.resultado == GANO)&&
			  personaje2->estadoActual != REA_VICTORIA && personaje2->estadoAnterior == REA_VICTORIA){
		return true;
	}
	return false;
}

string Mundo::quienGano() {
	if(personaje1->llevarACabo.resultado == GANO) return personaje1->nombre;
	if(personaje2->llevarACabo.resultado == GANO) return personaje2->nombre;
}


Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libero a los personajes", Log::LOG_DEB);
}

void Mundo::detectarRealiaccionesDeFatalities() {
	if(personaje1->estadoActual == FAT_ARCADE && personaje1->countLoops == 13){
		personaje1->llevarACabo.rectaDelPj.p.x = personaje2->llevarACabo.rectaDelPj.p.x;
		personaje2->reinicializar(REA_FAT_ARCADE);
	}
	if(personaje2->estadoActual == FAT_ARCADE && personaje2->countLoops == 13){
	   personaje2->llevarACabo.rectaDelPj.p.x = personaje1->llevarACabo.rectaDelPj.p.x;
		personaje2->reinicializar(REA_FAT_ARCADE);
	}
	if(personaje2->estadoActual == FAT_ARCADE && personaje2->countLoops == 13) {
		personaje1->llevarACabo.rectaDelPj.p.x = personaje1->rectanguloPj.p.y;
	}
	if(personaje2->estadoActual == FAT_LEVANTA && personaje2->countLoops == 4) {
		personaje1->reinicializar(REA_FAT_LEVANTA);
	}else if(personaje1->estadoActual == FAT_LEVANTA && personaje1->countLoops == 4) {
		personaje2->reinicializar(REA_FAT_LEVANTA);
	}
	if(personaje1->estadoActual == FAT_BRUTALITY_SUBZERO) personaje2->reinicializar(REA_FAT_BRUTALITY_SUBZERO);
	if(personaje2->estadoActual == FAT_BRUTALITY_SUBZERO) personaje1->reinicializar(REA_FAT_BRUTALITY_SUBZERO);
}
