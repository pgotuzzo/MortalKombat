#ifndef ACCIONES_CAMINAR_H_
#define ACCIONES_CAMINAR_H_

#include "../Accion.h"

class Caminar : public Accion{

private:
	bool estado;
	bool direccion;

public:
	Caminar();

	bool getEstado();
	void setEstado(bool nuevoEstado, bool nuevaDireccion);

	Posicion realizarAccion(Posicion pos);

	virtual ~Caminar();
};

#endif /* ACCIONES_CAMINAR_H_ */
