

//Suponemos al par ordenado (x,y) como un punto sobre la cabeza de nuestro personaje.


#include "Personaje.h"
#include "acciones/SaltoVertical.h"
#include "acciones/Agachar.h"
#include "acciones/Caminar.h"
#include "acciones/SaltoOblicuo.h"


const float factorDeRestroceso = 2;
const bool activado = true;
const float avanceDelPoder = 5;
const float danioPoder = 5;


/*
 *Constructor de personaje. Se crean acciones que puede realizar el mismo.
 * Direccion: True = derecha
 * Sentido: True = derecha
 */
Personaje::Personaje(bool direccion,Posicion posInicial,float alto,float ancho){

	this->direccion = direccion;
	this->sentido = true;
	parado = true;
	estado = PARADO;
	inputAnterior.movimiento = TinputMovimiento:: KEY_NADA;
	inputAnterior.accion = TinputAccion:: KEY_NADA;
	this->posInicial = posInicial;
	pos = posInicial;
	posAnt = posInicial;
	alturaParado = alto;
	this->altura = alto;
	this->ancho = ancho;
	yPiso = altura + pos.getY();
	accionesEnCurso[0] = new SaltoVertical();
	accionesEnCurso[1] = new Agachar(&altura, pos.getY() + altura);
	accionesEnCurso[2] = new Caminar();
	accionesEnCurso[3] = new SaltoOblicuo(altura);

	loopsGolpe = 0;
	loopsPiniaAlta = 0;
	loopsPiniaBaja = 0;

	string pj = "Se crea personaje con ancho "+to_string(ancho)+" y alto "+to_string(alto);
	loguer->loguear(pj.c_str(), Log::LOG_DEB);
	loguer->loguear("Se crean las acciones del personaje", Log::LOG_DEB);

	enCaida = false;

	golpe = new Golpe(this->ancho,this->altura);

	poder = new Poder(this->ancho,this->altura);

	lanzandoGolpe = false;
	lanzandoPoder = false;
	protegiendose = false;

	vida = 100;
}



/*
 * Se verifica que el personaje no se pase nunca por debajo del piso.
 */
Posicion Personaje::verificarPuntoEnY(Posicion posicionActual){
	if(posicionActual.getY()+altura >= yPiso){
		return Posicion(posicionActual.getX(),yPiso-altura);
	}
	return posicionActual;

}

/*
 * Se verifica que el personaje nunca se pase de los margenes del escenario.
 * Si se pasa devuelve la posicion del limite del margen correspondiente.
 */
Posicion Personaje::verificarPuntoEnX(Posicion posicionActual,float anchoEscenario){
	if (posicionActual.getX() > anchoEscenario - ancho){
		return Posicion(anchoEscenario - ancho, posicionActual.getY());
	}
	if (posicionActual.getX() < 1){
		return Posicion(1,posicionActual.getY());
	}
	else return posicionActual;
}

/*
 * Se ejecutan las acciones que esten activadas (una por vez). Verificando que no se vaya del piso
 * y de los margenes.
 * No hay ninguna condicion para activar a agachar debido a que esta dura un gameloop.
 */
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
		pos = verificarPuntoEnX(accionesEnCurso[3]->realizarAccion(pos,enCaida),anchoEscenario);
	}
	if (poder->estado){
		poder->avanzar(10);
	}
}

TestadoPersonaje Personaje::generarEstado(Tinput input) {
	TinputMovimiento movimiento = input.movimiento;
	TinputAccion accion = input.accion;

	switch (movimiento){
		case TinputMovimiento::KEY_NADA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return PARADO;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return PODER;
			}
			break;
		case TinputMovimiento:: KEY_ABAJO:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return AGACHADO;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return AGACHADO;
			}
			break;

		case TinputMovimiento::KEY_DERECHA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return CAMINANDO;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return PODER;
			}
			break;
		case TinputMovimiento::KEY_IZQUIERDA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return CAMINANDO;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return PODER;
			}
			break;
		case TinputMovimiento::KEY_ARRIBA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return SALTANDO_VERTICAL;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return PODER;
			}
			break;
		case TinputMovimiento::KEY_ARRIBA_DERECHA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return SALTANDO_OBLICUO;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return PODER;
			}
			break;
		case TinputMovimiento::KEY_ARRIBA_IZQUIERDA:
			switch(accion){
				case TinputAccion::KEY_NADA:
					return SALTANDO_OBLICUO;
				case TinputAccion::KEY_PATADA_ALTA:
					return PATADA_ALTA;
				case TinputAccion::KEY_PATADA_BAJA:
					return PATADA_BAJA;
				case TinputAccion::KEY_PINIA_ALTA:
					return PINIA_ALTA;
				case TinputAccion::KEY_PINIA_BAJA:
					return PINIA_BAJA;
				case TinputAccion::KEY_PROTECCION:
					return PROTECCION;
				case TinputAccion::KEY_PODER:
					return PODER;
			}
			break;
	}
}


bool Personaje::seguirPegando(TestadoPersonaje estadoInput) {
	if(estado == PINIA_ALTA && (estadoInput == PARADO || estadoInput == CAMINANDO) && loopsPiniaAlta > 0){
		return true;
	}
	if(estado == PINIA_ALTA_AGACHADO && estadoInput == AGACHADO && loopsGolpe > 0){
		return true;
	}
	if(estado == PINIA_BAJA && (estadoInput == PARADO || estadoInput == CAMINANDO) && loopsPiniaBaja>0){
		return true;
	}
	if(estado == PINIA_BAJA_AGACHADO && estadoInput == AGACHADO && loopsGolpe > 0){
		return true;
	}
	if(estado == PATADA_ALTA && (estadoInput == PARADO || estadoInput == CAMINANDO) && loopsGolpe > 0){
		return true;
	}
	if(estado == PATADA_AGACHADO && estadoInput == AGACHADO && loopsGolpe > 0){
		return true;
	}
	if(estado == PATADA_ALTA_ATRAS && estadoInput == CAMINANDO && !sentido && loopsGolpe > 0){
		return true;
	}
	if(estado == PATADA_BAJA && (estadoInput == PARADO || estadoInput == CAMINANDO) && loopsGolpe > 0){
		return true;
	}
	if(estado == PATADA_BAJA_ATRAS && estadoInput == CAMINANDO && !sentido && loopsGolpe > 0){
		return true;
	}
	if(estado == PODER && (estadoInput == PARADO || estadoInput == SALTANDO_VERTICAL) && loopsGolpe >0){
		return true;
	}
	return false;
}


/*
 * Dependiendo de la orden que se reciba se activara la accion correspondiente.
 * Por default se siguen ejecutando las acciones que se venian ejecutando de antes.
 * Se verifica que no se puedan activar dos funciones al mismo tiempo. Por ejemplo no
 * se puede agachar mientras esta saltando verticalmente.
 */
void Personaje::realizarAccion(Tinput orden,float anchoEscenario) {
	posAnt = pos;
	golpe->setAlturaPJ(altura);
	TestadoPersonaje estadoInput = generarEstado(orden);
	if(!seguirPegando(estadoInput)) {
		switch (estadoInput) {
			case AGACHADO:
				//activo el estado de agachar
				if (!accionesEnCurso[0]->getEstado()) {
					if (!accionesEnCurso[3]->getEstado()) {
						if (!poder->estado) {
							loguer->loguear("El personaje se encuentra agachado", Log::LOG_DEB);
							accionesEnCurso[1]->setEstado(activado, pos);
							estado = AGACHADO;
							parado = false;
							lanzandoGolpe = false;
							lanzandoPoder = false;
						}
					}
				}
				break;
			case PARADO:
				if (!accionesEnCurso[0]->getEstado()) {
					if (!accionesEnCurso[3]->getEstado()) {
						if (!accionesEnCurso[1]->getEstado()) {
							if (!poder->estado) {
								//loguer->loguear("El personaje se encuentra parado", Log::LOG_DEB);
								parado = true;
								estado = PARADO;
								lanzandoGolpe = false;
								lanzandoPoder = false;
								protegiendose = false;

							}
						}
					}
				}
				break;
			case CAMINANDO:
				if (orden.movimiento == TinputMovimiento::KEY_DERECHA){
					if( !protegiendose || (inputAnterior.movimiento == TinputMovimiento::KEY_DERECHA
										   && estado == PROTECCION
										   && orden.accion == TinputAccion::KEY_NADA)) {
						caminar(true);
					}
				}
				else if (orden.movimiento == TinputMovimiento::KEY_IZQUIERDA){
					if( !protegiendose || (inputAnterior.movimiento == TinputMovimiento::KEY_IZQUIERDA
										   && estado == PROTECCION
										   && orden.accion == TinputAccion::KEY_NADA)) {
						caminar(false);
					}
				}
				break;
			case SALTANDO_VERTICAL:
				if (!accionesEnCurso[0]->getEstado()) {
					if (!accionesEnCurso[3]->getEstado()) {
						if (!accionesEnCurso[1]->getEstado()) {
							if (!protegiendose || (inputAnterior.movimiento == TinputMovimiento::KEY_ARRIBA
												   && estado == PROTECCION
												   && orden.accion == TinputAccion::KEY_NADA)) {
								//Activo el estado de saltar verticalmente. Puede realizar el poder durante el salto vertical
								loguer->loguear("El personaje salta verticalmente", Log::LOG_DEB);
								accionesEnCurso[0]->setEstado(activado, pos);
								estado = SALTANDO_VERTICAL;
								parado = false;
								lanzandoGolpe = false;
								lanzandoPoder = false;
								protegiendose = false;
							}
						}
					}
				}
				break;
			case SALTANDO_OBLICUO:
				if (orden.movimiento == TinputMovimiento::KEY_ARRIBA_DERECHA){
					if( !protegiendose || (inputAnterior.movimiento == TinputMovimiento::KEY_ARRIBA_DERECHA
										   && estado == PROTECCION
										   && orden.accion == TinputAccion::KEY_NADA)) {
						saltarOblicuamente(true);
					}
				}
				else if (orden.movimiento == TinputMovimiento::KEY_ARRIBA_IZQUIERDA){
					if( !protegiendose || (inputAnterior.movimiento == TinputMovimiento::KEY_ARRIBA_IZQUIERDA
										   && estado == PROTECCION
										   && orden.accion == TinputAccion::KEY_NADA)) {
						saltarOblicuamente(false);
					}
				}
				break;
			case PROTECCION:
				if (!accionesEnCurso[3]->getEstado() && !accionesEnCurso[0]->getEstado() && !poder->estado) {
					if (orden.movimiento != TinputMovimiento::KEY_ABAJO) {
						estado = PROTECCION;
					}
					if (estado == PARADO || accionesEnCurso[2]->getEstado()) {
						estado = PROTECCION;
					}
					if (estado == AGACHADO) {
						estado = PROTECCION_AGACHADO;
					}
					parado = false;
					lanzandoGolpe = false;
					lanzandoPoder = false;
					protegiendose = true;
				}
				break;
			case PODER:
				if(estado != PROTECCION || estado != PROTECCION_AGACHADO){
					if (estado == PARADO || estado == SALTANDO_VERTICAL) {
							if (!poder->estado) {
								loopsGolpe = 3;
								poder->activar(this->pos, this->direccion, danioPoder, true);
								estado = PODER;
							}
							parado = false;
							lanzandoGolpe = false;
							lanzandoPoder = true;
							protegiendose = false;
					}
				}
				break;
			case PINIA_ALTA:
				if(loopsPiniaAlta > 0){
					loopsPiniaAlta = loopsPiniaAlta + 3;
				}
				if (!poder->estado) {
					if (estado == PARADO || estado == CAMINANDO) {
						loopsPiniaAlta = 4;
						golpe->activar(PINIA_ALTA, this->pos, this->direccion);
						estado = PINIA_ALTA;
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (estado == AGACHADO) {
						loopsGolpe = 5;
						estado = PINIA_ALTA_AGACHADO;
						golpe->setAlturaPJ(altura / 2);
						golpe->activar(PINIA_ALTA, Posicion(pos.getX(), pos.getY() / 2), direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (accionesEnCurso[0]->getEstado() || accionesEnCurso[3]->getEstado()) {
						estado = PINIA_SALTO;
						golpe->activar(PINIA_BAJA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
				}
				break;
			case PINIA_BAJA:
				if(loopsPiniaBaja > 0){
					loopsPiniaBaja = loopsPiniaBaja + 3;
				}
				if (!poder->estado) {
					if (estado == PARADO || estado == CAMINANDO) {
						loopsPiniaBaja = 4;
						golpe->activar(PINIA_BAJA, this->pos, this->direccion);
						estado = PINIA_BAJA;
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (estado == AGACHADO) {
						loopsGolpe = 4;
						estado = PINIA_BAJA_AGACHADO;
						golpe->setAlturaPJ(altura / 2);
						golpe->activar(PINIA_BAJA, Posicion(pos.getX(), pos.getY() / 2), direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (accionesEnCurso[0]->getEstado() || accionesEnCurso[3]->getEstado()) {
						estado = PINIA_SALTO;
						golpe->activar(PINIA_BAJA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
				}
				break;
			case PATADA_ALTA:
				if (!poder->estado) {
					if (estado == PARADO || (estado == CAMINANDO && sentido)) {
						loopsGolpe = 12;
						golpe->activar(PATADA_ALTA, this->pos, this->direccion);
						estado = PATADA_ALTA;
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (estado == AGACHADO) {
						loopsGolpe = 4;
						estado = PATADA_AGACHADO;
						golpe->setAlturaPJ(altura / 2);
						golpe->activar(PATADA_BAJA, Posicion(pos.getX(), pos.getY() / 2), direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (accionesEnCurso[0]->getEstado()) {
						estado = PATADA_SALTO_VERTICAL;
						golpe->activar(PATADA_ALTA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (accionesEnCurso[3]->getEstado()) {
						estado = PATADA_SALTO;
						golpe->activar(PATADA_BAJA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (estado == CAMINANDO && !sentido) {
						loopsGolpe = 8;
						estado = PATADA_ALTA_ATRAS;
						golpe->activar(PATADA_ALTA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
				}
				break;
			case PATADA_BAJA:
				if (!poder->estado) {
					if (estado == PARADO || (estado == CAMINANDO && sentido)) {
						loopsGolpe = 12;
						golpe->activar(PATADA_BAJA, this->pos, this->direccion);
						estado = PATADA_BAJA;
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (estado == AGACHADO) {
						loopsGolpe = 4;
						estado = PATADA_AGACHADO;
						golpe->setAlturaPJ(altura / 2);
						golpe->activar(PATADA_BAJA, Posicion(pos.getX(), pos.getY() / 2), direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (accionesEnCurso[0]->getEstado()) {
						estado = PATADA_SALTO_VERTICAL;
						golpe->activar(PATADA_ALTA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (accionesEnCurso[3]->getEstado()) {
						estado = PATADA_SALTO;
						golpe->activar(PATADA_BAJA, pos, direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
					if (estado == CAMINANDO && !sentido) {
						loopsGolpe = 8;
						estado = PATADA_BAJA_ATRAS;
						golpe->setAlturaPJ(altura / 2);
						golpe->activar(PATADA_BAJA, Posicion(pos.getX(), pos.getY() + 6 / 7 * altura), direccion);
						parado = false;
						lanzandoGolpe = true;
						lanzandoPoder = false;
						protegiendose = false;
					}
				}
				break;
			default:
				cout << "Entro al default" << endl;
				break;

		}
	}
	if(loopsGolpe > 0) loopsGolpe--;
	if(loopsPiniaAlta>0) loopsPiniaAlta--;
	if(loopsPiniaBaja>0) loopsPiniaBaja--;
	inputAnterior = orden;

	ejecutarAcionesActivadas(accionesEnCurso,anchoEscenario);
	//Este metodo va a ejecutar las acciones que este listas para ejecutarse
	//Cada accion se desactiva cuando termina.


}

bool Personaje::getSentido() {
	return sentido;
}

bool Personaje::getDireccion() {
	return direccion;
}

void Personaje::setEstado(TestadoPersonaje estado) {
	this->estado = estado;
	if (estado == AGACHADO || estado == SALTANDO_OBLICUO){
		altura = altura/2;
		pos.setY(posInicial.getY()+altura);
	}
	altura = alturaParado;
	pos.setY(posInicial.getY()-alturaParado/2);

}


TestadoPersonaje Personaje::getEstado() {
	if(parado) return PARADO;
	return estado;
}


Posicion Personaje::getPosicion(){
	return pos;
}


float Personaje::getAlturaPersonaje() {
	// si esta saltando oblicuamente devuelve la mitad de la altura del personaje.
	if (accionesEnCurso[3]->getEstado()) return altura / 2;
	return altura;
}

float Personaje::getAltura() {
	if (accionesEnCurso[3]->getEstado()) return altura / 2;
	return altura;

}

float Personaje::getAnchoPersonaje() {
	return ancho;
}

// Se destruyen las acciones creadas en el constructor de personaje.
Personaje::~Personaje() {
	int i;
	for (i = 0;i<4;i++){
		delete accionesEnCurso[i];
	}
	delete golpe;
	delete poder;
	loguer->loguear("Se liberan acciones del personaje", Log::LOG_DEB);

}

void Personaje::setDireccion(bool direccion) {
	this->direccion = direccion;

}
void Personaje::mePegaron(float danioGolpe) {
	if (vida > danioGolpe) vida = vida - danioGolpe;
	else vida = 0;
}

void Personaje::caminar(bool direc) {
	if (!accionesEnCurso[0]->getEstado()) {
		if (!accionesEnCurso[3]->getEstado()) {
			if (!accionesEnCurso[1]->getEstado()) {
				if(!poder->estado) {
					//activo el estado avanzar
					if (direc) {
						sentido = direccion;
						loguer->loguear("El personaje camina hacia la derecha", Log::LOG_DEB);
					}
					else {
						sentido = !direccion;
						loguer->loguear("El personaje camina hacia la izquierda", Log::LOG_DEB);
					}
					accionesEnCurso[2]->setEstado(activado, direc);
					estado = CAMINANDO;
					parado = false;
					lanzandoGolpe = false;
					lanzandoPoder = false;
					protegiendose = false;
				}
			}
		}
	}

}

void Personaje::saltarOblicuamente(bool direc) {
	if (!accionesEnCurso[0]->getEstado()) {
		if (!accionesEnCurso[3]->getEstado()) {
			if (!accionesEnCurso[1]->getEstado()) {
				if(!poder->estado) {
					//Activo el estado de saltar oblicuamente
					if (direc) {
						sentido = direccion;
						loguer->loguear("El personaje salta a la derecha", Log::LOG_DEB);
					}
					else {
						sentido = !direccion;
						loguer->loguear("El personaje salta a la izquierda", Log::LOG_DEB);
					}
					accionesEnCurso[3]->setEstado(activado, pos, direc);
					estado = SALTANDO_OBLICUO;
					parado = false;
					lanzandoGolpe = false;
					lanzandoPoder = false;
					protegiendose = false;
				}
			}
		}
	}

}


