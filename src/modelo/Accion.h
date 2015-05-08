#ifndef ACCION_H_
#define ACCION_H_

#include "../Common.h"

// Clase madre de todas las acciones. Es una clase abstracta.

class Accion {
public:
	bool accion_activada;
	Posicion pos_inicial;
	bool estado;

	Accion();

	virtual bool getEstado();

	virtual void setEstado(bool nuevoEstado);

	virtual void setEstado(bool nuevoEstado, bool orientacion);

	virtual void setEstado(bool nuevoEstado, Posicion nuevaPosicion);

	virtual void setEstado(bool nuevoEstado, Posicion nuevaPosicion, bool orientacionSalto);

	virtual Posicion realizarAccion(Posicion posActual);

	virtual Posicion realizarAccion(Posicion pos,bool dir);

	virtual void setAnchoDePaso(float nuevoAnchoDePaso);

	virtual void setAnchoDePasoDefault();


	virtual ~Accion();
};

#endif /* ACCION_H_ */
