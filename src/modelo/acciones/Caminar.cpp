#include "Caminar.h"


// CAMINAR tiene la particularidad de durar un solo gameloop por lo tanto se desactiva en el mismo
// gameloop que se activo. Para que quede siempre activado se debe mantener presionada la tecla.
using namespace std;

// Constante para regular la accion caminar
const float ancho_paso = 2;


/*
 * El estado es necesario para que no se haga otra accion cuando se camine mas de un gameloop.
 */
Caminar::Caminar() {
	estado = false;
	direccion = true; // se la define para que camine a la derecha, igual despues se setea.
	this->anchoDePaso = ancho_paso;
}

void Caminar::setAnchoDePaso(float nuevoAnchoDePaso) {
	this->anchoDePaso = nuevoAnchoDePaso;
}


void Caminar::setAnchoDePasoDefault() {
	this->anchoDePaso = ancho_paso;
}
/*
 * Se setea la direccion para caminar y el estado.
 */
void Caminar::setEstado(bool nuevoEstado,bool nuevaDireccion){
	direccion = nuevaDireccion;
	estado = nuevoEstado;
}

void Caminar::setEstado(bool nuevoEstado) {
	estado = nuevoEstado;
}

bool Caminar::getEstado(){
	return estado;
}

/*
 * Se realiza la accion de caminar.
 */
Posicion Caminar::realizarAccion(Posicion pos){
	Posicion p = Posicion(anchoDePaso, 0);
	if (direccion) {
		estado = false;
		return pos + p;
	}
	estado = false;
	return pos - p;
}

Posicion Caminar::realizarAccion(Posicion pos, bool dir) {
	if (dir) {
		Posicion posAux;
		Posicion p = Posicion(0, 0);
		if (direccion) {
			estado = false;
			posAux = pos+p;
			cout<<"Derecha"<<endl;
			posAux.mostrarPar();
			return posAux;
		}
		estado = false;
		posAux = pos-p;
		cout<<"Izquierda"<<endl;
		posAux.mostrarPar();
		return posAux;
	}
}

Caminar::~Caminar() {
}

