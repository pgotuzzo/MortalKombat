/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: miguel
 */

#include "../modelo/Personaje.h"


const float Default_pos_Y = 50.0;
const float Default_pos_X = 50.0;
const bool activado = true;


Personaje::Personaje() {
	pos = Posicion(Default_pos_X,Default_pos_Y);
	//inicializo el vector de acciones
	accionesEnCurso[0] = new SaltoVertical();
	accionesEnCurso[1] = new Agachar();
	accionesEnCurso[2] = new Caminar();
	accionesEnCurso[3] = new SaltoOblicuo();
	}

void Personaje::ejecutarAcionesActivadas(Accion **accionesEnCurso) {
	if (accionesEnCurso[0]->getEstado()){
		pos = accionesEnCurso[0]->realizarAccion(pos);
		cout<<"Ejecuto accion de salto vertical"<<endl;
	}
	if (accionesEnCurso[1]->getEstado()){
		cout<<"ejecuto accion de agacharse"<<endl;
		pos = accionesEnCurso[1]->realizarAccion(pos);
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

	switch (orden){
		//Saltar
		case (1):
				//No puede saltar mientras esta saltando verticalmente
				if (!accionesEnCurso[0]->getEstado()){
					if(!accionesEnCurso[3]->getEstado()){
					//No puede saltar si esta agachado oblicuamente
						if(!accionesEnCurso[1]->getEstado()){
							//Activo el estado de saltar verticalmente
							accionesEnCurso[0]->setEstado(activado,pos);
							cout<< "SALTA"<<endl;
						}
					}
				}
				break;
		//Agachar
		case (2):
			//No te podes agachar mientras estas saltando verticalmente
			if (!accionesEnCurso[0]->getEstado()){
				//No te podes agachar mientras estas saltando oblicuamente
				if(!accionesEnCurso[3]->getEstado()){
					//activo el estado de agachar
					accionesEnCurso[1]->setEstado(activado,pos);
					cout << "SE AGACHA!"<<endl;
				}
			}
				break;

		//Caminar a la derecha
		case (3):
			//No podes avanzar mientras estas saltando verticalmente
			if (!accionesEnCurso[0]->getEstado()){
				//No podes avanzar mientras estas saltando oblicuamente
				if(!accionesEnCurso[3]->getEstado()){
					//No puede avanzar si esta agachado
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						accionesEnCurso[2]->setEstado(activado,true);
						cout << "CAMINA A LA DERECHA!" << endl;
					}
				}
			}
			break;
		case (4):
				//Caminar a la izquierda
			//No podes avanzar mientras estas saltando verticalmente
			if (!accionesEnCurso[0]->getEstado()){
				//No podes avanzar mientras estas saltando oblicuamente
				if(!accionesEnCurso[3]->getEstado()){
					if(!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						accionesEnCurso[2]->setEstado(activado,false);
						cout << "CAMINA A LA IZQUIERDA!"<<endl;
					}
				}
			}
			break;

		case (5):
			//No puede saltar oblicuamente mientras esta saltando verticalmente
			if (!accionesEnCurso[0]->getEstado()){
				//No puede saltar oblicuamente si esta saltando oblicuamente
				if(!accionesEnCurso[3]->getEstado()){
					//No se puede saltar oblicuamente mientras se esta agachado
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						accionesEnCurso[3]->setEstado(activado, pos,true);
						cout << "SALTO OBLICUAMENTE PARA LA DERECHA!"<<endl;
					}
				}
			}
			break;

		//Salto oblicuo a la izquierda
		case (6):
			//No puede saltar oblicuamente mientras esta saltando verticalmente
			if (!accionesEnCurso[0]->getEstado()){
				//No puede saltar oblicuamente si esta saltando oblicuamente
				if(!accionesEnCurso[3]->getEstado()){
					//No se puede saltar oblicuamente mientras se esta agachado
					if(!accionesEnCurso[1]->getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						accionesEnCurso[3]->setEstado(activado, pos, false);
						cout << "SALTO OBLICUAMENTE PARA LA IZQUIERDA!"<<endl;
					}
				}
			}
			break;

		default:
			break;
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

