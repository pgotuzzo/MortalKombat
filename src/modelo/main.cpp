#include "SDL2/SDL.h"
#include <iostream>
#include <tr1/unordered_map>
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
	while (i <= 10) {
		subcero.realizarAccion((i%5+1));
		cout<<"posicion de SUBCERO en el loop"<<endl;
		cout <<subcero.getPosicion().getX()<<endl;
		cout << subcero.getPosicion().getY()<<endl;
		i++;
	}
	return 0;
}
