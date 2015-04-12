
//Suponemos al par ordenado (x,y) como un punto sobre la cabeza de nuestro personaje.


#include "Personaje.h"
#include "acciones/SaltoVertical.h"
#include "acciones/Agachar.h"
#include "acciones/Caminar.h"
#include "acciones/SaltoOblicuo.h"

const bool activado = true;


Personaje::Personaje(bool orientacion,Posicion posInicial,float alto,float ancho,float nuevoAltoEscenario){
	this->orientacion = orientacion;
	this->direccion = true;
	parado = true;
	estado = PARADO;
	pos = posInicial;
	alturaDelPersonaje = alto;
	anchoDelPersonaje = ancho;
	altoEscenario = nuevoAltoEscenario;
	yPiso = alturaDelPersonaje + pos.getY();
	accionesEnCurso[0] = new SaltoVertical();
	accionesEnCurso[1] = new Agachar(&alturaDelPersonaje, pos.getY() + alturaDelPersonaje);
	accionesEnCurso[2] = new Caminar();
	accionesEnCurso[3] = new SaltoOblicuo(alturaDelPersonaje);
}

bool Personaje::getDireccion() {
	return direccion;
}

bool Personaje::getOrientacion() {
	return orientacion;
}
Posicion Personaje::verificarPuntoEnY(Posicion posicionActual){
	cout<<yPiso<<endl;
	if(posicionActual.getY()+alturaDelPersonaje >= yPiso){
		return Posicion(posicionActual.getX(),yPiso-alturaDelPersonaje);
	}
	return posicionActual;

}

Posicion Personaje::verificarPuntoEnX(Posicion posicionActual,float anchoEscenario){
	if (posicionActual.getX() > anchoEscenario - anchoDelPersonaje){
		return Posicion(anchoEscenario - anchoDelPersonaje, posicionActual.getY());
	}
	if (posicionActual.getX() < 1){
		return Posicion(1,posicionActual.getY());
	}
	else return posicionActual;
}


void Personaje::ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario) {

	pos = accionesEnCurso[1]->realizarAccion(pos);

	if (accionesEnCurso[0]->getEstado()){
		pos = verificarPuntoEnY(accionesEnCurso[0]->realizarAccion(pos));
	}

	if (accionesEnCurso[2]->getEstado()){
		//cout<<"ejecuto accion de caminar"<<endl;
		pos = verificarPuntoEnX(accionesEnCurso[2]->realizarAccion(pos),anchoEscenario);

	}
	if (accionesEnCurso[3]->getEstado()){
		//cout<<"Ejecuto accion de salto oblicuo"<<endl;
		pos = verificarPuntoEnX(accionesEnCurso[3]->realizarAccion(pos),anchoEscenario);
	}
}


void Personaje::realizarAccion(int orden,float anchoEscenario){
	if (!accionesEnCurso[0]->getEstado()){
		if(!accionesEnCurso[3]->getEstado()){
			switch (orden){
				//Parado
				case(0):
					if(!accionesEnCurso[1]->getEstado()){
						parado=true;
						estado = PARADO;
					}
					break;
				//Saltar
				case (1):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar verticalmente
						accionesEnCurso[0]->setEstado(activado,pos);
						estado = SALTANDO_VERTICAL;
						parado=false;
						//cout<< "SALTA"<<endl;
					}
					break;
				//Agachar
				case (2):
					//activo el estado de agachar
					accionesEnCurso[1]->setEstado(activado,pos);
					estado = AGACHADO;
					parado=false;
					//cout << "SE AGACHA!"<<endl;
					break;

				//Caminar a la derecha
				case (3):
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						direccion = true;
						accionesEnCurso[2]->setEstado(activado,true);
						estado = CAMINANDO;
						parado=false;
						//cout << "CAMINA A LA DERECHA!" << endl;
						}
					break;
				//Caminar a la izquierda
				case (4):
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						direccion = false;
						accionesEnCurso[2]->setEstado(activado,false);
						estado = CAMINANDO;
						parado=false;
						//cout << "CAMINA A LA IZQUIERDA!"<<endl;
						}
					break;
				//Salto oblicuo a la derecha
				case (5):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						direccion = true;
						accionesEnCurso[3]->setEstado(activado, pos,true);
						estado = SALTANDO_OBLICUO;
						parado=false;
						//cout << "SALTO OBLICUAMENTE PARA LA DERECHA!"<<endl;
						}
					break;

				//Salto oblicuo a la izquierda
				case (6):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						direccion = false;
						accionesEnCurso[3]->setEstado(activado, pos, false);
						estado = SALTANDO_OBLICUO;
						parado=false;
						//cout << "SALTO OBLICUAMENTE PARA LA IZQUIERDA!"<<endl;
					}
					break;
				default:
					estado = PARADO;
					break;
			}
		}
	}

	ejecutarAcionesActivadas(accionesEnCurso,anchoEscenario);
	//Este metodo va a ejecutar las acciones que este listas para ejecutarse
	//Cada accion se desactiva cuando termina.
}


TestadoPersonaje Personaje::getEstado() {
	if(parado) return PARADO;
	return estado;
}



Posicion Personaje::getPosicion(){
	return pos;
}

float Personaje::getAlturaPersonaje() {
	if (accionesEnCurso[3]->getEstado()) return alturaDelPersonaje/2;
	return alturaDelPersonaje;
}

float Personaje::getAnchoPersonaje() {
	return anchoDelPersonaje;
}


Personaje::~Personaje() {
	int i;
	for (i = 0;i<4;i++){
		delete accionesEnCurso[i];
	}

}
