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

	float pos_x1 = anchoEscenario/2 - anchoPJ;
	float pos_x2 = anchoEscenario/2 + anchoPJ;
	float pos_y = altoEscenario - altoPiso - altoPJ;

	anchoVentana = configuracion.getVentana().ancho;
	float distanciaMaximaPJs = anchoVentana - 4 * anchoPJ;

	Tdireccion direccion = configuracion.getPersonaje().orientacion;

	bool dir;

	if (direccion == DERECHA) dir = true;
	else dir = false;

	personaje1 = new Personaje(dir,Posicion(pos_x1,pos_y),altoPJ,anchoPJ, altoEscenario,distanciaMaximaPJs);
	personaje2 = new Personaje(!dir,Posicion(pos_x2,pos_y),altoPJ,anchoPJ,altoEscenario,distanciaMaximaPJs);

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

// TODO: Verificar logica sentido y terminar de verificar cuando se tiene que dar vuelta el pj
Tcambio Mundo::actualizarMundo(Tcambio c,Tinput input1,Tinput input2){
	personaje1->realizarAccion(input1,anchoEscenario);
	personaje2->realizarAccion(input2,anchoEscenario);
	personaje1->direccion = verificarDireccion(personaje1->pos,personaje2->pos);
	personaje2->direccion = !personaje1->direccion;
	actualizarPersonaje(&c,personaje1);
	//actualizarPersonaje(&c,personaje2);

	return c;
}

bool Mundo::verificarDireccion(Posicion posPJ1, Posicion posPJ2) {
	if (posPJ1.getX() <= posPJ2.getX()) return true;
	else return false;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
}

