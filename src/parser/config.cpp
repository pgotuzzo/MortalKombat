#include "config.h"

#include <fstream>

using namespace Json;

config::config(string path) {
	//Inicio el Reader para leer el archivo.
	Value partes;
	Reader reader(Features::strictMode());
	//Prueba si se puede parsear el archivo.
	ifstream prueba(path.c_str(), ios::binary);
	//
	bool parseoExitoso = reader.parse(prueba, partes, true);

	if (!parseoExitoso) {
		string mensaje = "Fallo el parseo, se carga por defecto" + reader.getFormattedErrorMessages();
		//const char * c = mensaje.c_str();
		//Log::loguear(c, Log::LOG_TIPO::LOG_ERR);
		std::ifstream prueba("pruebaDefecto.json", std::ifstream::binary);
		parseoExitoso = reader.parse(prueba, partes, true);
	}

	//Se fija si coinciden  las partes del escenario con sus respectivos nombres,
	//si alguna no coincide se pasa al else y la que no coincide se levanta por defecto.
	bool noCoincide=partes["ventana"].isNull()&&partes["personaje"].isNull()&&partes["capas"].isNull()&&partes["escenario"].isNull();

	if (noCoincide) {
		std::string mensajeError = "No coinciden los nombres de las partes del escenario, fallo el parseo del archivo ";
		//Log::Loguear(mensajeError, path);
		std::cout << mensajeError << "\n";

	} else {
		this->ventana.altopx= partes["ventana"].get("alto-px", 600).asInt();
		this->ventana.anchopx = partes["ventana"].get("ancho-px", 800).asInt();
		this->ventana.ancho = partes["ventana"].get("ancho", 200).asInt();

		string orientacion;
		this->personaje.ancho = partes["personaje"].get("ancho", 20).asFloat();
		this->personaje.alto = partes["personaje"].get("alto", 35).asFloat();
		this->personaje.zIndex = partes["personaje"].get("z-index",1).asInt();
		orientacion = partes["personaje"].get("orientacion","derecha").asString();
		this->personaje.orientacion = this->obtieneBool(orientacion);

		this->escenario.alto = partes["escenario"].get("alto",150).asFloat();
		this->escenario.ancho = partes["escenario"].get("ancho",1000.5).asFloat();
		this->escenario.yPiso = partes["escenario"].get("y-piso",20).asInt();

		Value capa=partes["capas"];
		Tcapa aux;
		for(unsigned i=0; i<capa.size(); i++){
			aux.dirCapa=capa[i].get("imagen_fondo","defaultFondo.png").asString();
			aux.ancho=capa[i].get("ancho",500).asFloat();
			this->vectorCapas.push_back(aux);
		}

	}
}

Tdireccion config::obtieneBool(string ori){
	if(ori=="derecha")
		return Tdireccion::DERECHA;
	else
		return Tdireccion::IZQUIERDA;
}

Tventana config::getVentana(){
	return this->ventana;
}

Tescenario config::getEscenario(){
	return this->escenario;
}

Tpersonaje config::getPersonaje(){
	return this->personaje;
}

vector<Tcapa> config::getCapas(){
	return this->vectorCapas;
}

config::~config() {
	// TODO Auto-generated destructor stub
}

