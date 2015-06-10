#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include <iostream>
#include "json.h"
#include "../utils/Common.h"
#include "../utils/PersonajeUtils.h"
#include <vector>

using namespace std;


class config {


public:
	enum Tdato{
		DOUBLE,
		INT,
		STRING,
	};

	enum Tparte{
		ESCENARIO_H,
		ESCENARIO_W,
		ESCENARIO_P,
		VENTANA_H,
		VENTANA_W,
		VENTANA_A,
		COLOR_I,
		COLOR_F,
		COLOR_D,
		BOTONES_HK,//HIGH KICK
				BOTONES_LK,//LOW KICK
				BOTONES_LP,//LOW PUNCH
				BOTONES_HP,//HIGH PUNCH
				BOTONES_PROTEC,//PROTECCION
				BOTONES_POD,//PODER
				PLAYER1,//PELEA
				PLAYER2,//PELEA
				COMBOP,
		COMBOA,
		FATALITIE1,
		GLOBALE,
		GLOBALT,
	};
	struct Tcombo{
		string nombre;
		string combo;
	};

	config(string path);
	virtual ~config();
	Tcombos getCombos();
	int getTiempo();
	int getError();
	Tventana getVentana();
	Tescenario getEscenario();
	vector<Tcapa> getCapas();
	vector<Tpersonaje> getPersonajes ();
	Tbotones getBotones();

private:
	TcolorSettings color;
	Tventana ventana;
	Tescenario escenario;
	Tpersonaje personaje1;
	Tpersonaje personaje2;;
	vector<Tpersonaje> personajes;
	Tpelea pelea;
	Tbotones botones;
	Tcapa capa;
	Tcombo combo1;
	Tcombo fata1;
	int tiempoCombo;
	int errorCombo;
	vector<Tcapa> vectorCapas;
	int zIndexDefecto;

	void setValores(Json::Value);
	void setCapa(Json::Value);

	void obtiene(Json::Value,string,string,Tparte,int,Tdato);
	void defecto(Tparte,int);
	void original(Tparte,Json::Value);
	void setPersonajeX(Json::Value);
	TcolorSettings ObColor(Json::Value,int);
	int cantSprites(TestadoPersonaje);
	bool directorioExiste(const char*);
	void cargaExitosa(string);

	vector<Tinput>letrasAinput(string);
	void validaCombos();

	//Validacion de direcciones de archivos, numeros positivos, y tamaños deseados.
	void validacionPath(string);
	void validacionPositivoI(int,string,string);
	void validacionPositivoF(float,string,string);
	void validacionTamanioZindex();
	void validacionTamanioYpiso();
	void validacionAnchoVentanaEscenario();
	void validacionPelea();

	void copiarImagenDefault(int&,const char*);

	void ventanaDefecto();
	void escenarioDefecto();
	void personajeXDefecto();
	void colorDefecto();
	void capasDefecto();
	void botonesDefecto();

	void fatalitiesDefecto();
	void combosDefecto();
	void globalDefecto();


};

/* namespace config */

#endif /* CONFIG_H_ */