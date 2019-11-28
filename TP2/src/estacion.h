/*
 * estacion.h
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#ifndef ESTACION_H_
#define ESTACION_H_

#include <string>
#include "Lista.h"
#include "coordenadas.h"

enum TipoEstacion {
	colectivo = 0,
	subte = 1,
	tren = 2,
	metrobus = 3,
	garaje = 4
};

class Estacion{
private:
	TipoEstacion tipoDeTransporte;
	std::string id;
	std::string lineaDeTransporte;
	std::string nombre;
	Coordenadas coordenadas;

public:
	static const std::string TIPOS[];

	Estacion& operator= (const Estacion&);

	/*Constructor:
	 * Precondicion: recibe un tipo de transporte, el nombre de su linea y
	 * 				 un objeto de coordenadas.
	 * Postcondicion: crea una estacion.
	 */
	Estacion(TipoEstacion transporte, std::string id, std::string linea, std::string nombre, Coordenadas coordenadas);

	/*Destructor
	 * nada
	 */
	~Estacion();

	/*Obtener coordenadas:
	 * Precondicion: -
	 * Postcondicion: devuelve un objeto coordenadas de la estacion.
	 */
	Coordenadas getCoordenadas() const;

	/*Obtener linea:
	 * Precondicion: -
	 * Postcondicion: devuelve la linea de la estacion.
	 */
	std::string getLinea() const;

	std::string getId() const;

	std::string getNombre() const;

	TipoEstacion getTipo() const;

	/*La estacion esta cerca?:
	 * Precondicion: recibe una estacion y un numero.
	 * Postcondicion: devuelve true si la estacion se encuentra dentro del
	 * 				  radio ingresado por parametro. False en caso contrario.
	 */
	bool estaCerca(Estacion estacion, float radio);

	/*Pertenecen a la misma linea?:
	 * Precondicion: recibe una estacion.
	 * Postcondicion: devuelve true si son de la misma linea, false en caso contrario.
	 */
	bool mismaLinea(Estacion estacion);

	/*Obtener la estacion siguiente:
	 * Precondicion: recibe un puntero a una lista de punteros a estaciones y
	 * 				 un puntero a una estacion de destino.
	 * Postcondicion: devuelve un puntero a una estacion. Dicha estacion cumple
	 * 				  con los requisitos necesarios para ser la estacion siguiente.
	 */
	Estacion* obtenerEstacionSiguiente(Lista<Estacion>* , Estacion* destino);

	bool esIgual(Estacion*& estacion);
};



#endif /* ESTACION_H_ */
