

//Suponemos al par ordenado (x,y) como un punto sobre la cabeza de nuestro personaje.


#include "Personaje.h"
#include "acciones/SaltoVertical.h"
#include "acciones/Agachar.h"
#include "acciones/Caminar.h"
#include "acciones/SaltoOblicuo.h"
#include "Colisionador.h"


const float factorDeRestroceso = 2;
const bool activado = true;
const float avanceDelPoder = 5;


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
	pos = posInicial;
	posAnt = posInicial;
	this->altura = alto;
	this->ancho = ancho;
	yPiso = altura + pos.getY();
	accionesEnCurso[0] = new SaltoVertical();
	accionesEnCurso[1] = new Agachar(&altura, pos.getY() + altura);
	accionesEnCurso[2] = new Caminar();
	accionesEnCurso[3] = new SaltoOblicuo(altura);

	string pj = "Se crea personaje con ancho "+to_string(ancho)+" y alto "+to_string(alto);
	loguer->loguear(pj.c_str(), Log::LOG_DEB);
	loguer->loguear("Se crean las acciones del personaje", Log::LOG_DEB);

	enCaida = false;

	golpe = new Golpe(this->ancho,this->altura);

	poder = new Poder();

	lanzandoGolpe = false;

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
		poder->avanzar(avanceDelPoder);
	}
}

/*
 * Dependiendo de la orden que se reciba se activara la accion correspondiente.
 * Por default se siguen ejecutando las acciones que se venian ejecutando de antes.
 * Se verifica que no se puedan activar dos funciones al mismo tiempo. Por ejemplo no
 * se puede agachar mientras esta saltando verticalmente.
 */
void Personaje::realizarAccion(Tinput orden,float anchoEscenario){
	posAnt = pos;
	switch (orden){
		//Parado
		case(KEY_NADA):
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					if (!accionesEnCurso[1]->getEstado()) {
						if(!poder->estado) {
							//loguer->loguear("El personaje se encuentra parado", Log::LOG_DEB);
							parado = true;
							estado = PARADO;
							lanzandoGolpe = false;
							lanzandoPoder = false;
						}
					}
				}
			}
			break;
			//Saltar
		case (KEY_ARRIBA):
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					if (!accionesEnCurso[1]->getEstado()) {
						//Activo el estado de saltar verticalmente
						loguer->loguear("El personaje salta verticalmente", Log::LOG_DEB);
						accionesEnCurso[0]->setEstado(activado, pos);
						estado = SALTANDO_VERTICAL;
						parado = false;
						lanzandoGolpe = false;
						lanzandoPoder = false;
					}
				}
			}
			break;
			//Agachar
		case (KEY_ABAJO):
			//activo el estado de agachar
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					loguer->loguear("El personaje se encuentra agachado", Log::LOG_DEB);
					accionesEnCurso[1]->setEstado(activado, pos);
					estado = AGACHADO;
					parado = false;
					lanzandoGolpe = false;
					lanzandoPoder = false;
				}
			}
			break;

			//Caminar a la derecha
		case (KEY_DERECHA):
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					if (!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						sentido = direccion;
						loguer->loguear("El personaje camina hacia la derecha", Log::LOG_DEB);
						accionesEnCurso[2]->setEstado(activado, true);
						estado = CAMINANDO;
						parado = false;
						lanzandoGolpe = false;
						lanzandoPoder = false;
					}
				}
			}
			break;
			//Caminar a la izquierda
		case (KEY_IZQUIERDA):
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					if (!accionesEnCurso[1]->getEstado()) {
						//activo el estado avanzar
						sentido = !direccion;
						loguer->loguear("El personaje camina hacia la izquierda", Log::LOG_DEB);
						accionesEnCurso[2]->setEstado(activado, false);
						estado = CAMINANDO;
						parado = false;
						lanzandoGolpe = false;
						lanzandoPoder = false;
					}
				}
			}
			break;
			//Salto oblicuo a la derecha
		case (KEY_ARRIBA_DERECHA):
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					if (!accionesEnCurso[1]->getEstado()) {
						//Activo el estado de saltar oblicuamente
						sentido = direccion;
						loguer->loguear("El personaje salta a la derecha", Log::LOG_DEB);
						accionesEnCurso[3]->setEstado(activado, pos, true);
						estado = SALTANDO_OBLICUO;
						parado = false;
						lanzandoGolpe = false;
						lanzandoPoder = false;
					}
				}
			}
			break;

			//Salto oblicuo a la izquierda
		case (KEY_ARRIBA_IZQUIERDA):
			if (!accionesEnCurso[0]->getEstado()) {
				if (!accionesEnCurso[3]->getEstado()) {
					if (!accionesEnCurso[1]->getEstado()) {
						//Activo el estado de saltar oblicuamente
						sentido = !direccion;
						loguer->loguear("El personaje salta a la izquierda", Log::LOG_DEB);
						accionesEnCurso[3]->setEstado(activado, pos, false);
						estado = SALTANDO_OBLICUO;
						parado = false;
						lanzandoGolpe = false;
						lanzandoPoder = false;
					}
				}
			}
			break;

		case (KEY_PINIA_ALTA):
			golpe->activar(PINIA_ALTA,this->pos,this->direccion);
			//estado = PINIA_ALTA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PINIA_BAJA):
			golpe->activar(PINIA_BAJA,this->pos,this->direccion);
			//estado = PINIA_BAJA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PATADA_ALTA):
			golpe->activar(PATADA_ALTA,this->pos,this->direccion);
			//estado = PATADA_ALTA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PATADA_BAJA):
			golpe->activar(PATADA_BAJA,this->pos,this->direccion);
			//estado = PATADA_BAJA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PODER):
			//estado = PODER;
			if (!lanzandoPoder){
				poder = new Poder(pos,ancho,altura);//TODO: No se tiene que crear cada vez que se apreta la tecla
			}
			poder->activar(direccion,0,true);
			lanzandoGolpe = false;
			lanzandoPoder = true;
			break;

		case (KEY_PROTECCION):
			//estado = PROTECCION;
			lanzandoGolpe = false;
			lanzandoPoder = false;
			break;

		default:
			estado = PARADO;
			lanzandoGolpe = false;
			lanzandoPoder = false;
			break;
	}

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

float Personaje::getAnchoPersonaje() {
	return ancho;
}

// Se destruyen las acciones creadas en el constructor de personaje.
Personaje::~Personaje() {
	int i;
	for (i = 0;i<4;i++){
		delete accionesEnCurso[i];
	}
	loguer->loguear("Se liberan acciones del personaje", Log::LOG_DEB);

}

void Personaje::setDireccion(bool direccion) {
	this->direccion = direccion;

}
void Personaje::mePegaron(float danioGolpe) {
	if (vida > danioGolpe) vida = vida - danioGolpe;
	else vida = 0;
}
