#include "recorrido.h"
#include "estacion.h"
#include "EasyBMP.h"


Recorrido::Recorrido(Estacion* origen, Estacion* destino) {
	this->origen = origen;
	this->destino = destino;
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

void Recorrido::setDestino(Estacion*& destino) {
	this->destino = destino;
}

void Recorrido::setOrigen(Estacion*& origen) {
	this->origen = origen;
}

bool Recorrido::esIgual(Recorrido*& recorrido) {
	bool sonIguales = false;
	if (recorrido->origen->esIgual(this->origen)
			&& recorrido->destino->esIgual(this->destino)) {
		sonIguales = true;
	}

	return sonIguales;
}

