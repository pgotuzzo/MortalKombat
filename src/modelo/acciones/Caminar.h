#ifndef ACCIONES_CAMINAR_H_
#define ACCIONES_CAMINAR_H_

#include "../Accion.h"

class Caminar : public Accion{
public:
	bool estado;
	bool direccion;
	//Orientacion true = orientacion derecha
	Caminar();
	bool getEstado();
	void setEstado(bool nuevoEstado, bool NuevaOrientacion);
	Posicion realizarAccion(Posicion pos);
	virtual ~Caminar();
};

#endif /* ACCIONES_CAMINAR_H_ */
