/*
 * coordenadas.h
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
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
	double getLongitud() const;

	void setLongitud(double);

	/*Obtener latitud:
	 * Precondicion: -
	 * Postcondicion: devuelve el valor de la latitud.
	 */
	double getLatitud() const;

	void setLatitud(double);

	/*Calcular distancia:
	 * Precondicion: recibe otro objeto coordenadas.
	 * Postcondicion: devuelve el valor de la distancia en metros entre ambas coordenadas.
	 */
	double distancia(const Coordenadas& c) const;

	/*Calcular la mas cercana:
	 * Precondicion: recibe dos objetos coordenadas.
	 * Postcondicion: devuelve el par de coordenadas mas cercano entre los dos.
	 */
	Coordenadas masCercana(Coordenadas& c1, Coordenadas& c2);

	std::string toString();
};



#endif /* COORDENADAS_H_ */
