/*
 * arista.cpp
 *
 *  Created on: 25 nov. 2019
 *      Author: joaquin
 */

#include "Nodo.h"
#include "arista.h"
#include "estacion.h"
#include "coordenadas.h"

Arista::Arista(Nodo<Estacion>* origen, Nodo<Estacion>* destino){
	this->origen = origen;
	this->destino = destino;
}

Arista::~Arista(){

}

unsigned int Arista::obtenerLargo(){
	unsigned int largo;
	Coordenadas origen = this->origen->obtenerDato().getCoordenadas();
	Coordenadas destino = this->destino->obtenerDato().getCoordenadas();
	largo = origen.distancia(destino);
	return largo;
}


