/*
 * config.h
 *
 *  Created on: 26/3/2015
 *      Author: sebastian
 */

#ifndef CONFIG_H_
#define CONFIG_H_
#include <string>
#include <iostream>
#include "json.h"
#include <vector>

using namespace std;

namespace configuracion {

class config {

public:
	struct Tventana {
				int altopx;
				int anchopx;
				float ancho;

			};


	struct Tescenario {
		float ancho;
		float alto;
		int yPiso;
	};

	struct Tcapa {
		string dirCapa;
		float ancho;
	};

	vector<Tcapa> vectorCapas;

	struct Tpersonaje {
		float ancho;
		float alto;
		int zIndex;
		bool orientacion;

	};

public:



	config(string path);
	virtual ~config();
	bool obtieneBool(string);
	Tventana getVentana();
	Tescenario getEscenario();
	vector<Tcapa> getCapas();
	Tpersonaje getPersonaje ();

private:
	 Tventana ventana;
	 Tescenario escenario;
	 Tcapa capa;
	 Tpersonaje personaje;

};

} /* namespace config */

#endif /* CONFIG_H_ */
