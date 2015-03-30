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
const int Default_index_Z = 3;


Personaje::Personaje() {
	pos = Posicion(Default_pos_X,Default_pos_Y);
	//inicializo el vector de acciones todo en cero, pq todavia no se esta realizando una accion
	accionesEnCurso[0] = SaltoVertical();
	accionesEnCurso[1] = Agachar();
	accionesEnCurso[2] = Caminar();
	accionesEnCurso[3] = SaltoOblicuo();
	}
/*
void Personaje::ejecutarAcionesActivadas(accionesEnCurso[]){

}

void Personaje::terminarAcciones(accionesEnCurso[]){

}*/
void Personaje::realizarAccion(int orden){

	switch (orden){
		//Saltar
		case (1):
				//No puede saltar mientras esta saltando verticalmente
				if (!accionesEnCurso[0].getEstado()){
					if(!accionesEnCurso[3].getEstado()){
					//No puede saltar si esta agachado oblicuamente
						if(!accionesEnCurso[1].getEstado()){
							//Activo el estado de saltar verticalmente
							accionesEnCurso[0].setEstado(activado);
							cout<< "SALTA"<<endl;
						}
					}
				}
				break;
		//Agachar
		case (2):
			//No te podes agachar mientras estas saltando verticalmente
			if (!accionesEnCurso[0].getEstado()){
				//No te podes agachar mientras estas saltando oblicuamente
				if(!accionesEnCurso[3].getEstado()){
					//activo el estado de agachar
					accionesEnCurso[1].setEstado(activado);
					cout << "SE AGACHA!"<<endl;
				}
			}
				break;

		//Caminar a la derecha
		case (3):
			//No podes avanzar mientras estas saltando verticalmente
			if (!accionesEnCurso[0].getEstado()){
				//No podes avanzar mientras estas saltando oblicuamente
				if(!accionesEnCurso[3].getEstado()){
					//No puede avanzar si esta agachado
					if(!accionesEnCurso[1].getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						accionesEnCurso[2].setEstado(activado, true);
						cout << "CAMINA A LA DERECHA!" << endl;
					}
				}
			}
				break;
		case (4):
				//Caminar a la izquierda
			//No podes avanzar mientras estas saltando verticalmente
			if (!accionesEnCurso[0].getEstado()){
				//No podes avanzar mientras estas saltando oblicuamente
				if(!accionesEnCurso[3].getEstado()){
					if(!accionesEnCurso[1].getEstado()) {
						//activo el estado avanzar
						//orientacion false = izquierda
						accionesEnCurso[2].setEstado(activado, false);
						cout << "CAMINA A LA IZQUIERDA!"<<endl;
					}
				}
			}
			break;
		case (5):
			//No puede saltar oblicuamente mientras esta saltando verticalmente
			if (!accionesEnCurso[0].getEstado()){
				//No puede saltar oblicuamente si esta saltando oblicuamente
				if(!accionesEnCurso[3].getEstado()){
					//No se puede saltar oblicuamente mientras se esta agachado
					if(!accionesEnCurso[1].getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						accionesEnCurso[3].setEstado(activado, true);
						cout << "SALTO OBLICUAMENTE PARA LA DERECHA!"<<endl;
					}
				}
			}
				break;

		//Salto oblicuo a la izquierda
		case (6):
			//No puede saltar oblicuamente mientras esta saltando verticalmente
			if (!accionesEnCurso[0].getEstado()){
				//No puede saltar oblicuamente si esta saltando oblicuamente
				if(!accionesEnCurso[3].getEstado()){
					//No se puede saltar oblicuamente mientras se esta agachado
					if(!accionesEnCurso[1].getEstado()){
						//Activo el estado de saltar oblicuamente
						//ortientacion true = ortientacion derecha
						accionesEnCurso[3].setEstado(activado, false);
						cout << "SALTO OBLICUAMENTE PARA LA IZQUIERDA!"<<endl;
					}
				}
			}				break;

		default:
			break;
	}
	//ejecutarAcionesActivadas(accionesEnCurso[]);

	//terminarAcciones(accionesEnCurso[]);
}




Posicion Personaje::getPosicion(){
	return pos;
}




Personaje::~Personaje() {

}

