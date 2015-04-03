#include <iostream>
#include "../modelo/Mundo.h"

using namespace std;

int main(int argc, char** argv){
/*
	pair<string,string> p1 = make_pair("hola","soy Miki");
	tr1::unordered_map<string,string> mymap;
	mymap.insert(p1);

	string valor = mymap["hola"];
	cout<<valor<<endl;
*/
	int i = 1;
	Mundo nuevoMundo = Mundo();
	Personaje* subcero = nuevoMundo.getPersonaje();

	cout<<"posicion Inicial de SUBCERO"<<endl;
	subcero->getPosicion().mostrarPar();
	while (i <= 600) {
		cout<<"Iteracion: "<<i<<endl;

		subcero->realizarAccion(3,1000);
		cout<<"posicion de SUBCERO en el loop"<<endl;
		subcero->getPosicion().mostrarPar();
		cout<<"---------------------------------------------"<<endl;

		i++;
	}
	subcero->realizarAccion(3,1000);
	subcero->getPosicion().mostrarPar();
	return 0;
}
