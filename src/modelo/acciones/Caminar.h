#ifndef ACCIONES_CAMINAR_H_
#define ACCIONES_CAMINAR_H_

#include "../Accion.h"

class Caminar : public Accion{

private:
	bool estado;
	bool direccion;

public:
	Caminar();
	float anchoDePaso;

	bool getEstado();
	void setEstado(bool nuevoEstado, bool nuevaDireccion);

	void setAnchoDePaso(float nuevoAnchoDePaso);
	void setAnchoDePasoDefault();

	Posicion realizarAccion(Posicion pos);
	Posicion realizarAccion(Posicion pos, bool dir);

	virtual ~Caminar();
};

#endif /* ACCIONES_CAMINAR_H_ */
