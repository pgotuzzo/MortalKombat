/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#include "../modelo/Personaje.h"

//Suponemos al par ordenado (x,y) como un punto sobre la cabeza de nuestro personaje.
//Por ende este tendria una altura de: (alto de la pantalla - default_pos_Y)
const float Default_pos_Y = 180.0;
const float Default_pos_X = 100.0;
const float Default_Altura_PJ = (200 - Default_pos_Y);
const bool activado = true;


Personaje::Personaje(Posicion posInicial,float alto,float ancho,float nuevoAltoPantalla){
	pos = posInicial;
	alturaDelPersonaje = alto;
	anchoDelPersonaje = ancho;
	accionesEnCurso[0] = new SaltoVertical();
	accionesEnCurso[1] = new Agachar(alturaDelPersonaje, pos.getY() + alturaDelPersonaje);
	accionesEnCurso[2] = new Caminar();
	accionesEnCurso[3] = new SaltoOblicuo(alturaDelPersonaje);
}

/*Personaje::Personaje() {
	pos = Posicion(Default_pos_X,Default_pos_Y);
	alturaDelPersonaje = Default_Altura_PJ;
	//inicializo el vector de acciones
	accionesEnCurso[0] = new SaltoVertical();
	accionesEnCurso[1] = new Agachar(alturaDelPersonaje);
	accionesEnCurso[2] = new Caminar();
	accionesEnCurso[3] = new SaltoOblicuo();
	}*/

void Personaje::ejecutarAcionesActivadas(Accion **accionesEnCurso) {

	pos = accionesEnCurso[1]->realizarAccion(pos);

	if (accionesEnCurso[0]->getEstado()){
		pos = accionesEnCurso[0]->realizarAccion(pos);
		cout<<"Ejecuto accion de salto vertical"<<endl;
	}

	if (accionesEnCurso[2]->getEstado()){
		cout<<"ejecuto accion de caminar"<<endl;
		pos = accionesEnCurso[2]->realizarAccion(pos);
	}
	if (accionesEnCurso[3]->getEstado()){
		cout<<"Ejecuto accion de salto oblicuo"<<endl;
		pos = accionesEnCurso[3]->realizarAccion(pos);
	}
}


void Personaje::realizarAccion(int orden){
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
						accionesEnCurso[2]->setEstado(activado,true);
						cout << "CAMINA A LA DERECHA!" << endl;
						}
					break;
				//Caminar a la izquierda
				case (4):
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						accionesEnCurso[2]->setEstado(activado,false);
						cout << "CAMINA A LA IZQUIERDA!"<<endl;
						}
					break;
				//Salto oblicuo a la derecha
				case (5):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						accionesEnCurso[3]->setEstado(activado, pos,true);
						cout << "SALTO OBLICUAMENTE PARA LA DERECHA!"<<endl;
						}
					break;

				//Salto oblicuo a la izquierda
				case (6):
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						accionesEnCurso[3]->setEstado(activado, pos, false);
						cout << "SALTO OBLICUAMENTE PARA LA IZQUIERDA!"<<endl;
					}
					break;
				default:
					break;
			}
		}
	}

	ejecutarAcionesActivadas(accionesEnCurso);
	//Este metodo va a ejecutar las acciones que este listas para ejecutarse
	//Cada accion se desactiva cuando termina.

	cout<<"Ya se ejecutaron las accion durante un game loop"<<endl;
}




Posicion Personaje::getPosicion(){
	return pos;
}




Personaje::~Personaje() {

}

