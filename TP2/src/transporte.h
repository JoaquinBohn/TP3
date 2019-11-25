/*
 * transporte.h
 *
 *  Created on: Oct 30, 2019
 *      Author: cristian
 */

#ifndef TRANSPORTE_H_
#define TRANSPORTE_H_

#include "Lista.h"
#include "estacion.h"
#include "coordenadas.h"

class Transporte {
private:
	Coordenadas minimo;
	Coordenadas maximo;
	Lista<Estacion*>* transportes;
	void ajustarMinimoYMaximo(Coordenadas& coordenadas);
	void cargarArchivo(const char* archivo, TipoEstacion tipo);
	void agregarEstacionColectivo(std::string &registro);
	void agregarEstacionSubte(std::string &registro);
	void agregarEstacionTren(std::string &registro);
	void agregarEstacionMetrobus(std::string &registro);
	void agregarEstacionGaraje(std::string &registro);

public:
	Transporte();
	~Transporte();
	void cargarTransportes();
	Lista<Estacion*>*& getTransportes();
	Coordenadas& getMinimo();
	Coordenadas& getMaximo();
};



#endif /* TRANSPORTE_H_ */
