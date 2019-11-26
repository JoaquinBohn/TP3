#ifndef RECORRIDO_H_
#define RECORRIDO_H_

#include "estacion.h"

class Recorrido {
private:
	Estacion* origen;
	Estacion* destino;
	double distancia;

public:

	Recorrido(Estacion*, Estacion*);

	Recorrido& operator= (const Recorrido&);

	Estacion* getOrigen();

	Estacion* getDestino();

	void setDestino(Estacion*&);

	void setOrigen(Estacion*&);

	bool esIgual(Recorrido*& recorrido);

	double calcularDistancia();
};

#endif /* RECORRIDO_H_ */
