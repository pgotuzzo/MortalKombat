/*
* main.cpp
*
*  Created on: 26/3/2015
*      Author: miguel
*/

#include "SDL2/SDL.h"
#include <iostream>
#include <tr1/unordered_map>

using namespace std;

int main(){
	pair<string,string> p1 = make_pair("hola","soy Miki");
	tr1::unordered_map<string,string> mymap;
	mymap.insert(p1);

	string valor = mymap["hola"];
	cout<<valor<<endl;
	return 0;
}
