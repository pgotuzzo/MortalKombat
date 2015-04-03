#include <iostream>
#include "../modelo/Mundo.h"
#include "../parser/config.h"

using namespace std;
using namespace configuracion;

int main(int argc, char** argv){
/*
	pair<string,string> p1 = make_pair("hola","soy Miki");
	tr1::unordered_map<string,string> mymap;
	mymap.insert(p1);

	string valor = mymap["hola"];
	cout<<valor<<endl;
*/
	int i = 1;

	config configur = config("/home/miguel/Escritorio/Workspace/MortalKombat/src/parser/EscenarioDefault.json");
	Mundo nuevoMundo = Mundo(configur);
	float anchoEscenario = nuevoMundo.getAncho();
	Personaje* subcero = nuevoMundo.getPersonaje();

	cout<<"posicion Inicial de SUBCERO"<<endl;
	subcero->getPosicion().mostrarPar();
	while (i <= 600) {
		cout<<"Iteracion: "<<i<<endl;

		subcero->realizarAccion(i%6+1,anchoEscenario);
		cout<<"posicion de SUBCERO en el loop"<<endl;
		subcero->getPosicion().mostrarPar();
		cout<<"---------------------------------------------"<<endl;

		i++;
	}

	return 0;
}
