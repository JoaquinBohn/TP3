/*
 * archivo.cpp
 *
 *  Created on: Oct 18, 2019
 *      Author: cristian
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "estacion.h"
#include "Lista.h"
#include "auxiliar.h"
#include "transporte.h"

Transporte::Transporte() {
	this->transportes = new Lista<Estacion*>;
	this->minimo = Coordenadas(1000, 1000);
	this->maximo = Coordenadas(-1000, -1000);
}

Transporte::~Transporte() {
	this->transportes->iniciarCursor();
	while (this->transportes->avanzarCursor()) {
		delete this->transportes->obtenerCursor();
	}
	delete this->transportes;
}

void Transporte::ajustarMinimoYMaximo(Coordenadas& coordenadas) {
	if (coordenadas.getLatitud() < this->minimo.getLatitud()) {
		this->minimo.setLatitud(coordenadas.getLatitud());
	}
	if (coordenadas.getLatitud() > this->maximo.getLatitud()) {
		this->maximo.setLatitud(coordenadas.getLatitud());
	}
	if (coordenadas.getLongitud() < this->minimo.getLongitud()) {
		this->minimo.setLongitud(coordenadas.getLongitud());
	}
	if (coordenadas.getLongitud() > this->maximo.getLongitud()) {
		this->maximo.setLongitud(coordenadas.getLongitud());
	}
}

void Transporte::agregarEstacionColectivo(std::string &registro) {
	double longitud;
	double latitud;
	std::string id;
	std::string nombre;
	std::string direccion;
	std::string sentido;
	std::string lineaTransporte;

	std::string celda;
	std::stringstream streamDeCadena(registro);

	getline(streamDeCadena, id, ','); // id
	getline(streamDeCadena, celda, ','); // code
	getline(streamDeCadena, celda, ','); // name
	nombre = celda;
	direccion = celda;
	getline(streamDeCadena, celda, ','); // latitud
	latitud = stringADouble(celda);
	getline(streamDeCadena, celda, ','); // longitud
	longitud = stringADouble(celda);
	Coordenadas coordenadas(longitud, latitud);
	getline(streamDeCadena, sentido, ','); // direction
	getline(streamDeCadena, celda, ','); // route
	getline(streamDeCadena, celda, ','); // agency
	getline(streamDeCadena, celda, ','); // route_short_name (linea)
	lineaTransporte = celda + "*" + sentido;

	Estacion* estacion = new Estacion(colectivo, id, lineaTransporte, nombre, direccion, coordenadas);
	this->ajustarMinimoYMaximo(coordenadas);
	this->transportes->agregar(estacion);
}

void Transporte::agregarEstacionSubte(std::string &registro) {
	double longitud;
	double latitud;
	std::string id;
	std::string nombre;
	std::string direccion;
	std::string lineaTransporte;

	std::string celda;
	std::stringstream streamDeCadena(registro);

	getline(streamDeCadena, celda, ','); // longitud
	longitud = stringADouble(celda);
	getline(streamDeCadena, celda, ','); // latitud
	latitud = stringADouble(celda);
	Coordenadas coordenadas(longitud, latitud);
	getline(streamDeCadena, id, ','); // id
	getline(streamDeCadena, lineaTransporte, ','); // line
	getline(streamDeCadena, nombre, ','); // estacion
	for (int i = 0; i < 17; i++) {
		getline(streamDeCadena, celda, ','); // campos a ignorar
	}
	getline(streamDeCadena, direccion, ','); // dom_orig

	Estacion* estacion = new Estacion(subte, id, lineaTransporte, nombre, direccion, coordenadas);
	this->ajustarMinimoYMaximo(coordenadas);
	this->transportes->agregar(estacion);
}

void Transporte::agregarEstacionTren(std::string &registro) {
	double longitud;
	double latitud;
	std::string id;
	std::string nombre;
	std::string direccion;
	std::string lineaTransporte;

	std::string celda;
	std::stringstream streamDeCadena(registro);

	getline(streamDeCadena, celda, ','); // longitud
	longitud = stringADouble(celda);
	getline(streamDeCadena, celda, ','); // latitud
	latitud = stringADouble(celda);
	Coordenadas coordenadas(longitud, latitud);
	getline(streamDeCadena, id, ','); // id
	getline(streamDeCadena, nombre, ','); // nombre
	direccion = nombre;
	getline(streamDeCadena, lineaTransporte, ','); // linea
	getline(streamDeCadena, celda, ','); // linea2
	getline(streamDeCadena, celda, ','); // ramal
	lineaTransporte += " (" + celda + ")";

	Estacion* estacion = new Estacion(tren, id, lineaTransporte, nombre, direccion, coordenadas);
	this->ajustarMinimoYMaximo(coordenadas);
	this->transportes->agregar(estacion);
}

void Transporte::agregarEstacionMetrobus(std::string &registro) {
	double longitud;
	double latitud;
	std::string id;
	std::string nombre;
	std::string direccion;
	std::string lineaTransporte;

	std::string celda;
	std::stringstream streamDeCadena(registro);

	getline(streamDeCadena, celda, ','); // longitud
	longitud = stringADouble(celda);
	getline(streamDeCadena, celda, ','); // latitud
	latitud = stringADouble(celda);
	Coordenadas coordenadas(longitud, latitud);
	getline(streamDeCadena, id, ','); // id
	for (int i = 0; i < 6; i++) {
		getline(streamDeCadena, celda, ','); // campos a ignorar
	}
	getline(streamDeCadena, lineaTransporte, ','); // linea
	getline(streamDeCadena, nombre, ','); // nombre

	Estacion* estacion = new Estacion(metrobus, id, lineaTransporte, nombre, direccion, coordenadas);
	this->ajustarMinimoYMaximo(coordenadas);
	this->transportes->agregar(estacion);
}

void Transporte::agregarEstacionGaraje(std::string &registro) {
	double longitud;
	double latitud;
	std::string id;
	std::string nombre;
	std::string direccion;
	std::string altura;
	std::string lineaTransporte;

	std::string celda;
	std::stringstream streamDeCadena(registro);

	getline(streamDeCadena, celda, ','); // longitud
	longitud = stringADouble(celda);
	getline(streamDeCadena, celda, ','); // latitud
	latitud = stringADouble(celda);
	Coordenadas coordenadas(longitud, latitud);
	getline(streamDeCadena, id, ','); // smp
	getline(streamDeCadena, direccion, ','); // calle
	getline(streamDeCadena, altura, ','); // altura
	direccion = direccion + " " + altura;
	nombre = direccion;
	getline(streamDeCadena, celda, ','); // tipo1
	getline(streamDeCadena, lineaTransporte, ','); // tipo2

	if (lineaTransporte.compare("CERRADO")) {
		Estacion* estacion = new Estacion(garaje, id, lineaTransporte, nombre, direccion, coordenadas);
		this->ajustarMinimoYMaximo(coordenadas);
		this->transportes->agregar(estacion);
	}
}

void Transporte::cargarArchivo(const char* archivo, TipoEstacion tipo) {
	std::ifstream entrada;
	std::string registro;

	entrada.open(archivo);
	if (entrada.fail()) {
		throw std::string("No se pudo abrir ") + std::string(archivo);
	}

	// lee la linea con el nombre de los campos
	getline(entrada, registro);

	// se leen los registros del archivo hasta llegar al final
	while (getline(entrada, registro)) {
		switch(tipo) {
			case colectivo:
				agregarEstacionColectivo(registro);
				break;
			case subte:
				agregarEstacionSubte(registro);
				break;
			case tren:
				agregarEstacionTren(registro);
				break;
			case metrobus:
				agregarEstacionMetrobus(registro);
				break;
			case garaje:
				agregarEstacionGaraje(registro);
				break;
			case indefinido:
				break;
		}
	}
	entrada.close();
}

void Transporte::cargarTransportes() {
	std::cout << "Cargando colectivos (lento)..." << std::endl;
	cargarArchivo("paradas-de-colectivo.csv", colectivo);
	std::cout << "Colectivos cargados!" << std::endl;

	std::cout << "Cargando subtes..." << std::endl;
	cargarArchivo("bocas-de-subte.csv", subte);
	std::cout << "Subtes cargados!" << std::endl;

	std::cout << "Cargando trenes..." << std::endl;
	cargarArchivo("estaciones-de-ferrocarril.csv", tren);
	std::cout << "Trenes cargados!" << std::endl;

	std::cout << "Cargando metrobus..." << std::endl;
	cargarArchivo("estaciones-de-metrobus.csv", metrobus);
	std::cout << "Metrobus cargado!" << std::endl;

	std::cout << "Cargando garajes..." << std::endl;
	cargarArchivo("garajes-comerciales.csv", garaje);
	std::cout << "Garajes cargados!" << std::endl;
	std::cout << std::endl;
}

Lista<Estacion*>*& Transporte::getTransportes() {
	return this->transportes;
}

Coordenadas& Transporte::getMaximo() {
	return maximo;
}

Coordenadas& Transporte::getMinimo() {
	return minimo;
}



