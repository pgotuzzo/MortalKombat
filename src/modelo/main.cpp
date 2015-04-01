#include <iostream>
#include "../modelo/Personaje.h"
#include "../modelo/Posicion.h"


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
	Posicion nuevaPosicion = Posicion();
	while (i <= 50) {
		subcero.realizarAccion((5));
		cout<<"posicion de SUBCERO en el loop"<<endl;
		cout<<"ESTA ES LA POSICION pos:"<<subcero.getPosicion().getX()<<"-"<<subcero.getPosicion().getY()<<endl;
		i++;
	}
	return 0;
}
