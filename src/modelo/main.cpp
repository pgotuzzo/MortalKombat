#include "SDL2/SDL.h"
#include <iostream>
#include <tr1/unordered_map>

using namespace std;

int main(int argc, char** argv){
	pair<string,string> p1 = make_pair("hola","soy Miki");
	tr1::unordered_map<string,string> mymap;
	mymap.insert(p1);

	string valor = mymap["hola"];
	cout<<valor<<endl;
	return 0;
}
