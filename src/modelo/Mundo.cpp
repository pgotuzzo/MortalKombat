#include "../parser/config.h"
#include "Mundo.h"


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

	personaje1 = new Personaje(dir,Posicion(pos_x+anchoPJ,pos_y),altoPJ,anchoPJ, altoEscenario);
	personaje2 = new Personaje(dir,Posicion(pos_x-anchoPJ,pos_y),altoPJ,anchoPJ, altoEscenario);

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

	personaje1->realizarAccion(inputs[0],anchoEscenario);
	personaje2->realizarAccion(inputs[1],anchoEscenario);
	cambio1.posicion = personaje1->getPosicion();
	if(personaje1->getDireccion()) cambio1.direccion = DERECHA;
	else cambio1.direccion = IZQUIERDA;
	if(personaje1->getSentido()) cambio1.sentido = ADELANTE;
	else cambio1.sentido = ATRAS;
	cambio1.estado = personaje1->getEstado();
	cambio1.dPJ.h = personaje1->getAlturaPersonaje();
	cambio1.dPJ.w = personaje1->getAnchoPersonaje();

	cambio2.posicion = personaje2->getPosicion();
	cambio2.estado = personaje2->getEstado();
	cambio2.dPJ.h = personaje2->getAlturaPersonaje();
	cambio2.dPJ.w = personaje2->getAnchoPersonaje();
	if(personaje2->getDireccion()) cambio2.direccion = DERECHA;
	else cambio2.direccion = IZQUIERDA;
	if(personaje2->getSentido()) cambio2.sentido = ADELANTE;
	else cambio2.sentido = ATRAS;

	c.push_back(cambio1);
	c.push_back(cambio2);

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libera al personaje", Log::LOG_DEB);
}

