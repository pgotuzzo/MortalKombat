#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const int tiempoInicialRound = 99;

/* Constructor de Mundo.
 * Recibe la configuracion que se devuelve del parser.
 * Crea un personaje e inicializa su posicion, altura y ancho.
 * Tambien se inicializa el alto, ancho y yPiso del escenario.

 */
Mundo::Mundo(config configuracion) {
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

	personaje1 = new Personaje(PJ1.nombre,direccion1,rectanguloPj1,anchoVentana);
	personaje2 = new Personaje(PJ2.nombre,direccion2,rectanguloPj2,anchoVentana);

	colisionador = DetectorDeColisiones(anchoVentana,anchoEscenario);

	anchoPantalla = configuracion.getVentana().ancho;

	roundsPJ1 = roundsPJ2 = 0;

	tiempoRound = tiempoInicialRound;

	tiempoInicial = SDL_GetTicks();
}

void Mundo::verificarDireccionDeLosPersonajes() {
	//direccion derecha igual true
	//TODO: ESTO DEBERIA ANDAR AL REVEZ, PERO NO ME ANDA. VER DESPUES
	//osea pidiendo que el estado actual sea diferente de la accion y la reaccion agarre
	// para que haga el cambio de direccion
	if(personaje1->estadoActual == ACC_AGARRE || personaje1->estadoActual == REA_AGARRE) {
		cout<<"No entro"<<endl;
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

	return cambio;
}

/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
vector<Tcambio> Mundo::actualizarMundo(vector<Tinput> inputs) {
	vector<Tcambio> c;
	Tcambio cambio1, cambio2;

	verificarGanadorDelRound();
	Uint32 tiempo = SDL_GetTicks();
	//cout<<tiempoInicial<<"----"<<tiempo<<endl;d
	if(SDL_TICKS_PASSED(tiempo, tiempoInicial + 1000)) {
		tiempoInicial = tiempo;
		tiempoRound--;
	}


	//Verifica y da vuelta la direccion de los personajes si se pasan
	verificarDireccionDeLosPersonajes();


	// Los personajes realizan sus acciones
	personaje1->realizarAccion(inputs[1]);
	personaje2->realizarAccion(inputs[0]);
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
	return roundsPJ1 == 2 || roundsPJ2 == 2;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libero a los personajes", Log::LOG_DEB);
}

void Mundo::verificarGanadorDelRound() {
	string mensaje;
	mensaje = "Ganador Round N°" + to_string(roundsPJ1 + roundsPJ2) + ": ";
	if(tiempoRound >= 0) {
		if (personaje1->vida == 0) {
			mensaje = mensaje + personaje2->nombre + " ---> Personaje 2";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			personaje1->reinicializar();
			personaje2->reinicializar();
			roundsPJ1++;
			tiempoRound = tiempoInicialRound;
		}
		else {
			if (personaje2->vida == 0) {
				mensaje = mensaje + personaje1->nombre + " ---> Personaje 1";
				loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
				personaje1->reinicializar();
				personaje2->reinicializar();
				roundsPJ2++;
				tiempoRound = tiempoInicialRound;
			}
		}
	}
	else{
		if (personaje1->vida == personaje2->vida) {
			loguer->loguear("EMPATARONNNN", Log::LOG_DEB);
			personaje1->reinicializar();
			personaje2->reinicializar();
			roundsPJ1++;
			tiempoRound = tiempoInicialRound;
		}
		else if(personaje1->vida > personaje2->vida){
			mensaje = mensaje + personaje1->nombre + " ---> Personaje 1";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			personaje1->reinicializar();
			personaje2->reinicializar();
			roundsPJ2++;
			tiempoRound = tiempoInicialRound;
		}
		else{
			mensaje = mensaje + personaje2->nombre + " ---> Personaje 2";
			loguer->loguear(mensaje.c_str(), Log::LOG_DEB);
			personaje1->reinicializar();
			personaje2->reinicializar();
			roundsPJ2++;
			tiempoRound = tiempoInicialRound;
		}
	}
}