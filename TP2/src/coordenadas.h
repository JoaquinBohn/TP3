/*
 * coordenadas.h
 *
 *  Created on: 9 oct. 2019
 *      Author: joaquin
 */

#ifndef COORDENADAS_H_
#define COORDENADAS_H_

#include <string>

class Coordenadas{
private:
	double longitud;
	double latitud;

public:
	Coordenadas();
	Coordenadas& operator= (const Coordenadas &);

	/*Constructor:
	 * Precondicion: recibe dos numeros punto flotantes.
	 * Postcondicion: crea un objeto coordenadas con dos valores, el primero
	 * 				  para la longitud y el segundo para la latitud.
	 */
	Coordenadas(double, double);

	/*Destructor:
	 * Precondicion: -
	 * Postcondicion: por ahora nada
	 */
	~Coordenadas();

	/*Obtener longitud:
	 * Precondicion: -
	 * Postcondicion: devuelve el valor de la longitud.
	 */
	double getLongitud();

	void setLongitud(double);

	/*Obtener latitud:
	 * Precondicion: -
	 * Postcondicion: devuelve el valor de la latitud.
	 */
	double getLatitud();

	void setLatitud(double);

	/*Calcular distancia:
	 * Precondicion: recibe otro objeto coordenadas.
	 * Postcondicion: devuelve el valor de la distancia entre ambas coordenadas.
	 */
	double distancia(Coordenadas& c);

	/*Calcular la mas cercana:
	 * Precondicion: recibe dos objetos coordenadas.
	 * Postcondicion: devuelve el par de coordenadas mas cercano entre los dos.
	 */
	Coordenadas masCercana(Coordenadas& c1, Coordenadas& c2);

	std::string toString();
};



#endif /* COORDENADAS_H_ */
