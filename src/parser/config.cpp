#include "config.h"
#include <fstream>
#include <string.h>

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
	if(ori=="derecha")
		return Tdireccion::DERECHA;
	else
		return Tdireccion::IZQUIERDA;
}

void config::setValores(Value partes){

	//Si algun nombre de las partes del escenario no coincide se carga por defecto ese valor.

	this->ventana.altopx= partes["ventana"].get("alto-px", 600).asInt();
	this->validacionPositivoI(this->ventana.altopx,"ventana","alto-px");

	this->ventana.anchopx = partes["ventana"].get("ancho-px", 800).asInt();
	this->validacionPositivoI(this->ventana.anchopx,"ventana","ancho-px");

	this->ventana.ancho = partes["ventana"].get("ancho", 200).asInt();
	this->validacionPositivoI(this->ventana.ancho,"ventana","ancho");

	this->personaje.ancho = partes["personaje"].get("ancho", 20).asFloat();
	this->validacionPositivoF(this->personaje.ancho,"personaje","ancho");

	this->personaje.alto = partes["personaje"].get("alto", 35).asFloat();
	this->validacionPositivoF(this->personaje.alto,"personaje","alto");


	this->personaje.zIndex = partes["personaje"].get("z-index",1).asInt();
	this->validacionPositivoI(this->personaje.zIndex,"personaje","z-index");

	string orientacion;
	orientacion = partes["personaje"].get("orientacion","derecha").asString();
	this->personaje.orientacion = this->obtieneEnum(orientacion);

	// TODO - Agregar Ruta relativa
	this->personaje.sprites = partes["personaje"].get("sprites","/home/MortalKombat/sprites").asString();
	this->validacionPath(this->personaje.sprites);

	this->escenario.alto = partes["escenario"].get("alto",150).asFloat();
	this->validacionPositivoF(this->escenario.alto,"escenario","alto");


	this->escenario.ancho = partes["escenario"].get("ancho",1000).asFloat();
	this->validacionPositivoF(this->escenario.ancho,"escenario","ancho");


	this->escenario.yPiso = partes["escenario"].get("y-piso",20).asInt();
	this->validacionPositivoI(this->escenario.yPiso,"escenario","y-piso");


	Value capa=partes["capas"];
	Tcapa aux;
	bool existe=true;
	int anchoCapa=500;
	for(unsigned i = 0; i < capa.size(); i++){
		aux.dirCapa=capa[i].get("imagen_fondo","default").asString();
		FILE *fp = fopen(aux.dirCapa.c_str(),"r");
		if(!fp)
			existe=false;
		else
			fclose(fp);
		aux.ancho=capa[i].get("ancho",anchoCapa).asFloat();
		anchoCapa=anchoCapa*2;
		this->vectorCapas.push_back(aux);
	}

	//Se fija si existe la ruta, sino existe alguna de las rutas, levanta por defecto.
	if(!existe)
		this->cargaPorDefecto();

}

void config::cargaPorDefecto(){
	string mensajeError="Fallo la carga de una de las capas, se cargan capas por defecto.";
	loguerWar->loguear(mensajeError.c_str(), Log::Tlog::LOG_ERR);
	Tcapa aux;
	this->vectorCapas.clear();
	for(unsigned i=0; i<2; i++){
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
		if(num>=0)
			negativo=false;
		else
			negativo=true;

		if (negativo){
			ostringstream mensajeError;
			mensajeError<<"Se ingresó un número negativo en "<<parte<<"/"<<conf<<". Se carga un valor por defecto.";
			loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);
			//Cambia el valor negativo por uno por defecto.
			if(strcmp(parte.c_str(),"ventana")){
					if(strcmp(conf.c_str(),"ancho-px"))
						this->ventana.anchopx=800;
					else
						if(strcmp(parte.c_str(),"alto-px"))
							this->ventana.altopx=600;
						else
							this->ventana.ancho=200;
			}else
				if(strcmp(parte.c_str(),"escenario"))
					this->escenario.yPiso=20;
				else
					this->personaje.zIndex=1;


			}

}

void config::validacionPositivoF(float num,string parte,string conf){
	bool negativo;
	if(num>=0)
		negativo=false;
	else
		negativo=true;

	if (negativo){
		ostringstream mensajeError;
		mensajeError<<"Se ingresó un número negativo en "<<parte<<"/"<<conf<<". Se carga un valor por defecto.";
		loguerWar->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_ERR);
		//Cambia el valor negativo por uno por defecto.
		if(strcmp(parte.c_str(),"escenario")) {
			if(strcmp(parte.c_str(),"ancho"))
				this->escenario.ancho=1000;
			else
				this->escenario.alto=150;

		} else
			if(strcmp(parte.c_str(),"personaje")){
				if(strcmp(conf.c_str(),"ancho"))
					this->personaje.ancho=20;
				else
					this->personaje.alto=35;
				}

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




