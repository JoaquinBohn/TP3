/*
 * recorrido.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include "recorrido.h"
#include "estacion.h"
#include "EasyBMP.h"


Recorrido::Recorrido(Estacion* origen, Estacion* destino, double distanciaAnterior, Recorrido* anterior) {
	this->origen = origen;
	this->destino = destino;
	this->distancia = calcularDistancia();
	this->distanciaTotal = distanciaAnterior + this->distancia;
	this->siguientes = new Lista<Recorrido*>;
	this->anterior = anterior;
	this->precio = 0;
}

Recorrido::~Recorrido() {
	delete this->siguientes;
}

Recorrido& Recorrido::operator= (const Recorrido& recorrido) {
	this->origen = recorrido.origen;
	this->destino = recorrido.destino;
	return *this;
}

Estacion* Recorrido::getOrigen() {
	return this->origen;
}

Estacion* Recorrido::getDestino() {
	return this->destino;
}

Lista<Recorrido*>* Recorrido::getSiguientes() {
	return this->siguientes;
}

double Recorrido::getDistanciaTotal() {
	return this->distanciaTotal;
}

Recorrido* Recorrido::getAnterior() {
	return this->anterior;
}

void Recorrido::setAnterior(Recorrido* anterior) {
	this->anterior = anterior;
}

void Recorrido::setDestino(Estacion*& destino) {
	this->destino = destino;
}

void Recorrido::setOrigen(Estacion*& origen) {
	this->origen = origen;
}

bool Recorrido::esIgual(Recorrido*& recorrido) {
	bool sonIguales = false;
	if (this->origen->esIgual(recorrido->origen)
			&& this->destino->esIgual(recorrido->destino)) {
		sonIguales = true;
	}

	return sonIguales;
}

double Recorrido::calcularDistancia(){
	Coordenadas origen = this->origen->getCoordenadas();
	Coordenadas destino = this->destino->getCoordenadas();
	double distancia = origen.distancia(destino);
	return distancia;
}

