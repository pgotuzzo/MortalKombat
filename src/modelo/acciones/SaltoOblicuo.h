#ifndef SALTOOBLICUO_H_
#define SALTOOBLICUO_H_

#include <math.h>
#include "../Accion.h"


class SaltoOblicuo : public Accion{

private:
	bool estado;
	bool orientacion;
	float a;
	Posicion posInicial;
	Posicion posFinal;
	float coeficiente; // Segun este coeficiente sumara o restara x para avanzar y retroceder
	float alturaPJ;
	float yPiso;
	float anchoPantalla;
	float altoPantalla;

	Posicion posImg;

public:

	SaltoOblicuo(float altura);

	bool getEstado();
	void setEstado(bool nuevoEstado, Posicion nuevaPosicion,bool sentidoSalto);

	Posicion realizarAccion(Posicion pos);

	virtual ~SaltoOblicuo();
};

#endif /* SALTOOBLICUO_H_ */
