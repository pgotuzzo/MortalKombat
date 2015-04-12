#include "../parser/config.h"
#include "Mundo.h"

Mundo::Mundo(config configur) {
	Tescenario escenario = configur.getEscenario();
	Tpersonaje pj = configur.getPersonaje();

	anchoEscenario = escenario.ancho;
	altoEscenario = escenario.alto;
	altoPiso = escenario.yPiso;

	float altoPJ = pj.alto;
	float anchoPJ = pj.ancho;

	float pos_x = anchoEscenario/2;
	float pos_y = altoEscenario - altoPiso - altoPJ;

	bool orientacion = true; // agregar en el parser el get orientacion y cambiar esto

	personaje1 = new Personaje(orientacion,Posicion(pos_x,pos_y),altoPJ,anchoPJ, altoEscenario);

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

Tcambio Mundo::actualizarMundo(Tcambio c,int orden){
	personaje1->realizarAccion(orden,anchoEscenario);
	c.posicion = personaje1->getPosicion();
	if(personaje1->getOrientacion()) c.direccion = DERECHA;
	else c.direccion = IZQUIERDA;
	if(personaje1->getDireccion()) c.sentido = ADELANTE;
	else c.sentido = ATRAS;
	c.estado = personaje1->getEstado();
	c.alturaPJ = personaje1->getAlturaPersonaje();
	c.anchoPJ = personaje1->getAnchoPersonaje();

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
}

