#include "config.h"
#include <fstream>
#include <string.h>

const int cantidadDeCapasDefault = 3;

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
		loguer->loguear(mensaje.c_str(), Log::Tlog::LOG_WAR);
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
		loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
		std::cout << mensajeError << "\n";

	} else {
		//Si el archivo original o el por defecto se pueden parsear entra y setea los valores
		this->setValores(partes);
		string mensaje="Configuración cargada.";
		loguer->loguear(mensaje.c_str(), Log::Tlog::LOG_DEB);
	}
}




void config::setValores(Value partes){

	this->setVentana(partes);

	this->setCapa(partes);

	this->setPersonaje(partes);

	this->setEscenario(partes);

}

void config::setEscenario(Value partes){
	//Se fija si existe esa parte en Json. Si no carga por defecto.
	if(! partes["escenario"].isNull()){

		if(!partes["escenario"].get("alto", 150).isDouble()){
			string mensajeError="En personaje/alto, no hay un numero. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->escenario.alto=150;
		} else
			this->escenario.alto = partes["escenario"].get("alto",150).asFloat();


		this->validacionPositivoF(this->escenario.alto,"escenario","alto");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["escenario"].isMember("alto")){
			string mensajeError="No se encuentra en escenario alto en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		if(!partes["escenario"].get("ancho", 1000).isDouble()){
			string mensajeError="En personaje/ancho, no hay un numero. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->escenario.ancho=1000;
		} else
			this->escenario.ancho = partes["escenario"].get("ancho",1000).asFloat();


		this->validacionPositivoF(this->escenario.ancho,"escenario","ancho");
		this->validacionAnchoVentanaEscenario();


		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["escenario"].isMember("ancho")){
			string mensajeError="No se encuentra en escenario ancho en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		if(!partes["escenario"].get("y-piso", 20).isDouble()){
			string mensajeError="En personaje/y-piso, no hay un numero. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->escenario.yPiso=20;
		} else
			this->escenario.yPiso = partes["escenario"].get("y-piso",20).asFloat();


		this->validacionPositivoF(this->escenario.yPiso,"escenario","y-piso");
		this->validacionTamanioYpiso();

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["escenario"].isMember("y-piso")){
			string mensajeError="No se encuentra en escenario y-piso en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}
		cargaExistosa("escenario");

	} else
		this->escenarioDefecto();

}

void config::setPersonaje(Value partes){
	//Se fija si existe esa parte en Json. Si no carga por defecto.
	if(! partes["personaje"].isNull()){

		if(!partes["personaje"].get("ancho", 20).isDouble()){
			string mensajeError="En personaje/ancho, no hay un float. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->personaje.ancho=20;
		} else
			this->personaje.ancho = partes["personaje"].get("ancho", 20).asFloat();

		this->validacionPositivoF(this->personaje.ancho,"personaje","ancho");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("ancho")){
			string mensajeError="No se encuentra en personaje ancho en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		if(!partes["personaje"].get("alto", 35).isDouble()){
			string mensajeError="En personaje/alto, no hay un float. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->personaje.alto=35;
		} else
			this->personaje.alto = partes["personaje"].get("alto", 35).asFloat();

		this->validacionPositivoF(this->personaje.alto,"personaje","alto");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("alto")){
			string mensajeError="No se encuentra en personaje alto en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		if(!partes["personaje"].get("z-index", 1).isInt()){
			string mensajeError="En personaje/z-index, no hay un Int. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->personaje.zIndex=1;
		} else
			this->personaje.zIndex = partes["personaje"].get("z-index", 1).asInt();

		this->validacionPositivoI(this->personaje.zIndex,"personaje","z-index");
		this->validacionTamanioZindex();

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("z-index")){
			string mensajeError="No se encuentra en personaje z-index en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		string orientacion;
		if(!partes["personaje"].get("orientacion", "derecha").isString()){
			string mensajeError="En personaje/orientacion, no hay un string. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->personaje.orientacion=DERECHA;
		} else {
			orientacion = partes["personaje"].get("orientacion","derecha").asString();
			this->personaje.orientacion = this->obtieneEnum(orientacion);
		}

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("orientacion")){
			string mensajeError="No se encuentra en personaje orientacion en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		// TODO - Agregar Ruta relativa
		if(!partes["personaje"].get("sprites", "/home/MortalKombat/sprites").isString()){
			string mensajeError="En personaje/sprites, no hay un string. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->personaje.sprites="/home/MortalKombat/sprites";
		} else
			this->personaje.sprites = partes["personaje"].get("sprites","/home/MortalKombat/sprites").asString();

		this->validacionPath(this->personaje.sprites);

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["personaje"].isMember("sprites")){
			string mensajeError="No se encuentra en personaje sprites en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		cargaExistosa("personaje");

	} else
		this->personajeDefecto();
}

void config::setVentana(Value partes){

	//Si algun nombre de las partes del escenario no coincide se carga por defecto ese valor.
	if(! partes["ventana"].isNull()){

		if(!partes["ventana"].get("alto-px", 600).isInt()){
			string mensajeError="En ventana/alto-px, no hay un int. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->ventana.altopx=600;
		} else
			this->ventana.altopx= partes["ventana"].get("alto-px", 600).asInt();

		this->validacionPositivoI(this->ventana.altopx,"ventana","alto-px");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["ventana"].isMember("alto-px")){

			string mensajeError="No se encuentra en ventana alto-px en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		if(!partes["ventana"].get("ancho-px", 800).isInt()){
			string mensajeError="En ventana/ancho-px, no hay un Int. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->ventana.anchopx=800;
		} else
			this->ventana.anchopx = partes["ventana"].get("ancho-px", 800).asInt();


		this->validacionPositivoI(this->ventana.anchopx,"ventana","ancho-px");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["ventana"].isMember("ancho-px")){
			string mensajeError="No se encuentra en ventana ancho-px en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		if(!partes["ventana"].get("ancho", 200).isDouble()){
			string mensajeError="En ancho, no hay un float. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
			this->ventana.ancho=200;
		} else
			this->ventana.ancho = partes["ventana"].get("ancho", 200).asFloat();


		this->validacionPositivoF(this->ventana.ancho,"ventana","ancho");

		//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
		if(! partes["ventana"].isMember("ancho")){
			string mensajeError="No se encuentra en ventana ancho en el archivo Json. Se carga por defecto todas sus partes.";
			loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		}

		cargaExistosa("ventana");

	} else
		this->ventanaDefecto();
}

void config::setCapa(Value parte){

	this->vectorCapas.clear();

	//Se fija si existe esa parte en Json. Si no carga por defecto.
	if(! parte["capas"].isNull()){
		Value capa=parte["capas"];
		Tcapa aux;
		float anchoCapa = 500;
		bool existe = true;
		if (capa.size() == 0) this->capasDefecto(); // Miki: agrego este if pq si el array de capas estaba vacio ponia
			//una ventana transparente.
		else {
			float anchoAnterior = 0.0; // Esto lo declare yo. Miki
			unsigned int i=0;
			while( i < capa.size() && existe) {

				if(!capa[i].get("imagen_fondo", "default").isString()){
					string mensajeError="En ventana/capas/imagen_fondo, no hay un string. Se carga por defecto todas sus partes.";
					loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
					aux.dirCapa="default+";
				} else
					aux.dirCapa = capa[i].get("imagen_fondo", "default").asString();

				existe=this->directorioExiste(aux.dirCapa.c_str());

				if(!capa[i].get("ancho", anchoCapa).isDouble()){
					string mensajeError="En ventana/capas/ancho, no hay un float. Se carga por defecto todas sus partes.";
					loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
					aux.ancho=anchoCapa;
				} else
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
					loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);
				}
				anchoAnterior = aux.ancho;
				if(aux.ancho<this->ventana.ancho){
					string mensaje="Ancho de capa mas chico que ancho de la ventana. Se ajusta ancho de capa.";
					loguer->loguear(mensaje.c_str(), Log::Tlog::LOG_WAR);
				}

				// Aca es lo mio. Miki
				//anchoCapa = anchoCapa * 2;
				this->vectorCapas.push_back(aux);
				i++;
			}
		}

		//Se fija si existe la ruta, sino existe alguna de las rutas, levanta por defecto.
		if(!existe)
			this->capasDefecto();
		else
			cargaExistosa("capas");

	} else {
		this->capasDefecto();
	}

}

void config::escenarioDefecto(){
	string mensajeError="No se encuentra: escenario en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	this->escenario.alto=150;
	this->escenario.ancho=1000;
	this->escenario.yPiso=10;
	cargaExistosa("escenario");

}

void config::personajeDefecto(){
	string mensajeError="No se encuentra: personaje en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	this->personaje.alto=50;
	this->personaje.ancho=20;
	this->personaje.zIndex=1;
	this->personaje.orientacion=Tdireccion::DERECHA;
	// TODO - Agregar Ruta relativa
	this->personaje.sprites="/home/MortalKombat/sprites";

	cargaExistosa("personaje");
}

void config::ventanaDefecto(){
	string mensajeError="No se encuentra: ventana en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	this->ventana.altopx=600;
	this->ventana.anchopx=800;
	this->ventana.ancho=200;

	cargaExistosa("ventana");

}

void config::capasDefecto(){

	string mensajeError="Fallo la carga de una de las capas, se cargan capas por defecto.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	Tcapa aux;
	//borrar vector capas
	this->vectorCapas.clear();

	for(unsigned i=1; i<=cantidadDeCapasDefault; i++){

		float auxAncho;
		ostringstream os;

		// TODO - Agregar Ruta relativa
		os<<"/home/MortalKombat/capas/capa"<<(i)<<".png";
		aux.dirCapa=os.str();
		if(i==1)
			auxAncho=600;
		else
			auxAncho=auxAncho+200;
		aux.ancho=auxAncho;
		this->vectorCapas.push_back(aux);
	}

	cargaExistosa("capas");
}

void config::validacionPath(string path){
	ostringstream os;

	int cantErroneos=0;
	bool directorioExiste=true;
	int e=0;
	while( e < 5 && directorioExiste ){

		TestadoPersonaje estado = (TestadoPersonaje) e;
		ostringstream dir;
		dir<<path<<"/"<<TestadoPersonajeToString(estado);

		directorioExiste=this->directorioExiste(dir.str().c_str());

		e++;
	}

	if(!directorioExiste){
		// TODO - Agregar Ruta relativa
		this->personaje.sprites="/home/MortalKombat/sprites";

		ostringstream mensajeError;
		mensajeError<<"Directorios erroneos. Se cargan sprites por default.";
		loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);

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

				if(!this->directorioExiste(os.str().c_str()))
					this->copiarImagenDefault(cantErroneos,os.str().c_str());
			}

		}
}

void config::copiarImagenDefault(int &ContadorErroneos,const char* os){

	ContadorErroneos++;
	if(ContadorErroneos==40){
		// TODO - Agregar Ruta relativa
		this->personaje.sprites="/home/MortalKombat/sprites";
		ostringstream mensajeError;
		mensajeError<<"Falló la carga de todos los sprites. Se cargan sprites por default.";
		loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);
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
	arch.open(os, ios::out | ios::binary);
	arch << aux.rdbuf();

	arch.close();
	aux.close();

	ostringstream mensajeError;
	mensajeError<<"Falló la carga de "<<os<<". Se duplica un sprite en su lugar.";
	loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);
}

void config::validacionTamanioYpiso(){

	float relacion=(float)this->ventana.altopx*(float)this->ventana.ancho/(float)this->ventana.anchopx;

	if(this->escenario.yPiso>=relacion){
		this->escenario.yPiso=20;
		string mensajeError="En encenario: y-piso, más grande que el alto de la ventana. Se carga por defecto y-piso.";
		loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	}
}

void config::validacionTamanioZindex(){
	if((unsigned)this->personaje.zIndex>= this->vectorCapas.size()){

		this->personaje.zIndex=1;
		string mensajeError="En personaje: z-index, mas grande que las capas cargadas. Se carga por defecto z-index.";
		loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	}
}

void config::validacionPositivoI(int num,string parte,string conf){
	bool negativo;
	if(num>=0)
		negativo=false;
	else
		negativo=true;

	if (negativo || (strcmp(conf.c_str(),"z-index")!=0 && negativo)){

		ostringstream mensajeError;
		mensajeError<<"Se ingresó un número negativo en "<<parte<<"/"<<conf<<". Se carga un valor por defecto.";
		loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);


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
		loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);

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

void config::validacionAnchoVentanaEscenario(){
	if(escenario.ancho<=ventana.ancho){
		this->escenario.ancho=this->ventana.ancho+100;
		string mensaje="Ancho de ventana menor que ancho de pantalla. Se carga por defecto ancho de pantalla.";
		loguer->loguear(mensaje.c_str(), Log::Tlog::LOG_WAR);
	}
}

Tdireccion config::obtieneEnum(string ori){
	if(strcmp(ori.c_str(),"derecha")==0)
		return Tdireccion::DERECHA;
	else
	if(strcmp(ori.c_str(),"izquierda")==0)
		return Tdireccion::IZQUIERDA;
	else{
		string mensajeError="Orientación: izquierda o derecha, mal escrita. Se carga por defecto derecha.";
		loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
		return Tdireccion::DERECHA;
	}
}

int config::cantSprites(TestadoPersonaje e){
	int cant=0;
	switch ( e ) {
		case PARADO:
			cant=9;
			break;
		case AGACHADO:
			cant=3;
			break;
		case CAMINANDO:
			cant=8;
			break;
		case SALTANDO_OBLICUO:
			cant=10;
			break;
		case SALTANDO_VERTICAL:
			cant=5;
			break;
	}
	return cant;
}

bool config::directorioExiste(const char* direc){

	bool directorioExiste=true;

	FILE* archivo=fopen(direc,"r");

	if(archivo==NULL)
		directorioExiste=false;
	else
		fclose(archivo);

	return directorioExiste;

}

void config::cargaExistosa(string parte){

	ostringstream mensaje;
	mensaje<<"Se cargó "<<parte;
	loguer->loguear(mensaje.str().c_str(), Log::Tlog::LOG_DEB);
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

	this->vectorCapas.clear();

}



