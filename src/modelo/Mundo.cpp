#include <functional>
#include "../parser/config.h"
#include "Mundo.h"
#include "Golpe.h"

const float delta = 5.00;
const float deltaParaPelea = 25;
const float deltaParaPoder = 5;


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
	bool direccion = true;

	if(personaje1->pos.getX() - personaje2->pos.getX() <= 0){
		personaje1->setDireccion(direccion);
		personaje2->setDireccion(!direccion);

	}	else{
		personaje1->setDireccion(!direccion);
		personaje2->setDireccion(direccion);
	}
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

	//TODO: PLANTEARSE CAMBIAR SALTO OBLICUO O IMPLEMENTAR OTRA FUNCION
	//TODO: ARREGLAR EL TEMA CUANDO SALTA OBLICUAMENTE
	//La idea es calcular la distancia entre los personajes segun un cierto delta, si no estan
	//quiere decir que se estan por ir de la pantalla, y le asignamos su posicion anterior
	if(!detector.seVan(personaje1,personaje2,(anchoPantalla -(MIN_DISTANCE_FROM_BOUND*5)))){
			personaje1->pos = personaje1->posAnt;
			personaje2->pos = personaje2->posAnt;
	}


//TODO HACER MAS GENERICO, DEBERIAN METERSE TODOS LOS OBJETOS COLISIONABLES
//Esto va a ser para cuando halla mas objetos colisionables por ejemplo poderes

	vector<ObjetoColisionable*> objetosProximos;
	vector<ObjetoColisionable*> objetos;
	objetos.push_back(personaje1);
	objetos.push_back(personaje2);
	//cout<<endl<<"Objetos size: "<<objetos.size()<<endl;
	objetosProximos = detector.detectorDeProximidad(objetos, deltaParaPelea);
	string pj = "Objetos proximos:  "+to_string(objetosProximos.size());
	loguer->loguear(pj.c_str(), Log::LOG_DEB);
	if (!objetosProximos.empty()){
		personaje1->solucionarColision(personaje2);
		personaje2->solucionarColision(personaje1);
		if(personaje1->lanzandoGolpe){
			personaje2->mePegaron(personaje1->punchCreator.getGolpe()->danio);
			string pj = "Vida personaje2:  "+to_string(personaje2->vida);
			loguer->loguear(pj.c_str(), Log::LOG_DEB);
		}
		if(personaje2->lanzandoGolpe){
			personaje1->mePegaron(personaje2->punchCreator.getGolpe()->danio);
			string pj = "Vida personaje1:  "+to_string(personaje1->vida);
			loguer->loguear(pj.c_str(), Log::LOG_DEB);
		}
		//cout<<"ELERTA DE PROXIMIDAD"<<endl;

		/*for (int i=0; i<objetosProximos.size();i++){
			objetosProximos[i]->solucionColision(objetos);
		}*/
	}



	if (personaje1->lanzandoPoder){
		vector<ObjetoColisionable*> personajePoder;
		personajePoder.push_back(personaje2);
		personajePoder.push_back(personaje1->poder);
		objetosProximos = detector.detectorDeProximidad(personajePoder, deltaParaPoder);
		if(!objetosProximos.empty()){
			personaje1->poder->solucionarColision(personaje2);
		}

	}

	if (personaje2->lanzandoPoder){
		vector<ObjetoColisionable*> personajePoder1;
		personajePoder1.push_back(personaje1);
		personajePoder1.push_back(personaje2->poder);
		objetosProximos = detector.detectorDeProximidad(personajePoder1, deltaParaPoder);
		if(!objetosProximos.empty()){
			personaje2->poder->solucionarColision(personaje1);
		}

	}

	return c;
}

Mundo::~Mundo() {
	delete personaje1;
	delete personaje2;
	loguer->loguear("Se libera al personaje", Log::LOG_DEB);
}

