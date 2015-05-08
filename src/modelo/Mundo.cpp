#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const float delta = 5.00;
const float deltaLejania = 80;
const float deltaCero = 0;
const float deltaParaPelea = 25.00;
const float deltaParaPoder = 5.00;

/* Constructor de Mundo.
 * Recibe la configuracion que se devuelve del parser.
 * Crea un personaje e inicializa su posicion, altura y ancho.
 * Tambien se inicializa el alto, ancho y yPiso del escenario.

 */
Mundo::Mundo(config configuracion) {
	Tescenario escenario = configuracion.getEscenario();
	Tpersonaje pj = configuracion.getPersonaje();

	anchoEscenario = escenario.d.w;
	altoEscenario = escenario.d.h;
	altoPiso = escenario.yPiso;

	float altoPJ = pj.d.h;
	float anchoPJ = pj.d.w;

	float pos_x = anchoEscenario/2;
	float pos_y = altoEscenario - altoPiso - altoPJ;

	Tdireccion direccion = configuracion.getPersonaje().orientacion;

	bool dir;

	if (direccion == DERECHA) dir = true;
	else dir = false;

	//TODO: EL PJ1 Y PJ2 EMPIEZAN EN LADOS OPUESTOS - lo dejamos asi por los controles del teclado

	personaje1 = new Personaje(dir,Posicion(pos_x+anchoPJ,pos_y),altoPJ,anchoPJ);
	cout<<"Costado izquierdo personaje 1: "<<personaje1->pos.getX() - personaje1->ancho/2<<endl;
	personaje2 = new Personaje(dir,Posicion(pos_x-anchoPJ,pos_y),altoPJ,anchoPJ);
	cout<<"Costado derecho personaje 2: "<<personaje2->pos.getX() + personaje2->ancho/2<<endl;
	colisionador = Colisionador();
	colisionador.setEscenario(anchoEscenario);
	anchoPantalla = configuracion.getVentana().ancho;
}


Personaje* Mundo::getPersonaje(){
	return personaje1;
}

float Mundo::getAlto(){
	return altoEscenario;
}

float Mundo::getAncho(){
	return anchoEscenario;
}

float Mundo::getAltoPiso(){
	return altoPiso;
}

/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
vector<Tcambio> Mundo::actualizarMundo(vector<Tinput> inputs) {
	vector<Tcambio> c;
	Tcambio cambio1, cambio2;

	//Verifica y da vuelta la direccion de los personajes si se pasan
	verificarDireccionDeLosPersonajes();

	//Choque de saltos oblicuos en el aire
	if(!colisionador.detectarLejania(personaje1,personaje2,anchoPantalla-deltaLejania))verificarQueNoSeVallaDeLaPantalla();
	else VerificarSiPjsColisionanaEnElAire();

	// Los personajes realizan sus acciones
	personaje1->realizarAccion(inputs[0],anchoEscenario);
	personaje2->realizarAccion(inputs[1],anchoEscenario);

	personaje1->accionesEnCurso[2]->setAnchoDePasoDefault();
	personaje2->accionesEnCurso[2]->setAnchoDePasoDefault();

	//Colision entre personajes (empujar)
	if (colisionador.sonProximos(personaje1,personaje2,-1)){
		colisionador.solucionarColision(personaje1,personaje2);
		colisionador.solucionarColision(personaje2,personaje1);
	}

	//Colision entre el personaje y el golpe
	bool esPoder = true;
	verificarColision(personaje2->lanzandoGolpe,personaje1,personaje2->golpe,!esPoder);
	string mensajePJ1 = "Vida del personaje 1: " + to_string(personaje1->vida);
	if(personaje1->vida < 100 && personaje1->vida > 0)loguer->loguear(mensajePJ1.c_str(),Log::LOG_DEB);
	verificarColision(personaje1->lanzandoGolpe,personaje2,personaje1->golpe,!esPoder);
	string mensajePJ2 = "Vida del personaje 2: " + to_string(personaje2->vida);
	if(personaje2->vida < 100 && personaje2->vida > 0)loguer->loguear(mensajePJ2.c_str(),Log::LOG_DEB);

	//Colision entre el personaje y el poder
	if(personaje1->lanzandoPoder) {
		cout<<"personaje que lanza el poder"<<endl;
		personaje1->pos.mostrarPar();
	}
	if(personaje2->lanzandoPoder) {
		cout<<"personaje que lanza el poder"<<endl;
		personaje2->pos.mostrarPar();
	}
	verificarColision(personaje2->lanzandoPoder,personaje1,personaje2->poder,esPoder);
	verificarColision(personaje1->lanzandoPoder,personaje2,personaje1->poder,esPoder);

	//Se actualizan a los personajes
	cambio1 = actualizarPJ(personaje1);
	cambio2 = actualizarPJ(personaje2);
	c.push_back(cambio1);
	c.push_back(cambio2);

	return c;
}


void Mundo::verificarColision(bool generaViolencia, Personaje *PJ, ObjetoColisionable *objeto, bool esPoder) {
	if (generaViolencia) {
		if (colisionador.sonProximos(PJ,objeto,2)) {
			if (esPoder) {
				cout<<"Personaje que recibe el poder"<<endl;
				PJ->pos.mostrarPar();
				colisionador.solucionarColision(PJ, (Poder *) objeto);
			}
			else colisionador.solucionarColision(PJ, (Golpe *) objeto);
		}
	}
}

Tcambio Mundo::actualizarPJ(Personaje *PJ) {
	Tcambio cambio;
	cambio.posicion = PJ->getPosicion();
	if(PJ->getDireccion()) cambio.direccion = DERECHA;
	else cambio.direccion = IZQUIERDA;
	if(PJ->getSentido()) cambio.sentido = ADELANTE;
	else cambio.sentido = ATRAS;
	cambio.estado = PJ->getEstado();
	cambio.dPJ.h = PJ->getAlturaPersonaje();
	cambio.dPJ.w = PJ->getAnchoPersonaje();

	return cambio;

}

Mundo::~Mundo() {
	if(personaje1->vida == 0) loguer->loguear("El personaje 1 esta muerto",Log::LOG_DEB);
	else loguer->loguear("El personaje 1 sobrevivio",Log::LOG_DEB);
	if(personaje2->vida == 0) loguer->loguear("El personaje 2 esta muerto",Log::LOG_DEB);
	else loguer->loguear("El personaje 2 sobrevivio",Log::LOG_DEB);
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libero a los personajes", Log::LOG_DEB);
}

void Mundo::verificarDireccionDeLosPersonajes() {
	//direccion derecha igual true
	if(personaje1->pos.getX() - personaje2->pos.getX() <= 0){
		personaje1->setDireccion(true);
		personaje2->setDireccion(false);

	}	else{
		personaje1->setDireccion(false);
		personaje2->setDireccion(true);
	}
}

void Mundo::VerificarSiPjsColisionanaEnElAire(){
	if ((personaje1->getEstado() != SALTANDO_OBLICUO) || (personaje1->sentido == false)) {
		personaje1->enCaida = false;
	}
	if ((personaje2->getEstado() != SALTANDO_OBLICUO) || (personaje2->sentido == false)) {
		personaje2->enCaida = false;
	}
	if (personaje1->estado == SALTANDO_OBLICUO && personaje1->sentido == true && personaje2->estado == SALTANDO_OBLICUO && personaje2->sentido == true) {
		if (colisionador.seVan(personaje1, personaje2, deltaCero)) {
			personaje1->enCaida = true;
			personaje2->enCaida = true;
		}
	}


}



void Mundo::verificarQueNoSeVallaDeLaPantalla() {

	// No se vayan caminando
	if(!colisionador.detectarLejania(personaje1,personaje2,anchoPantalla -(MIN_DISTANCE_FROM_BOUND*4))){
		if(personaje1->estado == CAMINANDO){
			if(personaje1->direccion) personaje1->pos = Posicion(personaje1->pos.getX()+2,personaje1->pos.getY());
			else personaje1->pos = Posicion(personaje1->pos.getX()-2,personaje1->pos.getY());
		}
		if(personaje2->estado == CAMINANDO){
			if(personaje2->direccion) personaje2->pos = Posicion(personaje2->pos.getX()+2,personaje2->pos.getY());
			else personaje2->pos = Posicion(personaje2->pos.getX()-2,personaje2->pos.getY());

		}
	}
	//No se vayan saltando oblicuamente
	if(personaje1->estado == SALTANDO_OBLICUO) {
		if (((!personaje1->getSentido())&&(personaje1->getDireccion()))||
			((!personaje1->getSentido())&&(!personaje1->getDireccion())))
			personaje1->enCaida = true;
	}else personaje1->enCaida = false;
	if(personaje2->estado == SALTANDO_OBLICUO) {
		if (((!personaje2->getSentido())&&(personaje2->getDireccion()))||
			((!personaje2->getSentido())&&(!personaje2->getDireccion())))
			personaje2->enCaida = true;
	}else personaje2->enCaida = false;


}
