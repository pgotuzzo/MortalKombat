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

	personaje1 = new Personaje(Posicion(pos_x,pos_y),altoPJ,anchoPJ, altoEscenario);

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

Posicion Mundo::actualizarMundo(int orden){
	personaje1->realizarAccion(orden,anchoEscenario);
	return personaje1->getPosicion();
}

Mundo::~Mundo() {
	// TODO Auto-generated destructor stub
}

