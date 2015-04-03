#ifndef SALTOOBLICUO_H_
#define SALTOOBLICUO_H_

#include <math.h>
#include "../Accion.h"


class SaltoOblicuo : public Accion{
public:
	bool estado;
	bool orientacion;
	float a;
	Posicion posInicial;
	Posicion posFinal;
	float coeficiente; // Segun este coeficiente sumara o restara x para avanzar y retroceder
	float alturaPJ;
	float yPiso;
	float altoPantalla;

	SaltoOblicuo(float altura);

	void setEstado(bool nuevoEstado, Posicion nuevaPosicion,bool direccionSalto);
	Posicion realizarAccion(Posicion pos);
	bool getEstado();
	virtual ~SaltoOblicuo();
};

#endif /* SALTOOBLICUO_H_ */
