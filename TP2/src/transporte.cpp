/*
 * archivo.cpp
 *
 * Kiper, Cristian - padrón 100031.
 * Ligan, Cesar - padrón 101860.
 * Carbajal, Paulo - padrón 101311.
 * Bohn Valiere, Joaquin - padrón 102814.
 */

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "estacion.h"
#include "Lista.h"
#include "auxiliar.h"
#include "transporte.h"

const int Transporte::ID = 0;
const int Transporte::NOMBRE = 1;
const int Transporte::LATITUD = 2;
const int Transporte::LONGITUD = 3;
const int Transporte::LINEA = 4;
const int Transporte::IGNORAR = -1;
const int Transporte::FIN = -2;

Transporte::Transporte() {
	this->transportes = new Lista<Estacion*>;

	/* se incializan el minimo y el maximo con valores extremos */
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

unsigned int Transporte::lineaEsta(Lista<Estacion*> &lista, Estacion* &buscada) {
	bool esta = false;
	int posicion = 0;

	lista.iniciarCursor();
	while(!esta && lista.avanzarCursor()) {
		posicion++;
		Estacion* e = lista.obtenerCursor();
		if (e->getLinea().compare(buscada->getLinea()) == 0) {
			esta = true;
		}
	}

	return (esta) ? posicion : 0;
}

void Transporte::agregarEstacion(std::string& registro, TipoEstacion tipo, int orden[], char separador) {
	/* los valores que nos interesan se guardan en este arreglo de strings */
	std::string campos[] = {"", "", "", "", ""};

	unsigned int contadorRegistro = 0;
	unsigned int contadorCampos = 0;

	std::string celda;
	std::string celda2;
	std::stringstream streamDeCadena(registro);

	while(orden[contadorRegistro] != FIN && getline(streamDeCadena, celda, ',')) {
		if (celda.length() > 0 && celda.at(0) == '"') {
			/* el campo contiene un valor con coma.
			 * se combian dos campos para formar uno solo */
			getline(streamDeCadena, celda2, ',');
			celda = celda + "," + celda2;
			celda = celda.substr(1, celda.length() - 2);
		}
		if (orden[contadorRegistro] != IGNORAR) {
			if (campos[orden[contadorRegistro]].length() == 0) {
				campos[orden[contadorRegistro]] = celda;
			} else {
				/* se combinan varios valores si el campo que nos interesa
				 * esta formado por la combinacion de varios campos, utilizando
				 * un caracter de concatenacion que puede variar segun las necesidades */
				campos[orden[contadorRegistro]] = celda + separador + campos[orden[contadorRegistro]];
			}
			contadorCampos++;
		}
		contadorRegistro++;
	}

	Coordenadas coordenadas(stringADouble(campos[LONGITUD]), stringADouble(campos[LATITUD]));

	if (tipo != garaje || campos[LINEA].compare("CERRADO") != 0) {
		/* solo agrego la estacion si no corresponde a un garaje cerrado */
		Estacion* estacion = new Estacion(tipo, campos[ID], campos[LINEA], campos[NOMBRE], coordenadas);
		this->ajustarMinimoYMaximo(coordenadas);
		this->transportes->agregar(estacion);
	}
}

void Transporte::cargarArchivo(const char* archivo, TipoEstacion tipo, int orden[], char separador) {
	std::ifstream entrada;
	std::string registro;

	entrada.open(archivo);
	if (entrada.fail()) {
		throw std::string("No se pudo abrir ") + std::string(archivo);
	}

	/* lee la linea con el nombre de los campos */
	getline(entrada, registro);

	/* se leen los registros del archivo hasta llegar al final */
	while (getline(entrada, registro)) {
		agregarEstacion(registro, tipo, orden, separador);
	}
	entrada.close();
}

void Transporte::cargarTransportes() {
	/* para los campos que nos interesan se indica a que posicion del
	 * arreglo de campos deben ir, ver agregarEstacion().
	 * los campos que no nos interesan se marcan para ser ignorados */
	int ordenColectivo[] = {ID, IGNORAR, NOMBRE, LATITUD, LONGITUD, LINEA, IGNORAR, IGNORAR, LINEA, FIN};
	int ordenSubte[] = {LONGITUD, LATITUD, ID, LINEA, NOMBRE, FIN};
	int ordenTren[] = {LONGITUD, LATITUD, ID, NOMBRE, LINEA, IGNORAR, LINEA, FIN};
	int ordenMetrobus[] = {LONGITUD, LATITUD, ID, IGNORAR, IGNORAR, IGNORAR, IGNORAR, IGNORAR, IGNORAR, LINEA, NOMBRE, FIN};
	int ordenGarajes[] = {LONGITUD, LATITUD, ID, NOMBRE, NOMBRE, IGNORAR, LINEA, FIN};

	std::cout << "Cargando colectivos (lento)..." << std::endl;
	cargarArchivo("paradas-de-colectivo.csv", colectivo, ordenColectivo, '*');
	std::cout << "Colectivos cargados!" << std::endl;

	std::cout << "Cargando subtes..." << std::endl;
	cargarArchivo("bocas-de-subte.csv", subte, ordenSubte, ' ');
	std::cout << "Subtes cargados!" << std::endl;

	std::cout << "Cargando trenes..." << std::endl;
	cargarArchivo("estaciones-de-ferrocarril.csv", tren, ordenTren, '-');
	std::cout << "Trenes cargados!" << std::endl;

	std::cout << "Cargando metrobus..." << std::endl;
	cargarArchivo("estaciones-de-metrobus.csv", metrobus, ordenMetrobus, ' ');
	std::cout << "Metrobus cargado!" << std::endl;

	std::cout << "Cargando garajes..." << std::endl;
	cargarArchivo("garajes-comerciales.csv", garaje, ordenGarajes, ' ');
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



