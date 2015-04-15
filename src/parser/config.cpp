#include "config.h"
#include <fstream>
#include <string.h>

const int cantidadDeCapasDefault = 5;

using namespace Json;

config::config(string path) {
	//En partes estarán todas las partes del escenario.
	Value partes;
	Reader reader(Features::strictMode());

	ifstream prueba(path.c_str(), ios::binary);
	//Se fija si el archivo tiene el formato de Json correcto.
	bool formatoCorrectoJson = reader.parse(prueba, partes, true);
	bool porDefecto=false;
	bool noCoincide=true;
	//Dentro del if, se fija si estan todas las partes del escenario bien escritas, osea si coinciden.
	if(formatoCorrectoJson){
		noCoincide=partes["ventana"].isNull()&&partes["personaje"].isNull()&&partes["capas"].isNull()&&partes["escenario"].isNull();
	}
	//Si el formato del archivo original es incorrecto o el formato es correcto, pero
	//no coincide los nombres de las partes, se carga por defecto.
	if (!formatoCorrectoJson || (formatoCorrectoJson && noCoincide)) {

		string mensaje;
		if (formatoCorrectoJson && noCoincide){
			mensaje = "Fallo el parseo, se carga por defecto. No coinciden los nombres de las partes del escenario";
		} else{
			mensaje = "Fallo el parseo, se carga por defecto" + reader.getFormattedErrorMessages();
		}
		porDefecto=true;
		//Se loguea el error pertinente.
		loguerWar->loguear(mensaje.c_str(), Log::Tlog::LOG_ERR);
		//se abre el archivo por defecto.

		// TODO - Agregar Ruta relativa
		std::ifstream prueba("/home/MortalKombat/EscenarioDefault.json", std::ifstream::binary);
		formatoCorrectoJson = reader.parse(prueba, partes, true);
		if(formatoCorrectoJson){
			noCoincide=partes["ventana"].isNull()&&partes["personaje"].isNull()&&partes["capas"].isNull()&&partes["escenario"].isNull();
		}
	}

	//Si el parseo del archivo original y el por defecto fallan, se loguea el error.
	if (noCoincide && porDefecto) {
		string aux="Fallo el parseo, no coincide ninguno de los nombres de las partes del escenario.No-defecto, No-path";
		string mensajeError = aux + reader.getFormattedErrorMessages();
		loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		std::cout << mensajeError << "\n";
	} else {

		//Si el archivo original o el por defecto se pueden parsear entra y setea los valores
		this->setValores(partes);
	}
}

config::~config() {}

Tdireccion config::obtieneEnum(string ori){
	if(strcmp(ori.c_str(),"derecha")==0)
		return Tdireccion::DERECHA;
	else
	if(strcmp(ori.c_str(),"izquierda")==0)
		return Tdireccion::IZQUIERDA;
	else{
		return Tdireccion::DERECHA;
		string mensajeError="Orientación: izquierda o derecha, mal escrita. Se carga por defecto derecha.";
		loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	}
}

void config::setValores(Value partes){

	//Se fija si existe esa parte en Json. Si no carga por defecto.
	if(! partes["capas"].isNull()){
		Value capa=partes["capas"];
		Tcapa aux;
		int anchoCapa = 500;
		bool existe = true;
		if (capa.size() == 0) this->capasDefecto(); // Miki: agrego este if pq si el array de capas estaba vacio ponia
			//una ventana transparente.
		else {
			float anchoAnterior = 0.0; // Esto lo declare yo. Miki
			for (unsigned i = 0; i < capa.size(); i++) {
				aux.dirCapa = capa[i].get("imagen_fondo", "default").asString();
				FILE *fp = fopen(aux.dirCapa.c_str(), "r");
				if (!fp)
					existe = false;
				else
					fclose(fp);
				aux.ancho = capa[i].get("ancho", anchoCapa).asFloat();
				// Miki: ancho capa mal en json negativo. Devuelvo valor default
				if (aux.ancho <= 0.0) {
					if ( i == 0 ) {
						aux.ancho = 500;
						anchoAnterior = aux.ancho;
					}
					else {
						aux.ancho = anchoAnterior;
					}
					ostringstream mensajeError;
					mensajeError<<"Se ingresó un número negativo en la capa "<<(i+1)<<".Se carga un valor por defecto.";
					loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);
				}
				anchoAnterior = aux.ancho;
				// Aca es lo mio. Miki
				//anchoCapa = anchoCapa * 2;
				this->vectorCapas.push_back(aux);
			}
		}

		//Se fija si existe la ruta, sino existe alguna de las rutas, levanta por defecto.
		if(!existe)
			this->capasDefecto();
	} else {
		this->capasDefecto();
	}

	//Si algun nombre de las partes del escenario no coincide se carga por defecto ese valor.
	if(! partes["ventana"].isNull()){
		this->ventana.altopx= partes["ventana"].get("alto-px", 600).asInt();
		this->validacionPositivoI(this->ventana.altopx,"ventana","alto-px");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["ventana"].isMember("alto-px")){
			string mensajeError="No se encuentra en ventana alto-px en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		this->ventana.anchopx = partes["ventana"].get("ancho-px", 800).asFloat();
		this->validacionPositivoI(this->ventana.anchopx,"ventana","ancho-px");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["ventana"].isMember("ancho-px")){
			string mensajeError="No se encuentra en ventana ancho-px en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		this->ventana.ancho = partes["ventana"].get("ancho", 200).asInt();
		this->validacionPositivoF(this->ventana.ancho,"ventana","ancho");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["ventana"].isMember("ancho")){
			string mensajeError="No se encuentra en ventana ancho en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

	} else
		this->ventanaDefecto();

	//Se fija si existe esa parte en Json. Si no carga por defecto.
	if(! partes["personaje"].isNull()){
		this->personaje.ancho = partes["personaje"].get("ancho", 20).asFloat();
		this->validacionPositivoF(this->personaje.ancho,"personaje","ancho");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("ancho")){
			string mensajeError="No se encuentra en personaje ancho en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		this->personaje.alto = partes["personaje"].get("alto", 35).asFloat();
		this->validacionPositivoF(this->personaje.alto,"personaje","alto");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("alto")){
			string mensajeError="No se encuentra en personaje alto en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		this->personaje.zIndex = partes["personaje"].get("z-index",1).asInt();
		this->validacionPositivoI(this->personaje.zIndex,"personaje","z-index");
		this->validacionTamanioZindex();

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("z-index")){
			string mensajeError="No se encuentra en personaje z-index en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		string orientacion;
		orientacion = partes["personaje"].get("orientacion","derecha").asString();
		this->personaje.orientacion = this->obtieneEnum(orientacion);

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("orientacion")){
			string mensajeError="No se encuentra en personaje orientacion en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		// TODO - Agregar Ruta relativa
		this->personaje.sprites = partes["personaje"].get("sprites","/home/MortalKombat/sprites").asString();
		this->validacionPath(this->personaje.sprites);

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("sprites")){
			string mensajeError="No se encuentra en personaje sprites en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

	} else
		this->personajeDefecto();

	//Se fija si existe esa parte en Json. Si no carga por defecto.
	if(! partes["escenario"].isNull()){

		this->escenario.alto = partes["escenario"].get("alto",150).asFloat();
		this->validacionPositivoF(this->escenario.alto,"escenario","alto");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["escenario"].isMember("alto")){
			string mensajeError="No se encuentra en escenario alto en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		this->escenario.ancho = partes["escenario"].get("ancho",1000).asFloat();
		this->validacionPositivoF(this->escenario.ancho,"escenario","ancho");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["escenario"].isMember("ancho")){
			string mensajeError="No se encuentra en escenario ancho en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

		this->escenario.yPiso = partes["escenario"].get("y-piso",20).asFloat();
		this->validacionPositivoF(this->escenario.yPiso,"escenario","y-piso");
		this->validacionTamanioYpiso();

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["escenario"].isMember("y-piso")){
			string mensajeError="No se encuentra en escenario y-piso en el archivo Json. Se carga por defecto todas sus partes.";
			loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		}

	} else
		this->escenarioDefecto();

}

void config::escenarioDefecto(){
	string mensajeError="No se encuentra: escenario en el archivo Json. Se carga por defecto todas sus partes.";
	loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	this->escenario.alto=150;
	this->escenario.ancho=1000;
	this->escenario.yPiso=10;

}

void config::personajeDefecto(){
	string mensajeError="No se encuentra: personaje en el archivo Json. Se carga por defecto todas sus partes.";
	loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	this->personaje.alto=35;
	this->personaje.ancho=20;
	this->personaje.zIndex=1;
	this->personaje.orientacion=Tdireccion::DERECHA;
	// TODO - Agregar Ruta relativa
	this->personaje.sprites="/home/MortalKombat/sprites";
}

void config::ventanaDefecto(){
	string mensajeError="No se encuentra: ventana en el archivo Json. Se carga por defecto todas sus partes.";
	loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	this->ventana.altopx=600;
	this->ventana.anchopx=800;
	this->ventana.ancho=200;

}

void config::validacionTamanioYpiso(){

	if(this->escenario.yPiso>=this->ventana.altopx){
		this->escenario.yPiso=20;
		string mensajeError="En encenario: y-piso, más grande que el alto de la ventana. Se carga por defecto y-piso.";
		loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	}
}

void config::validacionTamanioZindex(){
	if((unsigned)this->personaje.zIndex>= this->vectorCapas.size()){

		this->personaje.zIndex=1;
		string mensajeError="En personaje: z-index, mas grande que las capas cargadas. Se carga por defecto z-index.";
		loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	}
}

void config::capasDefecto(){

	string mensajeError="Fallo la carga de una de las capas, se cargan capas por defecto.";
	loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	Tcapa aux;
	this->vectorCapas.clear();
	for(unsigned i=0; i<cantidadDeCapasDefault; i++){

		float auxAncho;
		ostringstream os;

		// TODO - Agregar Ruta relativa
		os<<"/home/MortalKombat/capas/capa"<<(i+1)<<".png";
		aux.dirCapa=os.str();
		if(i==0)
			auxAncho=500;
		else
			auxAncho=1000;
		aux.ancho=auxAncho;
		this->vectorCapas.push_back(aux);
	}
}

void config::validacionPath(string path){
	ostringstream os;

	int cantErroneos=0;
	bool directorioErroneo=false;
	for(int e = 0; e < 5; e++ ){

		TestadoPersonaje estado = (TestadoPersonaje) e;
		ostringstream dir;
		dir<<path<<"/"<<TestadoPersonajeToString(estado);
		FILE* archivo=fopen(dir.str().c_str(),"r");

		if(archivo==NULL)
			directorioErroneo=true;
		else
			fclose(archivo);
	}

	if(directorioErroneo){
		// TODO - Agregar Ruta relativa
		this->personaje.sprites="/home/MortalKombat/sprites";

		ostringstream mensajeError;
		mensajeError<<"Directorios erroneos. Se cargan sprites por default.";
		loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);

	} else
		for(int e = 0; e < 5; e++ ){

			TestadoPersonaje estado = (TestadoPersonaje) e;

			for(int i = 1; i <= this->cantSprites(estado); i++){
				os.str("");
				os.clear();
				if(i<=9)
					os<<path<<"/"<<TestadoPersonajeToString(estado)<<"/0"<<i<<".png";
				else
					os<<path<<"/"<<TestadoPersonajeToString(estado)<<"/"<<i<<".png";
				FILE* fp=fopen(os.str().c_str(),"r");
				if(!fp){
					cantErroneos++;
					if(cantErroneos==40){
						// TODO - Agregar Ruta relativa
						this->personaje.sprites="/home/MortalKombat/sprites";
						ostringstream mensajeError;
						mensajeError<<"Falló la carga de todos los sprites. Se cargan sprites por default.";
						loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);
					}
					// TODO - Agregar Ruta relativa
					string path="/home/MortalKombat/sprites/default.jpg";
					ifstream aux;
					ofstream arch;
					const int LEN=8192;
					char buffer_out[LEN];
					char buffer_in[LEN];
					if (LEN) {
						aux.rdbuf()->pubsetbuf(buffer_in, LEN );
						arch.rdbuf()->pubsetbuf(buffer_out, LEN);
					} else {
						aux.rdbuf()->pubsetbuf(NULL, 0 );
						arch.rdbuf()->pubsetbuf(NULL, 0);
					}
					aux.open(path.c_str(), ios::in | ios::binary);
					arch.open(os.str().c_str(), ios::out | ios::binary);
					arch << aux.rdbuf();

					arch.close();
					aux.close();

					ostringstream mensajeError;
					mensajeError<<"Falló la carga de "<<os.str()<<". Se duplica un sprite en su lugar.";
					loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);
				} else
					fclose(fp);
			}

		}
}

void config::validacionPositivoI(int num,string parte,string conf){
	bool negativo;
	if(num>0)
		negativo=false;
	else
		negativo=true;

	if (negativo){

		ostringstream mensajeError;
		mensajeError<<"Se ingresó un número negativo en "<<parte<<"/"<<conf<<". Se carga un valor por defecto.";
		loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);


		//Cambia el valor negativo por uno por defecto.
		if(strcmp(parte.c_str(),"ventana")==0){
			if(strcmp(conf.c_str(),"ancho-px")==0)
				this->ventana.anchopx=800;
			else
			if(strcmp(conf.c_str(),"alto-px")==0)
				this->ventana.altopx=600;
		}else
		if(strcmp(parte.c_str(),"personaje")==0)
			this->personaje.zIndex=1;
	}

}

void config::validacionPositivoF(float num,string parte,string conf){
	bool negativo;
	if(num>0)
		negativo=false;
	else
		negativo=true;

	if (negativo){

		ostringstream mensajeError;
		mensajeError<<"Se ingresó un número negativo en "<<parte<<"/"<<conf<<". Se carga un valor por defecto.";
		loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);

		//Cambia el valor negativo por uno por defecto.
		if(strcmp(parte.c_str(),"escenario")==0) {
			if(strcmp(conf.c_str(),"ancho")==0)
				this->escenario.ancho=1000;
			else
			if(strcmp(conf.c_str(),"alto")==0)
				this->escenario.alto=150;
			else
				this->escenario.yPiso=1;

		} else
		if(strcmp(parte.c_str(),"personaje")==0){
			if(strcmp(conf.c_str(),"ancho")==0)
				this->personaje.ancho=20;
			else
				this->personaje.alto=35;
		} else
			this->ventana.ancho=200;

	}
}

int config::cantSprites(TestadoPersonaje e){
	int cant=0;
	switch ( e ) {
		case PARADO:
			cant=12;
			break;
		case AGACHADO:
			cant=3;
			break;
		case CAMINANDO:
			cant=12;
			break;
		case SALTANDO_OBLICUO:
			cant=8;
			break;
		case SALTANDO_VERTICAL:
			cant=5;
			break;
	}
	return cant;
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



