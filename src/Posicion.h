#ifndef POSICION_H_
#define POSICION_H_

class Posicion {
public:
	float x;
	float y;


	Posicion();
	Posicion(float pos_x, float pos_y);
	float getX();
	float getY();
	Posicion operator=(Posicion p);
	Posicion operator+(Posicion p);
	Posicion operator-(Posicion p);
	bool operator==(Posicion p);
	void setX(float pos_x);
	void setY(float pos_y);
	void mostrarPar();

	virtual ~Posicion();
};

#endif /* POSICION_H_ */

