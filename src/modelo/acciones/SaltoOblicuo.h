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
	float anchoPantalla;
	float altoPantalla;

	float alturaSalto;
	float longitudSalto;
	float intervaloSalto;

	Posicion posImg;

	SaltoOblicuo(float altura);

	bool getEstado();
	void setEstado(bool nuevoEstado, Posicion nuevaPosicion,bool sentidoSalto);

	void setEstado(bool nuevoEstado);

	void setConfiguracion(float alturaSalto, float longitudSalto, float intervaloSalto);

	void setConfiguracionDefault();
	Posicion realizarAccion(Posicion pos,bool enCaida);

	virtual ~SaltoOblicuo();

	bool primeraVez;
	Posicion posCaida;
};

#endif /* SALTOOBLICUO_H_ */