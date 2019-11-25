/*
 * estacion.cpp
 *
 *  Created on: 23 oct. 2019
 *      Author: joaquin
 */

#include "estacion.h"
#include <string>
#include "coordenadas.h"

const std::string Estacion::TIPOS[] = {"colectivo", "subte", "tren", "metrobus", "garaje"};

Estacion& Estacion::operator= (const Estacion& estacion) {
	this->coordenadas = estacion.getCoordenadas();
	this->lineaDeTransporte = estacion.getLinea();
	this->id = estacion.getId();
	this->tipoDeTransporte = estacion.getTipo();
	return *this;
}

Estacion::Estacion(TipoEstacion transporte, std::string id, std::string linea, std::string nombre, std::string direccion, Coordenadas coordenadas){
	this->tipoDeTransporte = transporte;
	this->id = id;
	this->lineaDeTransporte = linea;
	this->nombre = nombre;
	this->direccion = direccion;
	this->coordenadas = coordenadas;
}

Estacion::~Estacion(){
}

bool Estacion::estaCerca(Estacion estacion, float radio){
	float distancia;
	Coordenadas coordenadasSegundaEstacion = estacion.getCoordenadas();
	distancia = (this->coordenadas).distancia(coordenadasSegundaEstacion);
	return(distancia<=radio);
}

Coordenadas Estacion::getCoordenadas() const{
	return this->coordenadas;
}

std::string Estacion::getLinea() const{
	return this->lineaDeTransporte;
}

std::string Estacion::getNombre() const{
	return this->nombre;
}

std::string Estacion::getId() const {
	return this->id;
}

TipoEstacion Estacion::getTipo() const {
	return this->tipoDeTransporte;
}

bool Estacion::mismaLinea(Estacion estacion){
	std::string lineaSegundaEstacion = estacion.getLinea();
	return(this->lineaDeTransporte == lineaSegundaEstacion);
}

bool Estacion::esIgual(Estacion*& estacion) {
	bool sonIguales = false;

	if (estacion->tipoDeTransporte == this->tipoDeTransporte
			&& estacion->id.compare(this->id) == 0) {
		sonIguales = true;
	}

	return sonIguales;
}




