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

	float pos_x1 = anchoEscenario/2 - anchoVentana/2 + MIN_DISTANCE_FROM_BOUND;
	float pos_x2 = anchoEscenario/2 + anchoVentana/2 - PJ2.d.w - MIN_DISTANCE_FROM_BOUND;
	float pos_y1 = altoEscenario - altoPiso - PJ1.d.h;
	float pos_y2 = altoEscenario - altoPiso - PJ2.d.h;

	Tdireccion direccion1 = PJ1.orientacion;
	Tdireccion direccion2 = PJ2.orientacion;

	Trect rectanguloPj1,rectanguloPj2;
	rectanguloPj1.d = PJ1.d;
	rectanguloPj2.d = PJ2.d;
	rectanguloPj1.p = {pos_x1, pos_y1};
	rectanguloPj2.p = {pos_x2,pos_y2};

	//TODO: EL PJ1 Y PJ2 EMPIEZAN EN LADOS OPUESTOS - lo dejamos asi por los controles del teclado

	personaje1 = new Personaje(direccion1,rectanguloPj1,anchoVentana);
	//cout<<"Costado izquierdo personaje 1: "<<personaje1->rectanguloPj.p.getX() - personaje1->rectanguloPj.d.w<<endl;
	personaje2 = new Personaje(direccion2,rectanguloPj2,anchoVentana);
	//cout<<"Costado derecho personaje 2: "<<personaje2->rectanguloPj.p.getX() + personaje2->rectanguloPj.d.w<<endl;


	colisionador = DetectorDeColisiones();

	anchoPantalla = configuracion.getVentana().ancho;
}


vector<Personaje*> Mundo::getPersonajes(){
	return vector<Personaje*> {personaje1,personaje2};
};

float Mundo::getAlto(){
	return altoEscenario;
}

float Mundo::getAncho(){
	return anchoEscenario;
}

float Mundo::getAltoPiso(){
	return altoPiso;
}

Tcambio Mundo::actualizarPJ(Personaje *PJ) {
	Tcambio cambio;
	cambio.dPJ = PJ->rectanguloPj.d;
	cambio.posicion = PJ->rectanguloPj.p;
	cambio.direccion = PJ->direccionPj;
	cambio.sentido = PJ->sentidoPj;
	cambio.estado = PJ->estadoActual;

	cambio.vida = PJ->vida;

	cambio.poder.d = PJ->poder->rectanguloPoder.d;
	cambio.poder.p = PJ->poder->rectanguloPoder.p;
	cambio.poder.e = PJ->poder->estado;

	return cambio;
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
	personaje1->realizarAccion(inputs[0]);
	personaje2->realizarAccion(inputs[1]);

	// COLISIONES
	colisionador.resolverColisiones(personaje1,personaje2);

	//Se actualizan a los personajes
	cambio1 = actualizarPJ(personaje1);
	cambio2 = actualizarPJ(personaje2);

	c.push_back(cambio1);
	c.push_back(cambio2);

	return c;
}


/*void Mundo::verificarColision(bool generaViolencia,Personaje* agresor,Personaje* PJ,ObjetoColisionable *objeto, bool esPoder) {
	if (generaViolencia) {
		if(!esPoder){
			colisionador.solucionarColision(PJ, agresor, (Golpe *) objeto);
		}
		else {
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
	if (PJ->estado == REA_GOLPE_FUERTE){
		loopsReaccionGolpeFuerte++;
		PJ->accionesEnCurso[3]->setConfiguracion(30, 60, 10);
		if (PJ->direccion) {
			if (!PJ->accionesEnCurso[3]->getEstado()) {
				PJ->accionesEnCurso[3]->setEstado(true, PJ->pos, false);
			}
		}
		else {
			if (!PJ->accionesEnCurso[3]->getEstado()) {
				PJ->accionesEnCurso[3]->setEstado(true, PJ->pos, true);
			}
		}
		cout<<loopsReaccionGolpeFuerte<<endl;
		if(loopsReaccionGolpeFuerte >= 13){
			PJ->accionesEnCurso[3]->setEstado(false);
			PJ->estado = MOV_PARADO;
			loopsReaccionGolpeFuerte = 0;
		}
	}
}*/

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
	if(personaje1->rectanguloPj.p.getX() - personaje2->rectanguloPj.p.getX() <= 0){
		personaje1->direccionPj = DERECHA;
		personaje2->direccionPj = IZQUIERDA;

	}	else{
		personaje1->direccionPj = IZQUIERDA;
		personaje2->direccionPj = DERECHA;
	}
}


// No borrar me sirve para el detector de colisiones despues.
/*void Mundo::VerificarSiPjsColisionanaEnElAire(){
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



}*/