#include <functional>
#include "../parser/config.h"
#include "Mundo.h"

const float delta = 5.00;
const float deltaLejania = 80;
const float deltaCero = 0;

/* Constructor de Mundo.
 * Recibe la configuracion que se devuelve del parser.
 * Crea un personaje e inicializa su posicion, altura y ancho.
 * Tambien se inicializa el alto, ancho y yPiso del escenario.

 */
Mundo::Mundo(config configuracion) {
	Tescenario escenario = configuracion.getEscenario();
	Tpersonaje pj = configuracion.getPersonaje();

	anchoEscenario = escenario.ancho;
	altoEscenario = escenario.alto;
	altoPiso = escenario.yPiso;

	float altoPJ = pj.alto;
	float anchoPJ = pj.ancho;

	float pos_x = anchoEscenario/2;
	float pos_y = altoEscenario - altoPiso - altoPJ;


	Tdireccion direccion = configuracion.getPersonaje().orientacion;

	bool dir;

	dir = direccion == DERECHA;

	personaje1 = new Personaje(dir,Posicion(pos_x+anchoPJ,pos_y),altoPJ,anchoPJ);
	personaje2 = new Personaje(dir,Posicion(pos_x-anchoPJ,pos_y),altoPJ,anchoPJ);
	detector = DetectorDeColisiones();
	anchoPantalla = configuracion.getVentana().ancho;
}

/* Devuelve la actualizacion del struct Tcambio recibido junto con el numero de accion que debe realizar
 * Personaje realiza su respectiva accion.
 * Se asigna todos los datos pertinentes de personaje a Tcambio.
 */
Tcambios Mundo::actualizarMundo(Tinputs inputs) {
	Tcambios c;
	//direccion derecha igual true
	verificarDireccionDeLosPersonajes();
	//TODO: PLANTEARSE CAMBIAR SALTO OBLICUO O IMPLEMENTAR OTRA FUNCION
	//TODO: ARREGLAR EL TEMA CUANDO SALTA OBLICUAMENTE
	//La idea es calcular la distancia entre los personajes segun un cierto delta, si no estan
	//quiere decir que se estan por ir de la pantalla, y le asignamos su posicion anterior
	if(!detector.detectarLejania(personaje1,personaje2,anchoPantalla -(MIN_DISTANCE_FROM_BOUND*4))){
		if(personaje1->estado == CAMINANDO){
			if(personaje1->direccion) personaje1->pos = Posicion(personaje1->pos.getX()+2,personaje1->pos.getY());
				else personaje1->pos = Posicion(personaje1->pos.getX()-2,personaje1->pos.getY());
		}
		if(personaje2->estado == CAMINANDO){
			if(personaje2->direccion) personaje2->pos = Posicion(personaje2->pos.getX()+2,personaje2->pos.getY());
			else personaje2->pos = Posicion(personaje2->pos.getX()-2,personaje2->pos.getY());

		}
	}

	if(!detector.detectarLejania(personaje1,personaje2,anchoPantalla-deltaLejania))verificarQueNoSeVallaDeLaPantalla();
		else VerificarSiPjsColisionanaEnElAire();
	personaje1->realizarAccion(inputs.input1,anchoEscenario);
	personaje2->realizarAccion(inputs.input2,anchoEscenario);
	c.cambio1.posicion = personaje1->getPosicion();
	if(personaje1->getDireccion()) c.cambio1.direccion = DERECHA;
	else c.cambio1.direccion = IZQUIERDA;
	if(personaje1->getSentido()) c.cambio1.sentido = ADELANTE;
	else c.cambio1.sentido = ATRAS;
	c.cambio1.estado = personaje1->getEstado();
	c.cambio1.alturaPJ = personaje1->getAlturaPersonaje();
	c.cambio1.anchoPJ = personaje1->getAnchoPersonaje();


	c.cambio2.posicion = personaje2->getPosicion();
	c.cambio2.estado = personaje2->getEstado();
	c.cambio2.alturaPJ = personaje2->getAlturaPersonaje();
	c.cambio2.anchoPJ = personaje2->getAnchoPersonaje();
	if(personaje2->getDireccion()) c.cambio2.direccion = DERECHA;
	else c.cambio2.direccion = IZQUIERDA;
	if(personaje2->getSentido()) c.cambio2.sentido = ADELANTE;
	else c.cambio2.sentido = ATRAS;



//TODO HACER MAS GENERICO, DEBERIAN METERSE TODOS LOS OBJETOS COLISIONABLES
//Esto va a ser para cuando halla mas objetos colisionables por ejemplo poderes
	vector<ObjetoColisionable*> objetosProximos;
	vector<ObjetoColisionable*> objetos;
	objetos.push_back(personaje1);
	objetos.push_back(personaje2);

	objetosProximos = detector.detectorDeProximidad(objetos, delta);
	if (!objetosProximos.empty()){
		//cout<<"ELERTA DE PROXIMIDAD"<<endl;
		objetosProximos[0]->solucionColision(objetos);
		objetosProximos[1]->solucionColision(objetos);
	}

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libera al personaje", Log::LOG_DEB);
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

void Mundo::VerificarSiPjsColisionanaEnElAire() {
	if(personaje1->estado == SALTANDO_OBLICUO && personaje2->estado == SALTANDO_OBLICUO){
		if(detector.seVan(personaje1,personaje2,deltaCero)){
			personaje1->enCaida = true;
			personaje2->enCaida = true;
		}else{
			personaje1->enCaida = false;
			personaje2->enCaida = false;
		}
	}else{
		personaje1->enCaida = false;
		personaje2->enCaida = false;
	}
}

void Mundo::verificarQueNoSeVallaDeLaPantalla() {
		if(personaje1->estado == SALTANDO_OBLICUO) {
			if (((!personaje1->getSentido())&&(personaje1->getDireccion()))||
				((!personaje1->getSentido())&&(!personaje1->getDireccion())))
			personaje1->enCaida = true;
		}else personaje1->enCaida = false;
		if(personaje2->estado == SALTANDO_OBLICUO) {
			if (((!personaje2->getSentido())&&(personaje2->getDireccion()))||
				((!personaje2->getSentido())&&(!personaje2->getDireccion())))
				personaje2->enCaida = true;
		}else personaje2->enCaida = false;
}