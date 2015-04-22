#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include <iostream>
#include "json.h"
#include "../Common.h"
#include <vector>

using namespace std;


class config {

public:
	config(string path);
	virtual ~config();

	Tventana getVentana();
	Tescenario getEscenario();
	vector<Tcapa> getCapas();
	Tpersonaje getPersonaje ();

private:

	Tventana ventana;
	Tescenario escenario;
	Tpersonaje personaje;
	Tcapa capa;
	vector<Tcapa> vectorCapas;

	void setValores(Json::Value);
	void setCapa(Json::Value);
	void setVentana(Json::Value);
	void setEscenario(Json::Value);
	void setPersonaje(Json::Value);

	Tdireccion obtieneEnum(string);
	int cantSprites(TestadoPersonaje);
	bool directorioExiste(const char*);
	void cargaExistosa(string);

	//Validacion de direcciones de archivos, numeros positivos, y tamaños deseados.
	void validacionPath(string);
	void validacionPositivoI(int,string,string);
	void validacionPositivoF(float,string,string);
	void validacionTamanioZindex();
	void validacionTamanioYpiso();
	void validacionAnchoVentanaEscenario();

	void copiarImagenDefault(int&,const char*);

	void ventanaDefecto();
	void escenarioDefecto();
	void personajeDefecto();
	void capasDefecto();

	bool esNumero();
};

/* namespace config */

#endif /* CONFIG_H_ */