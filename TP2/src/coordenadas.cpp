/*
 * coordenadas.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include "coordenadas.h"
#include <cmath>
#include <string>
#include <iostream>
#include <sstream>

Coordenadas::Coordenadas() {
	this->longitud = 0;
	this->latitud = 0;
}

Coordenadas& Coordenadas::operator= (const Coordenadas &coordenadas) {
	this->longitud = coordenadas.longitud;
	this->latitud = coordenadas.latitud;
	return *this;
}

Coordenadas::Coordenadas(double longitud, double latitud){
	this->longitud = longitud;
	this->latitud = latitud;
}

Coordenadas::~Coordenadas(){};

double Coordenadas::getLongitud() const {
	return this->longitud;
}

double Coordenadas::getLatitud() const {
	return this->latitud;
}

void Coordenadas::setLongitud(double longitud){
	this->longitud = longitud;
}

void  Coordenadas::setLatitud(double latitud){
	this->latitud = latitud;
}

double Coordenadas::distancia(const Coordenadas &c) const {
	double respuesta, restaLong, restaLat;
	restaLong = (this->longitud - c.getLongitud()) * 111320;
	restaLat = (this->latitud - c.getLatitud()) * 111320;
	respuesta = sqrt(restaLong*restaLong + restaLat*restaLat);
	return respuesta;
}


Coordenadas Coordenadas::masCercana(Coordenadas &c1, Coordenadas &c2){
	float distanciaC1, distanciaC2;
	distanciaC1 = this->distancia(c1);
	distanciaC2 = this->distancia(c2);
	if(distanciaC1<distanciaC2){
		return c1;
	} else {
		return c2;
	}
}

std::string Coordenadas::toString() {
	std::ostringstream oss;
	oss << this->latitud << ", " << this->longitud;
	std::string str = oss.str();
	return str;
}



