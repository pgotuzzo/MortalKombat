

//Suponemos al par ordenado (x,y) como un punto sobre la cabeza de nuestro personaje.


#include "Personaje.h"
#include "acciones/SaltoVertical.h"
#include "acciones/Agachar.h"
#include "acciones/Caminar.h"
#include "acciones/SaltoOblicuo.h"
#include "DetectorDeColisiones.h"


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

	punchCreator = CreadorDeGolpes();

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
			punchCreator.crearGolpe(PINIA_ALTA, pos, ancho, altura, direccion);
			//estado = PINIA_ALTA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PINIA_BAJA):
			punchCreator.crearGolpe(PINIA_BAJA, pos, ancho, altura, direccion);
			//estado = PINIA_BAJA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PATADA_ALTA):
			punchCreator.crearGolpe(PATADA_ALTA, pos, ancho, altura, direccion);
			//estado = PATADA_ALTA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PATADA_BAJA):
			punchCreator.crearGolpe(PATADA_BAJA, pos, ancho, altura, direccion);
			//estado = PATADA_BAJA;
			parado = false;
			lanzandoGolpe = true;
			lanzandoPoder = false;
			break;

		case (KEY_PODER):
			//estado = PODER;
			if (!lanzandoPoder){
				cout<<"Se creo poder"<<endl;
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

void Personaje::solucionColision(vector<ObjetoColisionable*>  objetosProximos) {

	DetectorDeColisiones detector = DetectorDeColisiones();
	vector<ObjetoColisionable*> objetosColisionados;
	//Como quiero saber si realmente estan colisionando le mando un delta 0.0
	objetosColisionados = detector.detectorDeProximidad(objetosProximos,0.0);
	if(!objetosColisionados.empty()){
		//for (int i = 0; i<=objetosColisionados.size();i = i+2){
		determinarAccionPorColision(objetosColisionados[0], objetosColisionados[1]);
		//}
	}
}


//TODO: DEBEMOS CONTEMPLAR EL CASO EN QUE SALTEN Y CHOQUEN EN EL AIRE
// IDEA: generar un un estado "CaidaLibre" que se accione solo cuando chocan en el aire
//       que al setearse desactive todos los otros estados y dure hasta que llegue al piso.
// es solo una sugerencia.

void Personaje::determinarAccionPorColision(ObjetoColisionable *primerObjeto, ObjetoColisionable *segundoObjeto) {
	//cout<<endl<<"CHOCAMOS VIEJA NO ME IMPORTA NADA"<<endl<<endl;


	if ((primerObjeto->pos.getX() - segundoObjeto->pos.getX()) <= 0){
		primerObjeto->pos.setX(primerObjeto->pos.getX() - factorDeRestroceso);
		segundoObjeto->pos.setX(segundoObjeto->pos.getX() + factorDeRestroceso);
	}	else{
			primerObjeto->pos.setX(primerObjeto->pos.getX() + factorDeRestroceso);
			segundoObjeto->pos.setX(segundoObjeto->pos.getX() - factorDeRestroceso);


	};

}

void Personaje::setDireccion(bool direccion) {
	this->direccion = direccion;

}
void Personaje::mePegaron(float danioGolpe) {
	if (vida > danioGolpe) vida = vida - danioGolpe;
	else vida = 0;
}
void Personaje::solucionarColision(ObjetoColisionable *enemigo) {
	DetectorDeColisiones detector = DetectorDeColisiones();
	vector<ObjetoColisionable*> objetosProximos;
	vector<ObjetoColisionable*> personajeYPoder;
	objetosProximos.push_back(this);
	objetosProximos.push_back(enemigo);

	vector<ObjetoColisionable*> objetosColisionados;

	if(lanzandoGolpe){
		cout<<"Se estan pegando"<<endl;
	}


	else{
		objetosColisionados = detector.detectorDeProximidad(objetosProximos,2.0);
		if(!objetosColisionados.empty()){
			if ((this->pos.getX() - enemigo->pos.getX()) <= 0) {
				this->pos.setX(this->pos.getX() - factorDeRestroceso);
				enemigo->pos.setX(enemigo->pos.getX() + factorDeRestroceso);
			} else {
				this->pos.setX(this->pos.getX() + factorDeRestroceso);
				enemigo->pos.setX(enemigo->pos.getX() - factorDeRestroceso);
			};
		}

	}
}