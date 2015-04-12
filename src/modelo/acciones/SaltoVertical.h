#ifndef SALTOVERTICAL_H_
#define SALTOVERTICAL_H_

#include "../Accion.h"

class SaltoVertical : public Accion{
public:
	Posicion posIni;
	Posicion posImg;
	bool subiendo;



	SaltoVertical();
	bool getEstado();
	void setEstado(bool nuevoEstado, Posicion nuevaPosicion);

	Posicion realizarAccion(Posicion pos_actual);
	virtual ~SaltoVertical();
};

#endif /* SALTOVERTICAL_H_ */
