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

	Tdireccion direccion = configuracion.getPersonaje().orientacion;

	bool dir;

	if (direccion == DERECHA) dir = true;
	else dir = false;

	personaje1 = new Personaje(dir,Posicion(pos_x,pos_y),altoPJ,anchoPJ, altoEscenario);

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
Tcambio Mundo::actualizarMundo(Tcambio c,Tinput input){
	personaje1->realizarAccion(input,anchoEscenario);
	c.posicion = personaje1->getPosicion();
	if(personaje1->getDireccion()) c.direccion = DERECHA;
	else c.direccion = IZQUIERDA;
	if(personaje1->getSentido()) c.sentido = ADELANTE;
	else c.sentido = ATRAS;
	c.estado = personaje1->getEstado();
	c.alturaPJ = personaje1->getAlturaPersonaje();
	c.anchoPJ = personaje1->getAnchoPersonaje();

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
}

