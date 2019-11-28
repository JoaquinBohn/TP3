/*
 * recorrido.h
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#ifndef RECORRIDO_H_
#define RECORRIDO_H_

#include "estacion.h"
#include "EasyBMP.h"

class Recorrido {
private:
	/* indican el origen y el destino de un recorrido */
	Estacion* origen;
	Estacion* destino;

	/* indica la distancia del recorrido */
	double distancia;

	/* indica la distancia total, incluyendo la distancia de los recorridos anteriores */
	double distanciaTotal;

	/* los proximos poisbles recorridos dentro de un camino */
	Lista<Recorrido*>* siguientes;

	/* el recorrido anterior dentro de un camino */
	Recorrido* anterior;

	/* el valor que se le asigna a este recorrido, segun el tipo de transporte y la distancia recorrida */
	double precio;

public:
	Recorrido(Estacion*, Estacion*, double distanciaAnterior, Recorrido* anterior);
	~Recorrido();
	Recorrido& operator= (const Recorrido&);
	Estacion* getOrigen();
	Estacion* getDestino();
	double getDistanciaTotal();
	void setDestino(Estacion*&);
	void setOrigen(Estacion*&);
	Lista<Recorrido*>* getSiguientes();
	Recorrido* getAnterior();
	void setAnterior(Recorrido* anterior);

	/* compara el recorrido actual con otro
	 *
	 * post: devuelve true si el origen y destino de los recorridos coinciden
	 */
	bool esIgual(Recorrido*& recorrido);

	/* calcula la distancias entre el origen y el destino del recorrido
	 *
	 * post: devuelve la distancia calculada
	 */
	double calcularDistancia();
};

#endif /* RECORRIDO_H_ */
