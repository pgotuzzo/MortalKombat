#include "config.h"
#include <fstream>
#include <string.h>

const int cantidadDeCapasDefault = 4;
const int cantidadTotalSprites=40;
using namespace Json;

config::config(string path) {
	//En partes estarán todas las partes del escenario.
	Value partes;
	Value defecto;
	Reader reader(Features::strictMode());

	std::ifstream pruebaD("./resources/EscenarioDefault.json", std::ifstream::binary);
	bool correctFormat = reader.parse(pruebaD, defecto, true);
	zIndexDefecto=defecto["escenario"].get("z-index",1).asInt();

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

		std::ifstream prueba("./resources/EscenarioDefault.json", std::ifstream::binary);
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
	if(! partes["ventana"].isNull()){
		obtiene(partes,"ventana","alto-px",Tparte::VENTANA_H,600,Tdato::INT);
		validacionPositivoI((int)ventana.dimPx.h,"ventana","alto-px");
		obtiene(partes,"ventana","ancho-px",Tparte::VENTANA_W,800,Tdato::INT);
		validacionPositivoI((int)ventana.dimPx.w,"ventana","ancho-px");
		obtiene(partes,"ventana","ancho",Tparte::VENTANA_A,200,Tdato::DOUBLE);
		validacionPositivoF(ventana.ancho,"ventana","ancho");
	}else
		this->ventanaDefecto();
	cargaExitosa("ventana");

	this->setCapa(partes);

	setPersonajeX(partes);

	this->validacionTamanioZindex();

	if( !partes["pelea"].isNull()){
		obtiene(partes,"pelea","player1",Tparte::PLAYER1,99,Tdato::STRING);
		obtiene(partes,"pelea","player2",Tparte::PLAYER2,99,Tdato::STRING);
		pelea.valida(personajes);
	}else{
		pelea.player1=personajes.at(0).nombre;
		pelea.player2=personajes.at(0).nombre;
		loguer->loguear("Se carga por defecto pelea.",Log::Tlog::LOG_WAR);
	}

	if(! partes["escenario"].isNull()){
		obtiene(partes,"escenario","alto",Tparte::ESCENARIO_H,150,Tdato::DOUBLE);
		validacionPositivoF(escenario.d.h,"escenario","alto");
		obtiene(partes,"escenario","ancho",Tparte::ESCENARIO_W,1000,Tdato::DOUBLE);
		validacionPositivoF(escenario.d.w,"escenario","ancho");
		this->validacionAnchoVentanaEscenario();
		obtiene(partes,"escenario","y-piso",Tparte::ESCENARIO_P,25,Tdato::DOUBLE);
		validacionPositivoF(escenario.yPiso,"escenario","y-piso");
		this->validacionTamanioYpiso();
	}else
		this->escenarioDefecto();
	cargaExitosa("escenario");

	if(! partes["botones"].isNull()){
		obtiene(partes,"botones","patada-alta",Tparte::BOTONES_HK,15,Tdato::INT);
		obtiene(partes,"botones","patada-baja",Tparte::BOTONES_LK,14,Tdato::INT);
		obtiene(partes,"botones","piña-alta",Tparte::BOTONES_HP,13,Tdato::INT);
		obtiene(partes,"botones","piña-baja",Tparte::BOTONES_LP,12,Tdato::INT);
		obtiene(partes,"botones","poder",Tparte::BOTONES_POD,11,Tdato::INT);
		obtiene(partes,"botones","proteccion",Tparte::BOTONES_PROTEC,10,Tdato::INT);
		botones.valida();
	}else
		this->botonesDefecto();
	cargaExitosa("botones");
}

void config::setPersonajeX(Value partes){
	if(! partes["personajes"].isNull()){
		Value parte=partes["personajes"];
		for(unsigned int i=0;i<parte.size();i++){

			if(parte[i].get("ancho","defecto").isDouble()){
				personaje1.d.w=parte[i].get("ancho",25).asFloat();
			}else{
				loguer->loguear("Error al cargar ancho personaje, se carga por defecto",Log::Tlog::LOG_WAR);
				personaje1.d.w=25;
			}
			validacionPositivoF(personaje1.d.w,"personaje","ancho");

			if(parte[i].get("alto","defecto").isDouble()){
				personaje1.d.h=parte[i].get("alto",60).asFloat();
			}else{
				loguer->loguear("Error al cargar alto personaje, se carga por defecto",Log::Tlog::LOG_WAR);
				personaje1.d.h=60;
			}
			validacionPositivoF(personaje1.d.h,"personaje","alto");

			if(parte[i].get("z-index","defecto").isInt()){
				personaje1.zIndex=parte[i].get("z-index",2).asInt();
			}else{
				loguer->loguear("Error al cargar z-index personaje, se carga por defecto",Log::Tlog::LOG_WAR);
				personaje1.zIndex=2;
			}
			this->validacionPositivoI(personaje1.zIndex,"personaje","z-index");

			if(parte[i].get("nombre",99).isString()){
				personaje1.nombre=parte[i].get("nombre","default").asString();
			}else{
				loguer->loguear("Error al cargar nombre personaje, se carga por defecto",Log::Tlog::LOG_WAR);
				personaje1.nombre="Default_"+i;
			}

			if(parte[i].get("sprites",99).isString()){
				personaje1.sprites=parte[i].get("sprites","default").asString();
			}else{
				loguer->loguear("Error al cargar sprites personaje, se carga por defecto",Log::Tlog::LOG_WAR);
				personaje1.sprites="./resources/sprites/subzero";
			}
			this->validacionPath(personaje1.sprites);

			personaje1.colorSettings=ObColor(parte,i);

			personajes.push_back(personaje1);
		}

	}else{
		this->personajeXDefecto();
	}

	cargaExitosa("personaje");
}

TcolorSettings config::ObColor(Value partes,int i){
	TcolorSettings aux;
	if(!partes[i]["color-alternativo"].isNull()){
		Value colores=partes[i]["color-alternativo"];

		if(colores[0].get("h-inicial","defecto").isDouble()){
			aux.hmin=colores[0].get("h-inicial",30).asFloat();
		}else{
			loguer->loguear("Error en color-alternativo. Se carga por defecto",Log::Tlog::LOG_WAR);
			aux.hmin=30;
		}

		if(colores[1].get("h-final","defecto").isDouble()){
			aux.hmax=colores[1].get("h-final",45).asFloat();
		}else{
			loguer->loguear("Error en color-alternativo. Se carga por defecto",Log::Tlog::LOG_WAR);
			aux.hmax=45;
		}

		if(colores[2].get("delta","defecto").isDouble()){
			aux.delta=colores[2].get("delta",45).asFloat();
		}else{
			loguer->loguear("Error en color-alternativo. Se carga por defecto",Log::Tlog::LOG_WAR);
			aux.delta=45;
		}
		aux.initialize();
		return aux;

	}else{
		this->colorDefecto();
		return color;
	}
}

void config::obtiene(Value partes,string parte,string subParte, Tparte tparte,int defecto,Tdato tipo){
	bool tipoDato=false;
	switch (tipo) {
		case DOUBLE: tipoDato=partes[parte].get(subParte, defecto).isDouble();

			break;
		case INT: tipoDato=partes[parte].get(subParte, defecto).isInt();break;
		case STRING: tipoDato=partes[parte].get(subParte, "defecto").isString();break;
		case ARRAY: tipoDato=partes[parte].get(subParte, "defecto").isArray();break;
	}

	if(!tipoDato){
		ostringstream mensaje;
		mensaje<<parte<<"/"<<subParte<<", dato mal ingresado. Se carga por defecto todas sus partes.";
		loguer->loguear(mensaje.str().c_str(), Log::Tlog::LOG_WAR);
		this->defecto(tparte,defecto);
	} else
		original(tparte,partes);

	//Se verifica si existe el miembro en la variable partes. Si no se carga por defecto.
	if(! partes[parte].isMember(subParte)){
		ostringstream mensajeError;
		mensajeError<<"No se encuentra en "<<parte<<"/"<<subParte<<" en el archivo Json. Se carga por defecto todas sus partes.";
		loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);
	}
}

void config::original(Tparte tipoParte,Value partes){
	switch (tipoParte){
		case ESCENARIO_H: this->escenario.d.h=partes["escenario"].get("alto",150).asFloat();break;
		case ESCENARIO_W: this->escenario.d.w=partes["escenario"].get("ancho",150).asFloat();break;
		case ESCENARIO_P: this->escenario.yPiso=partes["escenario"].get("y-piso",150).asFloat();break;
		case VENTANA_H: this->ventana.dimPx.h=partes["ventana"].get("alto-px",150).asInt();break;
		case VENTANA_W: this->ventana.dimPx.w=partes["ventana"].get("ancho-px",150).asInt();break;
		case VENTANA_A: this->ventana.ancho=partes["ventana"].get("ancho",150).asFloat();break;
		case COLOR_D: this->color.delta=partes["color-alternativo"].get("delta",30).asInt();break;
		case COLOR_I: this->color.hmin=partes["color-alternativo"].get("h-inicial",40).asInt();break;
		case COLOR_F: this->color.hmax=partes["color-alternativo"].get("h-final",45).asInt();break;
		case BOTONES_HK: this->botones.highKick=partes["botones"].get("patada-alta",15).asInt();break;
		case BOTONES_LK: this->botones.lowKick=partes["botones"].get("patada-baja",14).asInt();break;
		case BOTONES_HP: this->botones.highPunch=partes["botones"].get("piña-alta",13).asInt();break;
		case BOTONES_LP: this->botones.lowPunch=partes["botones"].get("piña-baja",12).asInt();break;
		case BOTONES_POD: this->botones.poder=partes["botones"].get("poder",11).asInt();break;
		case BOTONES_PROTEC: this->botones.proteccion=partes["botones"].get("proteccion",10).asInt();break;
		case PLAYER1: pelea.player1=partes["pelea"].get("player1","subzero").asString();break;
		case PLAYER2: pelea.player2=partes["pelea"].get("player2","ermac").asString();break;
	}
}

void config::defecto(Tparte tipoParte,int defecto){
	switch (tipoParte){
		case ESCENARIO_H: this->escenario.d.h=defecto;break;
		case ESCENARIO_W: this->escenario.d.w=defecto;break;
		case ESCENARIO_P: this->escenario.yPiso=defecto;break;
		case VENTANA_H: this->ventana.dimPx.h=defecto;break;
		case VENTANA_W: this->ventana.dimPx.w=defecto;break;
		case VENTANA_A: this->ventana.ancho=defecto;break;
		case COLOR_D: this->color.delta=defecto;break;
		case COLOR_I: this->color.hmin=defecto;break;
		case COLOR_F:this->color.hmax=defecto;break;
		case BOTONES_HK: this->botones.highKick=defecto;break;
		case BOTONES_LK: this->botones.lowKick=defecto;break;
		case BOTONES_HP: this->botones.highPunch=defecto;break;
		case BOTONES_LP: this->botones.highKick=defecto;break;
		case BOTONES_POD: this->botones.poder=defecto;break;
		case BOTONES_PROTEC: this->botones.proteccion=defecto;break;
		case PLAYER1: pelea.player1=personajes.at(0).nombre;break;
		case PLAYER2: pelea.player2=personajes.at(0).nombre;break;
	}
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
			cargaExitosa("capas");

	} else {
		this->capasDefecto();
	}
}

void config::escenarioDefecto(){
	string mensajeError="No se encuentra: escenario en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	this->escenario.d.h = 150;
	this->escenario.d.w = 1000;
	this->escenario.yPiso=10;
}

void config::personajeXDefecto(){
	string mensajeError="No se encuentra: personaje en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	personaje1.d.h = 50;
	personaje1.d.w = 20;
	personaje1.zIndex=2;
	personaje1.nombre="subzero";
	personaje1.sprites = "./resources/sprites/subzero";

	personaje2.d.h = 50;
	personaje2.d.w = 20;
	personaje2.zIndex=2;
	personaje2.nombre="ermac";
	personaje2.sprites = "./resources/sprites/ermac";
	personajes.push_back(personaje1);
	personajes.push_back(personaje2);
}

void config::ventanaDefecto(){
	string mensajeError="No se encuentra: ventana en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	this->ventana.dimPx.h = 600;
	this->ventana.dimPx.w = 800;
	this->ventana.ancho=200;
}

void config::colorDefecto(){
	string mensajeError="No se encuentra: color-alternativo en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	this->color.delta=30;
	this->color.hmax=45;
	this->color.hmin=40;
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

		os<<"./resources/capas/capa"<<(i)<<".png";
		aux.dirCapa=os.str();
		if(i==1)
			auxAncho=600;
		else
			auxAncho=auxAncho+200;
		aux.ancho=auxAncho;
		this->vectorCapas.push_back(aux);
	}
	cargaExitosa("capas");
}

void config::botonesDefecto(){
	string mensajeError="No se encuentra: botones en el archivo Json. Se carga por defecto todas sus partes.";
	loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	botones.highKick=12;
	botones.highPunch=13;
	botones.lowKick=14;
	botones.lowPunch=15;
	botones.poder=11;
	botones.proteccion=10;
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

		this->personaje1.sprites="./resources/sprites/subzero";

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
	if(ContadorErroneos==cantidadTotalSprites){

		this->personaje1.sprites="./resources/sprites/subzero";

		ostringstream mensajeError;
		mensajeError<<"Falló la carga de todos los sprites. Se cargan sprites por default.";
		loguer->loguear(mensajeError.str().c_str(), Log::Tlog::LOG_WAR);
	}
	string path="./resources/sprites/default.jpg";
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

	float relacion=(float)this->ventana.dimPx.h * (float)this->ventana.ancho/(float)this->ventana.dimPx.w;

	if(this->escenario.yPiso>=relacion){
		this->escenario.yPiso=20;
		string mensajeError="En encenario: y-piso, más grande que el alto de la ventana. Se carga por defecto y-piso.";
		loguer->loguear(mensajeError.c_str(), Log::Tlog::LOG_WAR);
	}
}

void config::validacionTamanioZindex(){

	for(unsigned int i=0;i<(personajes.size()-1);i++){

		if(personajes.at(i).zIndex!=personajes.at(i+1).zIndex){
			loguer->loguear("Distintos Z-index, se igualan.", Log::Tlog::LOG_WAR);
			personajes.at(i+1).zIndex=personajes.at(i).zIndex;
		}
	}

	if((unsigned)personajes.at(0).zIndex>= this->vectorCapas.size()){
		for(unsigned int i=0;i<personajes.size();i++){
			personajes.at(i).zIndex=1;
		}
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
				this->ventana.dimPx.w = 800;
			else
			if(strcmp(conf.c_str(),"alto-px")==0)
				this->ventana.dimPx.h = 600;
		}else
		if(strcmp(parte.c_str(),"personaje")==0){
			this->personaje1.zIndex=1; personaje2.zIndex=1;}
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
				this->escenario.d.w = 1000;
			else
			if(strcmp(conf.c_str(),"alto")==0)
				this->escenario.d.h = 150;
			else
				this->escenario.yPiso=1;
		} else
		if(strcmp(parte.c_str(),"personaje")==0){
			if(strcmp(conf.c_str(),"ancho")==0)
				this->personaje1.d.w = 20;
			else
				this->personaje1.d.h = 35;
		} else
			this->ventana.ancho=200;
	}
}

void config::validacionAnchoVentanaEscenario(){
	if(escenario.d.w <= ventana.ancho){
		this->escenario.d.w = this->ventana.ancho+100;
		string mensaje="Ancho de ventana menor que ancho de pantalla. Se carga por defecto ancho de pantalla.";
		loguer->loguear(mensaje.c_str(), Log::Tlog::LOG_WAR);
	}
}

int config::cantSprites(TestadoPersonaje e){
	int cant=0;
	switch ( e ) {
		case MOV_PARADO:
			cant=9;
			break;
		case MOV_AGACHADO:
			cant=3;
			break;
		case MOV_CAMINANDO:
			cant=8;
			break;
		case MOV_SALTANDO_OBLICUO:
			cant=10;
			break;
		case MOV_SALTANDO_VERTICAL:
			cant=5;
			break;
		case ACC_PINIA_BAJA:
			cant=4;break;
		case ACC_PINIA_BAJA_AGACHADO:
			cant=3;break;
		case ACC_PINIA_ALTA:
			cant=9;break;
		case ACC_PINIA_ALTA_AGACHADO:
			cant=5;break;
		case ACC_PINIA_SALTO:
			cant=3;break;
		case ACC_PATADA_BAJA:
			cant=9;break;
		case ACC_PATADA_BAJA_ATRAS:
			cant=8;break;
		case ACC_PATADA_AGACHADO:
			cant=7;break;
		case ACC_PATADA_SALTO_VERTICAL:
			cant=3;break;
		case ACC_PATADA_SALTO:
			cant=3;break;
		case ACC_PATADA_ALTA:
			cant=3;break;
		case ACC_PATADA_ALTA_ATRAS:
			cant=8;break;
		case ACC_PROTECCION:
			cant=3;break;
		case ACC_PROTECCION_AGACHADO:
			cant=3;break;
		case ACC_PODER:
			cant=7;break;

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

void config::cargaExitosa(string parte){
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

vector <Tpersonaje> config::getPersonajes(){
	vector <Tpersonaje> vectorPersonajes;

	unsigned int i=0;
	if(personajes.size()==1){
		loguer->loguear("Un solo personaje en personajes, se selecciona el mismo personaje dos veces",Log::Tlog::LOG_WAR);
		vectorPersonajes.push_back(personajes.at(0));
		vectorPersonajes.push_back(personajes.at(0));
	}else
		while(i<personajes.size()||vectorPersonajes.size()!=2){

			if(!strcmp(pelea.player1.c_str(),personajes.at(i).nombre.c_str()) && !strcmp(pelea.player2.c_str(),personajes.at(i).nombre.c_str())){
				vectorPersonajes.push_back(personajes.at(i));
				vectorPersonajes.push_back(personajes.at(i));
			}else if(!strcmp(pelea.player1.c_str(),personajes.at(i).nombre.c_str())||!strcmp(pelea.player2.c_str(),personajes.at(i).nombre.c_str()))
				vectorPersonajes.push_back(personajes.at(i));
			i++;
		}

	return vectorPersonajes;
}

vector<Tcapa> config::getCapas(){
	return this->vectorCapas;
}
Tbotones config::getBotones(){
	return botones;
}

config::~config() {
	this->vectorCapas.clear();
}