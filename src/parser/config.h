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
	void cargaPorDefecto();
	Tdireccion obtieneEnum(string);
	void validacionPath(string);
	void validacionPositivoI(int,string,string);
	void validacionPositivoF(float,string,string);
	int cantSprites(TestadoPersonaje);
};

/* namespace config */

#endif /* CONFIG_H_ */
