#ifndef CONFIG_H_
#define CONFIG_H_
#include <iostream>
#include <string>
#include <vector>
#include "json.h"
#include "../Common.h"

using namespace std;

class config {

public:
	config(string path);
	virtual ~config();
	Tdireccion obtieneBool(string);
	Tventana getVentana();
	Tescenario getEscenario();
	vector<Tcapa> getCapas();
	Tpersonaje getPersonaje ();

private:
	Tventana ventana;
	Tescenario escenario;
	vector<Tcapa> vectorCapas;
	Tpersonaje personaje;

};

#endif /* CONFIG_H_ */
