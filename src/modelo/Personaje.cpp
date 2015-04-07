
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
	estado = PARADO;
	pos = posInicial;
	alturaDelPersonaje = alto;
	anchoDelPersonaje = ancho;
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


Posicion Personaje::verificarPunto(Posicion posicionActual,float anchoEscenario){
	if (posicionActual.getX() > anchoEscenario){
		return Posicion(anchoEscenario, posicionActual.getY());
	}
	if (posicionActual.getX() < 0){
		return Posicion(0,posicionActual.getY());
	}
	else return posicionActual;
}


void Personaje::ejecutarAcionesActivadas(Accion **accionesEnCurso,float anchoEscenario) {

	pos = accionesEnCurso[1]->realizarAccion(pos);
	estado = AGACHADO;

	if (accionesEnCurso[0]->getEstado()){
		pos = accionesEnCurso[0]->realizarAccion(pos);
		estado = SALTANDO_VERTICAL;
		cout<<"Ejecuto accion de salto vertical"<<endl;
	}

	if (accionesEnCurso[2]->getEstado()){
		cout<<"ejecuto accion de caminar"<<endl;
		pos = verificarPunto(accionesEnCurso[2]->realizarAccion(pos),anchoEscenario);
		estado = CAMINANDO;


	}
	if (accionesEnCurso[3]->getEstado()){
		cout<<"Ejecuto accion de salto oblicuo"<<endl;
		pos = verificarPunto(accionesEnCurso[3]->realizarAccion(pos),anchoEscenario);
		estado = SALTANDO_OBLICUO;
	}
}


void Personaje::realizarAccion(int orden,float anchoEscenario){
	if (!accionesEnCurso[0]->getEstado()){
		if(!accionesEnCurso[3]->getEstado()){
			switch (orden){
				//Saltar
				case (1):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar verticalmente
						accionesEnCurso[0]->setEstado(activado,pos);
						cout<< "SALTA"<<endl;
					}
					break;
				//Agachar
				case (2):
					//activo el estado de agachar
					accionesEnCurso[1]->setEstado(activado,pos);
					cout << "SE AGACHA!"<<endl;
					break;

				//Caminar a la derecha
				case (3):
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						direccion = true;
						accionesEnCurso[2]->setEstado(activado,true);
						cout << "CAMINA A LA DERECHA!" << endl;
						}
					break;
				//Caminar a la izquierda
				case (4):
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						direccion = false;
						accionesEnCurso[2]->setEstado(activado,false);
						cout << "CAMINA A LA IZQUIERDA!"<<endl;
						}
					break;
				//Salto oblicuo a la derecha
				case (5):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						direccion = true;
						accionesEnCurso[3]->setEstado(activado, pos,true);
						cout << "SALTO OBLICUAMENTE PARA LA DERECHA!"<<endl;
						}
					break;

				//Salto oblicuo a la izquierda
				case (6):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						direccion = false;
						accionesEnCurso[3]->setEstado(activado, pos, false);
						cout << "SALTO OBLICUAMENTE PARA LA IZQUIERDA!"<<endl;
					}
					break;
				default:
					break;
			}
		}
	}

	ejecutarAcionesActivadas(accionesEnCurso,anchoEscenario);
	//Este metodo va a ejecutar las acciones que este listas para ejecutarse
	//Cada accion se desactiva cuando termina.

	cout<<"Ya se ejecutaron las accion durante un game loop"<<endl;
}


TestadoPersonaje Personaje::getEstado() {
	/*bool activadoSaltoVertical = accionesEnCurso[0]->getEstado();
	bool activadoAgachar = accionesEnCurso[1]->getEstado();
	bool activadoCaminar = accionesEnCurso[2]->getEstado();
	bool activadoSaltoOblicuo = accionesEnCurso[3]->getEstado();

	if ( (!activadoSaltoVertical) && (!activadoAgachar) && (!activadoCaminar) && (!activadoSaltoOblicuo)){
		estado = PARADO;
	}*/
	return estado;
}



Posicion Personaje::getPosicion(){
	return pos;
}




Personaje::~Personaje() {
	int i;
	for (i = 0;i<4;i++){
		delete accionesEnCurso[i];
	}

}

