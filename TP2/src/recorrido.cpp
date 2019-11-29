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
	this->precio = calcularPrecio();
	this->distanciaTotal = distanciaAnterior + this->distancia;
	this->siguientes = new Lista<Recorrido*>;
	this->anterior = anterior;
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

double Recorrido::getPrecio() {
	return this->precio;
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
	if (origen == NULL || destino == NULL) {
		return 0;
	}
	Coordenadas origen = this->origen->getCoordenadas();
	Coordenadas destino = this->destino->getCoordenadas();
	double distancia = origen.distancia(destino);
	return distancia;
}

double Recorrido::calcularPrecio() {
	double costo;
	if (origen == NULL || destino == NULL) {
		precio = 0;
	} else {
		switch (origen->getTipo()) {
			case colectivo:
			case metrobus:
				if (distancia <= 3000) {
					costo = 18;
				} else if (distancia <= 6000) {
					costo = 20;
				} else if (distancia <= 12000) {
					costo = 21;
				} else if (distancia <= 27000) {
					costo = 22;
				} else {
					costo = 23;
				}
				break;
			case subte:
				costo = 19;
				break;
			case tren:
				costo = 11;
				break;
			case garaje:
				costo = distancia * 0.004;
				break;
		}
	}

	return costo;
}

