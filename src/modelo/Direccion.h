/*
 * Direccion.h
 *
 *  Created on: 28/3/2015
 *      Author: miguel
 */

#ifndef DIRECCION_H_
#define DIRECCION_H_

class Direccion {
public:
	bool derecha;
	Direccion();
	void setDireccion(bool dir);
	bool getDireccion();
	virtual ~Direccion();
};

#endif /* DIRECCION_H_ */
