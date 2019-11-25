/*
 * arista.h
 *
 *  Created on: 25 nov. 2019
 *      Author: joaquin
 */

#ifndef ARISTA_H_
#define ARISTA_H_

#include "estacion.h"

class Arista{
private:
	Nodo<Estacion>* origen;
	Nodo<Estacion>* destino;
public:
	/*
	 * Precondicion: recibe una estacion de origen y una de destino.
	 * Postcondicion: crea una arista que une ambas estaciones.
	 */
	Arista(Nodo<Estacion>*, Nodo<Estacion>*);

	/*
	 * Precondicion: -
	 * Postcondicion: -
	 */
	~Arista();

	/*
	 * Precondicion: -
	 * Postcondicion: devuelve el largo de la arista.
	 */
	unsigned int obtenerLargo();
};



#endif /* ARISTA_H_ */
