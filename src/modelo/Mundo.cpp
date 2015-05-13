#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const float delta = 5.00;
const float deltaLejania = 80;
const float deltaCero = 0;
const float deltaParaPelea = 25.00;
const float deltaParaPoder = 5.00;

/* Constructor de Mundo.
 * Recibe la configuracion que se devuelve del parser.
 * Crea un personaje e inicializa su posicion, altura y ancho.
 * Tambien se inicializa el alto, ancho y yPiso del escenario.

 */
Mundo::Mundo(config configuracion) {
	Tescenario escenario = configuracion.getEscenario();
	vector<Tpersonaje> personajes = configuracion.getPersonajes();
	float anchoVentana = configuracion.getVentana().ancho;

	cout<<anchoVentana<<endl;

	Tpersonaje PJ1 = personajes[0];
	Tpersonaje PJ2 = personajes[1];


	anchoEscenario = escenario.d.w;
	altoEscenario = escenario.d.h;
	altoPiso = escenario.yPiso;

	float altoPJ1 = PJ1.d.h;
	float anchoPJ1 = PJ1.d.w;
	float altoPJ2 = PJ2.d.h;
	float anchoPJ2 = PJ2.d.w;

	float pos_x = anchoEscenario/2;
	float pos_y1 = altoEscenario - altoPiso - altoPJ1;
	float pos_y2 = altoEscenario - altoPiso - altoPJ2;

	Tdireccion direccion1 = PJ1.orientacion;
	Tdireccion direccion2 = PJ2.orientacion;

	bool dir1, dir2;

	if (direccion1 == DERECHA) dir1 = true;
	else dir1 = false;

	if(direccion2 == DERECHA) dir2 = true;
	else dir2 = false;


	//TODO: EL PJ1 Y PJ2 EMPIEZAN EN LADOS OPUESTOS - lo dejamos asi por los controles del teclado

	personaje1 = new Personaje(dir1,Posicion(pos_x+anchoVentana/2-anchoPJ1-MIN_DISTANCE_FROM_BOUND,pos_y1),altoPJ1,anchoPJ1);
	cout<<"Costado izquierdo personaje 1: "<<personaje1->pos.getX() - personaje1->ancho/2<<endl;
	personaje2 = new Personaje(dir2,Posicion(pos_x-anchoVentana/2+MIN_DISTANCE_FROM_BOUND,pos_y2),altoPJ2,anchoPJ2);
	cout<<"Costado derecho personaje 2: "<<personaje2->pos.getX() + personaje2->ancho/2<<endl;
	colisionador = Colisionador();
	colisionador.setEscenario(anchoEscenario);
	anchoPantalla = configuracion.getVentana().ancho;
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

/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
vector<Tcambio> Mundo::actualizarMundo(vector<Tinput> inputs) {
	vector<Tcambio> c;
	Tcambio cambio1, cambio2;

	//Verifica y da vuelta la direccion de los personajes si se pasan
	verificarDireccionDeLosPersonajes();

	// Los personajes realizan sus acciones
	personaje1->realizarAccion(inputs[0],anchoEscenario);
	personaje2->realizarAccion(inputs[1],anchoEscenario);

	personaje1->accionesEnCurso[2]->setAnchoDePasoDefault();
	personaje2->accionesEnCurso[2]->setAnchoDePasoDefault();


	//Choque de saltos oblicuos en el aire
	if(!colisionador.sonCercanos(personaje1, personaje2, anchoPantalla - (MIN_DISTANCE_FROM_BOUND * 2)-personaje1->ancho - personaje2->ancho)){
		verificarQueNoSeVallaDeLaPantalla();
	}
	else {
		VerificarSiPjsColisionanaEnElAire();
	}

	//Colision entre personajes (empujar)
	if (colisionador.sonProximos(personaje1,personaje2,deltaCero)){
		colisionador.solucionarColision(personaje1,personaje2);
		colisionador.solucionarColision(personaje2,personaje1);
	}

	//Colision entre el personaje y el golpe
	bool esPoder = true;
	verificarColision(personaje2->lanzandoGolpe,personaje2->estado,personaje1,personaje2->golpe,!esPoder);
	string mensajePJ1 = "Vida del personaje 1: " + to_string(personaje1->vida);
	if(personaje1->vida < 100 && personaje1->vida > 0)loguer->loguear(mensajePJ1.c_str(),Log::LOG_DEB);
	verificarColision(personaje1->lanzandoGolpe,personaje1->estado,personaje2,personaje1->golpe,!esPoder);
	string mensajePJ2 = "Vida del personaje 2: " + to_string(personaje2->vida);
	if(personaje2->vida < 100 && personaje2->vida > 0)loguer->loguear(mensajePJ2.c_str(),Log::LOG_DEB);

	//Colision entre el personaje y el poder
	if(personaje1->lanzandoPoder) {
		cout<<"personaje que lanza el poder"<<endl;
		personaje1->pos.mostrarPar();
	}
	if(personaje2->lanzandoPoder) {
		cout<<"personaje que lanza el poder"<<endl;
		personaje2->pos.mostrarPar();
	}
	verificarColision(personaje2->lanzandoPoder,personaje2->estado,personaje1,personaje2->poder,esPoder);
	verificarColision(personaje1->lanzandoPoder,personaje1->estado,personaje2,personaje1->poder,esPoder);

	//Se actualizan a los personajes
	cambio1 = actualizarPJ(personaje1);
	cambio2 = actualizarPJ(personaje2);

	/*cout<<"PERSONAJE1"<<endl;
	personaje1->pos.mostrarPar();*/

	c.push_back(cambio1);
	c.push_back(cambio2);

	return c;
}


void Mundo::verificarColision(bool generaViolencia,TestadoPersonaje estadoViolento,Personaje* PJ,ObjetoColisionable *objeto, bool esPoder) {
	if (generaViolencia) {
		switch (estadoViolento) {
			case (ACC_PATADA_ALTA_ATRAS):
				if (colisionador.sonProximos(personaje1, personaje2, 8) && !esPoder) {
					//cout<<"Personaje que recibe el poder"<<endl;
					//PJ->pos.mostrarPar();
					colisionador.solucionarColision(PJ, estadoViolento, (Golpe *) objeto);
				}
				break;
			default:
				if (colisionador.sonProximos(personaje1, personaje2, 2) && !esPoder) {
					//cout<<"Personaje que recibe el poder"<<endl;
					//PJ->pos.mostrarPar();
					colisionador.solucionarColision(PJ, estadoViolento, (Golpe *) objeto);
				}
				break;
		}
		if (esPoder) {
			if (PJ->direccion) {
				if (colisionador.distanciaColisionadaenX(PJ,objeto)>0){
					objeto->pos.setX(objeto->pos.getX() + colisionador.distanciaColisionadaenX(PJ,objeto));
					colisionador.solucionarColision(PJ, (Poder *) objeto);
				}
			}
			else{
				if (colisionador.distanciaColisionadaenX(objeto,PJ)>0){
					objeto->pos.setX(objeto->pos.getX() - colisionador.distanciaColisionadaenX(objeto,PJ));
					colisionador.solucionarColision(PJ, (Poder *) objeto);
				}

			}
		}
	}
}

Tcambio Mundo::actualizarPJ(Personaje *PJ) {
	Tcambio cambio;
	cambio.posicion = PJ->getPosicion();
	if(PJ->getDireccion()) cambio.direccion = DERECHA;
	else cambio.direccion = IZQUIERDA;
	if(PJ->getSentido()) cambio.sentido = ADELANTE;
	else cambio.sentido = ATRAS;
	cambio.estado = PJ->getEstado();
	cambio.dPJ.h = PJ->getAlturaPersonaje();
	cambio.dPJ.w = PJ->getAnchoPersonaje();

	cambio.vida = PJ->vida;

	cambio.poder.d.h = PJ->poder->altura;
	cambio.poder.d.w = PJ->poder->ancho;
	cambio.poder.p = PJ->poder->pos;

	return cambio;

}

Mundo::~Mundo() {
	if(personaje1->vida == 0) loguer->loguear("El personaje 1 esta muerto",Log::LOG_DEB);
	else loguer->loguear("El personaje 1 sobrevivio",Log::LOG_DEB);
	if(personaje2->vida == 0) loguer->loguear("El personaje 2 esta muerto",Log::LOG_DEB);
	else loguer->loguear("El personaje 2 sobrevivio",Log::LOG_DEB);
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libero a los personajes", Log::LOG_DEB);
}

void Mundo::verificarDireccionDeLosPersonajes() {
	//direccion derecha igual true
	if(personaje1->pos.getX() - personaje2->pos.getX() <= 0){
		personaje1->setDireccion(true);
		personaje2->setDireccion(false);

	}	else{
		personaje1->setDireccion(false);
		personaje2->setDireccion(true);
	}
}

void Mundo::VerificarSiPjsColisionanaEnElAire(){
	if ((personaje1->getEstado() != MOV_SALTANDO_OBLICUO) || (personaje1->sentido == false)) {
		personaje1->enCaida = false;
		personaje2->enCaida = false;
	}
	if ((personaje2->getEstado() != MOV_SALTANDO_OBLICUO) || (personaje2->sentido == false)) {
		personaje1->enCaida = false;
		personaje2->enCaida = false;
	}
	if (colisionador.sonCercanos(personaje1, personaje2, deltaCero)) {
		if (personaje1->estado == MOV_SALTANDO_OBLICUO && personaje1->sentido == true && personaje2->estado ==
																						 MOV_SALTANDO_OBLICUO && personaje2->sentido == true) {
			personaje1->enCaida = true;
			personaje2->enCaida = true;
			if ((personaje1->pos.getX() - personaje2->pos.getX()) <= 0) {
				if(colisionador.distanciaColisionadaenX(personaje1,personaje2) < 0) {
					personaje2->pos.setX(personaje2->pos.getX() + colisionador.distanciaColisionadaenX(personaje1, personaje2));
				}
			} else {
				if(colisionador.distanciaColisionadaenX(personaje2,personaje1) > 0) {
					personaje2->pos.setX(personaje2->pos.getX() -colisionador.distanciaColisionadaenX(personaje2, personaje1));
				}
			};
		}
	}


}



void Mundo::verificarQueNoSeVallaDeLaPantalla() {

	// No se vayan caminando
	if(personaje1->estado == MOV_CAMINANDO && !personaje1->sentido){
			personaje1->pos.setX(personaje1->posAnt.getX());
		}
	if(personaje2->estado == MOV_CAMINANDO && !personaje2->sentido){
		personaje2->pos.setX(personaje2->posAnt.getX());
		}
	if ((personaje1->estado == MOV_SALTANDO_OBLICUO || personaje1->estado == ACC_PINIA_SALTO || personaje1->estado ==
																								ACC_PATADA_SALTO) && !personaje1->sentido){
		personaje1->enCaida = true;
		personaje1->pos.setX(personaje1->posAnt.getX());
		if((personaje2->estado == MOV_SALTANDO_OBLICUO || personaje2->estado == ACC_PINIA_SALTO || personaje2->estado ==
																								   ACC_PATADA_SALTO) && !personaje2->sentido){
			personaje2->enCaida = true;
			personaje2->pos.setX(personaje2->posAnt.getX());
		}
		if (personaje2->estado == MOV_CAMINANDO && !personaje2->sentido){
			//personaje2->pos = personaje2->posAnt;
			personaje2->pos.setX(personaje2->posAnt.getX());
		}

	}

	if ((personaje2->estado == MOV_SALTANDO_OBLICUO || personaje2->estado == ACC_PINIA_SALTO || personaje2->estado ==
																								ACC_PATADA_SALTO) && !personaje2->sentido){
		personaje2->enCaida = true;
		personaje2->pos.setX(personaje2->posAnt.getX());
		if (personaje1->estado == MOV_CAMINANDO && !personaje1->sentido) {
			personaje1->pos.setX(personaje1->posAnt.getX());
			//personaje1->pos = personaje1->posAnt;
		}

	}
	if (((personaje1->getEstado() != MOV_SALTANDO_OBLICUO || personaje1->estado != ACC_PINIA_SALTO || personaje1->estado !=
																									  ACC_PATADA_SALTO)) || personaje1->sentido) {
		personaje1->enCaida = false;
		personaje2->enCaida = false;
	}
	if (((personaje2->getEstado() != MOV_SALTANDO_OBLICUO) || personaje2->estado != ACC_PINIA_SALTO || personaje2->estado !=
																									   ACC_PATADA_SALTO) || personaje2->sentido) {
		personaje1->enCaida = false;
		personaje2->enCaida = false;
	}



}
