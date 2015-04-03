enum estado {caminando,parado}
struct cambios{
	Posicion p;
	estado e;
};

cambios c;

c.e = estado::caminando;
