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
	personaje2 = new Personaje(!dir,Posicion(pos_x+50,pos_y),altoPJ,anchoPJ,altoEscenario);

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


void Mundo::actualizarPersonaje(Tcambio* c, Personaje *personaje) {
	c->posicion = personaje->getPosicion();
	if(personaje->getDireccion()) c->direccion = DERECHA;
	else c->direccion = IZQUIERDA;
	if(personaje->getSentido()) c->sentido = ADELANTE;
	else c->sentido = ATRAS;
	c->estado = personaje->getEstado();
	c->alturaPJ = personaje->getAlturaPersonaje();
	c->anchoPJ = personaje->getAnchoPersonaje();

}
/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
Tcambio Mundo::actualizarMundo(Tcambio c,Tinput input1,Tinput input2){
	personaje1->realizarAccion(input1,anchoEscenario);
	actualizarPersonaje(&c,personaje1);
	personaje2->realizarAccion(input2,anchoEscenario);
	//actualizarPersonaje(&c,personaje2);

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
}

