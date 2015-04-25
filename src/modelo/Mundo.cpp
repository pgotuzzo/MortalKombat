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

	anchoEscenario = escenario.ancho;
	altoEscenario = escenario.alto;
	altoPiso = escenario.yPiso;

	float altoPJ = pj.alto;
	float anchoPJ = pj.ancho;

	float pos_x = anchoEscenario/2;
	float pos_y = altoEscenario - altoPiso - altoPJ;
	float distanciaMaxima = configuracion.getVentana().ancho -((MIN_DISTANCE_FROM_BOUND*2)-1);


	Tdireccion direccion = configuracion.getPersonaje().orientacion;

	bool dir;

	if (direccion == DERECHA) dir = true;
	else dir = false;

	personaje1 = new Personaje(dir,Posicion(pos_x+anchoPJ,pos_y),altoPJ,anchoPJ, altoEscenario, distanciaMaxima);
	personaje2 = new Personaje(dir,Posicion(pos_x-anchoPJ,pos_y),altoPJ,anchoPJ, altoEscenario, distanciaMaxima);

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
Tcambios Mundo::actualizarMundo(Tinputs inputs) {
	Tcambios c;
	personaje1->realizarAccion(inputs.input1,anchoEscenario);
	personaje2->realizarAccion(inputs.input2,anchoEscenario);
	c.cambio1.posicion = personaje1->getPosicion();
	if(personaje1->getDireccion()) c.cambio1.direccion = DERECHA;
	else c.cambio1.direccion = IZQUIERDA;
	if(personaje1->getSentido()) c.cambio1.sentido = ADELANTE;
	else c.cambio1.sentido = ATRAS;
	c.cambio1.estado = personaje1->getEstado();
	c.cambio1.alturaPJ = personaje1->getAlturaPersonaje();
	c.cambio1.anchoPJ = personaje1->getAnchoPersonaje();

	c.cambio2.posicion = personaje2->getPosicion();
	c.cambio2.estado = personaje2->getEstado();
	c.cambio2.alturaPJ = personaje2->getAlturaPersonaje();
	c.cambio2.anchoPJ = personaje2->getAnchoPersonaje();
	if(personaje2->getDireccion()) c.cambio2.direccion = DERECHA;
	else c.cambio2.direccion = IZQUIERDA;
	if(personaje2->getSentido()) c.cambio2.sentido = ADELANTE;
	else c.cambio2.sentido = ATRAS;

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libera al personaje", Log::LOG_DEB);
}

