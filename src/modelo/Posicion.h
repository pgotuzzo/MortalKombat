/*
 * Posicion.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef POSICION_H_
#define POSICION_H_

class Posicion {
public:
	float x;
	float y;


	Posicion();
	Posicion(float pos_x, float pos_y);
	float get_x();
	float get_y();
	Posicion operator=(Posicion p);
	Posicion operator+(Posicion p);
	Posicion operator-(Posicion p);
	bool operator==(Posicion p);
	void set_x(float pos_x);
	void set_y(float pos_y);

	virtual ~Posicion();
};

#endif /* POSICION_H_ */

