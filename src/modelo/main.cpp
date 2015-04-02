#include <iostream>
#include "../modelo/Personaje.h"

using namespace std;

int main(int argc, char** argv){
/*
	pair<string,string> p1 = make_pair("hola","soy Miki");
	tr1::unordered_map<string,string> mymap;
	mymap.insert(p1);

	string valor = mymap["hola"];
	cout<<valor<<endl;
*/
	int i = 0;

	Personaje subcero = Personaje();
	cout<<"posicion Inicial de SUBCERO"<<endl;
	subcero.getPosicion().mostrarPar();
	while (i <= 50) {

		subcero.realizarAccion((6));
		cout<<"posicion de SUBCERO en el loop"<<endl;
		subcero.getPosicion().mostrarPar();
		i++;
	}
	return 0;
}
